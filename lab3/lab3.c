// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
//#include "timer.h"

#include "kbd.h"
#include "kbd_macros.h"
// Any header files below this line should have been created by you

extern uint8_t scancode_array[2];
extern bool two_byte_code;
extern unsigned int timer_counter;
extern uint32_t sys_inb_counter;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (kbd_test_scan)(bool assembly) {

  int ipc_status;
  message msg;
  uint8_t bit_no;
  uint32_t r;
  uint32_t irq_set = BIT(1); //Keyboard ID
  scancode_array[0] = 0;
  sys_inb_counter = 0;


  if(subscribe_kbc(&bit_no) != 0) {
    printf("KBC was unable to be subscribed\n");
    return 1;
  }

 while(scancode_array[0] != ESC_BREAK_CODE) { 
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  
                  if (assembly) {
                    kbc_asm_ih();
                  }
                  else {
                    kbd_ih();
                  }
                  
                  //printf("Tbc:%d\n",two_byte_code);
                  //printf("[0]:%x  [1]:%x\n",scancode_array[0],scancode_array[1]);

                  if (!two_byte_code && scancode_array[0] == TWO_BYTE_CODE) {
                    kbd_print_scancode(test_make(scancode_array[1]),2,scancode_array);
                  }
                  else if (!two_byte_code) {
                    kbd_print_scancode(test_make(scancode_array[0]),1,scancode_array);
                  }
                  

                  tickdelay(micros_to_ticks(DELAY_US));
               break;
                }
          default:
               break; /* no other notifications expected: do nothing */	
        }
    } 
    else { /* received a standard message, not a notification */
       /* no standard messages expected: do nothing */
    }
 }

 if(unsubscribe_kbc() != 0) {
    printf("KBC was unable to be unsubscribed\n");
    return 1;
  }

  if (!assembly) {
    kbd_print_no_sysinb(sys_inb_counter);
  }

  printf("End\n");
  return 0;
}




int (kbd_test_poll)() {
    
scancode_array[0] = 0;
sys_inb_counter = 0;

 while(scancode_array[0] != ESC_BREAK_CODE) { 
  scancode_array[0] = 0;
  
  kbd_ih();

  if (scancode_array[0] == 0xff || scancode_array[0] == 0x00) {
    tickdelay(micros_to_ticks(DELAY_US));
    continue;
  }
  //printf("[0]:%x\n",scancode_array[0]);

  if (!two_byte_code && scancode_array[0] == TWO_BYTE_CODE) {
    kbd_print_scancode(test_make(scancode_array[1]),2,scancode_array);
  }
  else if (!two_byte_code) {
    kbd_print_scancode(test_make(scancode_array[0]),1,scancode_array);
  }
               
  tickdelay(micros_to_ticks(DELAY_US));
  }

  KBD_enable();

  kbd_print_no_sysinb(sys_inb_counter);
 printf("End\n");
 return 0;
}




int (kbd_test_timed_scan)(uint8_t n) {

  int ipc_status;
  message msg;
  uint8_t bit_no0;
  uint8_t bit_no1;
  uint32_t r;
  uint32_t irq_set0 = BIT(0); //Timer ID
  uint32_t irq_set1 = BIT(1); //Keyboard ID
  scancode_array[0] = 0;


  if(timer_subscribe_int(&bit_no0) != 0) {
    printf("Timer notification was unable to be subscribed\n");
    return 1;
  }

  if(subscribe_kbc(&bit_no1) != 0) {
    printf("KBC was unable to be subscribed\n");
    return 1;
  }

   while(((timer_counter/60) < n) && (scancode_array[0] != ESC_BREAK_CODE)) { 
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: /* hardware interrupt notification */				
          

          if (msg.m_notify.interrupts & irq_set1) { /* subscribed interrupt */
                  
           kbd_ih();
                  
           if (!two_byte_code && scancode_array[0] == TWO_BYTE_CODE) {
            kbd_print_scancode(test_make(scancode_array[1]),2,scancode_array);
           }
           else if (!two_byte_code) {
            kbd_print_scancode(test_make(scancode_array[0]),1,scancode_array);
           }
                  
           //printf("%d", timer_counter);
           timer_counter = 0;
           break;
          }


          else if (msg.m_notify.interrupts & irq_set0) {
            timer_int_handler();
            break;
          }
          break;
               
          default:
               break; /* no other notifications expected: do nothing */	
        }
    } 
    else { /* received a standard message, not a notification */
       /* no standard messages expected: do nothing */
    }
 }

printf("\nTIME:%d\n", timer_counter/60);

 if(unsubscribe_kbc() != 0) {
    printf("KBC was unable to be unsubscribed\n");
    return 1;
 }


 if(timer_unsubscribe_int() != 0) {
    printf("Timer notification was unable to be unsubscribed\n");
    return 1;
 }


 printf("End\n");
 return 0;

}
