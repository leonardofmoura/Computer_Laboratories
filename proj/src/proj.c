// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "include/i8254.h"
#include "include/kbd.h"
#include "include/mouse.h"
#include "include/video_card.h"
#include "include/rtc.h"
#include "include/serial_port.h"
#include "include/crosshair.h"
#include "include/character.h"
#include "include/terrain.h"
#include "include/event_manager.h"
#include "include/button.h"
#include "include/projectile.h"
#include "include/enemy.h"

/** @defgroup proj proj
 * @{
 *
 * The main function, the driver receive loop with all the interrupts
 */


// Any header files included below this line should have been created by you

//Mouse global variables
extern struct packet pack;
extern int byte_no;

//keyboard global variables
extern uint8_t scancode_array[2];
extern bool two_byte_code;

//timer global variable
extern unsigned int timer_counter;
extern unsigned int sprite_timer_counter;
extern unsigned int sprite_attack_counter;


//rtc global variable
extern uint8_t real_time[3];

//other global variables
extern bool isPlayerIdle;
extern character_t character;

extern bool blink;
extern bool attack;

extern bool ProjectilesInMap [50];
extern projectile_t* ProjectilesInfo [50];


/**
 * @brief The main function, calls the lcf
 * 
 * @param argc Number of arguments
 * @param argv Array withe the arguments
 * @return int 0 on success, 1 otherwise
 */
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  // lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

/**
 * @brief The main project loop, has the driver receive loop that receives all the interrupts
 * 
 * @param argc Number of arguments
 * @param argv Array withe the arguments
 * @return int 0 on success, 1 otherwise
 */
int (proj_main_loop)(int argc, char *argv[]) {
  bool spectate;

  if (argc == 1) {
    if (strcmp(argv[0],"play") == 0) {
      spectate = false;
    }
    else if (strcmp(argv[0],"spectate") == 0) {
      spectate = true;
    }
    else {
      printf("ERROR : Invalid argument(s)\n");
      printf("Valid arguments are:\n");
      printf("- play : play the game\n");
      printf("- spectate : spectate somebody else's game\n");
      return 1;
    }
  }
  else {
    printf("ERROR : Invalid argument(s)\n");
    printf("Valid arguments are: - play : play the game\n");
    printf("                     - spectate : spectate somebody else's game\n");
    return 1;
  }


  enum State game_state;
  bool state_loaded;
  if (spectate) {
    game_state = SPECTATE_WAIT;
    state_loaded = false;
  }
  else {
    game_state = LOAD;
    state_loaded = false;
  }


  if (!spectate) {
    set_graphics_card_mode(0x14c);
  }

  int ipc_status; 
  message msg;
  uint8_t bit_no_mouse;
  uint8_t bit_no_kbd;
  uint8_t bit_no_timer;
  uint8_t bit_no_rtc;
  uint8_t bit_no_serial_port;
  uint32_t r;

  uint32_t irq_set_mouse = BIT(MOUSE_IRQ);
  uint32_t irq_set_kbd = BIT(KBD_IRQ);
  uint32_t irq_set_timer = BIT(TIMER0_IRQ);
  uint32_t irq_set_rtc = BIT(RTC_IRQ);
  uint32_t irq_set_serial_port = BIT(UART_COM1_IRQ);

  if (spectate) {
    if (serial_port_subscribe_rec(&bit_no_serial_port) != 0) {
      printf("Serial port unable to be subscirbed\n");
      return 1;
    }
  }
  else {
    if (serial_port_subscribe_trans(&bit_no_serial_port) != 0) {
      printf("Serial port unable to be subscirbed\n");
      return 1;
    }    
  }

  if(subscribe_kbc(&bit_no_kbd) != 0) {
    printf("KBC was unable to be subscribed\n");
    return 1;
  }

  clear_obf();

  if (subscribe_mouse(&bit_no_mouse) != 0) {
    printf("Mouse was unable to be subscribed\n");
    return 1;
  }

  if (rtc_subscribe(&bit_no_rtc) != 0) {
    printf("Rtc unable to be subscribed\n");
    return 1;
  }

  if (timer_subscribe_int(&bit_no_timer) != 0) {
    printf("Timer was unable to be subscribed\n");
    return 1;
  }

  mouse_enable_data_rep();

  if (!spectate) {
    crosshair_init();
  }

  run_event_manager(&game_state,INIT_COMPLETE,&state_loaded);

  while(game_state != EXIT) { /* You may want to use a different condition */
    if (!state_loaded) {
      if (load_state(game_state) != 0) {
        vg_exit();   //TEMPORARY
        free_mem();
        free_second_buf();
        break;
      }
      state_loaded = true;
    }

    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: /* hardware interrupt notification */

            if (msg.m_notify.interrupts & irq_set_mouse) { /* subscribed interrupt */
              mouse_ih();
              if (byte_no % 3 == 0) {
                build_packet(&pack);
                if (!spectate) {
                  crosshair_update(&pack);
                }

                // printf("run mouse ih\n");
                run_event_manager(&game_state,manage_interrupt(game_state,MOUSE),&state_loaded);
              }  
            }

            if (msg.m_notify.interrupts & irq_set_kbd) {
              kbd_ih();
              //just a debug code to exit the game quickly
              // if (scancode_array[0] == ESC_BREAK_CODE) {
              //   game_state = EXIT;
              // }
              // printf("state:%d\n",game_state);
              run_event_manager(&game_state,manage_interrupt(game_state,KEYBOARD),&state_loaded);
              //to prevent the pause menu to bug
              scancode_array[0] = 0;
              scancode_array[1] = 0;
            }

            if (msg.m_notify.interrupts & irq_set_timer) {
              timer_int_handler();
              if (timer_counter % 1 == 0) {
                run_event_manager(&game_state,manage_interrupt(game_state,TIMER),&state_loaded);
              }
            }

            if (msg.m_notify.interrupts & irq_set_rtc) { /* subscribed interrupt */
              rtc_ih();
              run_event_manager(&game_state,manage_interrupt(game_state,RTC),&state_loaded);
            }

            if (msg.m_notify.interrupts & irq_set_serial_port) { /* subscribed interrupt */
            serial_port_ih();
            run_event_manager(&game_state,manage_interrupt(game_state,SERIAL_PORT),&state_loaded);
            }

            break;
          default:
            break; /* no other notifications expected: do nothing */ 
      }
    }
    else {
      /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }

  // crosshair_delete();

  if (timer_unsubscribe_int() != 0) {
    printf("Timer was unable to be unsubscribed\n");
    return 1;
  }  

  if (rtc_unsubscribe() != 0) {
    printf("Rtc was unable to be unsubscribed\n");
    return 1;
  }

  if (mouse_disable_data_rep() != 0) {
    printf("Could not disable data reporting\n");
    return 1;
  }

  if (unsubscribe_mouse() != 0 ){
    return 1;
  }

  if(unsubscribe_kbc() != 0) {
    printf("KBC was unable to be unsubscribed\n");
    return 1;
  }

  if (spectate) {
    if (serial_port_unsubscribe_rec() != 0) {
      printf("Serial port unable to be unsubscribed\n");
      return 1;
    } 
  }
  else {
    if (serial_port_unsubscribe_trans() != 0) {
      printf("Serial port unable to be unsubscribed\n");
      return 1;
    } 
  }

  if (!spectate) {
  vg_exit();
  free_mem();
  free_second_buf();
  }


  return 0;
}

/**@}*/

