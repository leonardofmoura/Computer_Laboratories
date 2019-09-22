// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "video_card.h"
#include "video_card_macros.h"

#include "kbd.h"
#include "kbd_macros.h"


//KEYBOARD GLOBAL VARIABLES
extern uint8_t scancode_array[2];
extern bool two_byte_code;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  //lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (video_test_init)(uint16_t mode, uint8_t delay) {
  
  
  if (set_graphics_card_mode(mode) != 0) {
    vg_exit();
    printf("Failed to set graphic mode\n");
    return 1;
  }

  tickdelay(micros_to_ticks(delay*1000000));

  vg_exit();
  free_mem();

  return 0;
}

int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                       uint16_t width, uint16_t height, uint32_t color) {

  if (set_graphics_card_mode(mode) != 0) {
    vg_exit();
    printf("Failed to set graphic mode\n");
    return 1;
  }

  //uint16_t starting_x = x - width/2;
  //uint16_t starting_y = y - height/2;

  int ipc_status;
  message msg;
  uint8_t bit_no;
  uint32_t r;
  uint32_t irq_set = BIT(1); //Keyboard ID
  scancode_array[0] = 0;

  vg_draw_rectangle(x,y,width,height,color);


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
                
                    kbd_ih();
    
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

  vg_exit();
  free_mem();

  printf("END!\n");

  return 0;
}

int (video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if (set_graphics_card_mode(mode) != 0) {
    vg_exit();
    printf("Failed to set graphic mode\n");
    return 1;
  }
  
  uint16_t rec_width = get_XResolution() / no_rectangles;
  uint16_t rec_height = get_YResolution() / no_rectangles;
  uint16_t right_stripe = get_XResolution() % no_rectangles;
  uint16_t bot_stripe = get_YResolution() % no_rectangles;
  //uint8_t bits_per_pix = get_BitsPerPixel();

  int ipc_status;
  message msg;
  uint8_t bit_no;
  uint32_t r;
  uint32_t irq_set = BIT(1); //Keyboard ID
  scancode_array[0] = 0;

  for (int j = 0; j < no_rectangles; j++) {
    if ((j*rec_height) >= (get_YResolution() - bot_stripe)) {
      break;
    }

    for (int i = 0; i < no_rectangles; i++) {
      if ((i*rec_width) >= (get_XResolution() - right_stripe)) {
        break;
      }

      if (mode == INDEXED_COLOR) {
        vg_draw_rectangle(i*rec_width,j*rec_height,rec_width,rec_height,index_col(i,j,step,first,no_rectangles));
      }

      else {
        vg_draw_rectangle(i*rec_width,j*rec_height,rec_width,rec_height,(B(i,j,step,first) | G(j,step,first) | R(i,step,first)));
        printf("C:%x\n",(B(j,i,step,first)));
      }
    }
  }

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
                
                    kbd_ih();
    
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

  vg_exit();
  free_mem();

  printf("END!\n");

  return 0;
}



int (video_test_xpm)(const char * 	xpm[], uint16_t 	x, uint16_t 	y)		{

  if (set_graphics_card_mode(0x105) != 0) {
    vg_exit();
    printf("Failed to set graphic mode\n");
    return 1;
  }


  int ipc_status;
  message msg;
  uint8_t bit_no;
  uint32_t r;
  uint32_t irq_set = BIT(1); //Keyboard ID
  scancode_array[0] = 0;

  int wd, hg;
  char *map;

  map = read_xpm(xpm, &wd, &hg);

  for (int iy = 0; iy < hg; iy++ ) {
    for (int ix = 0; ix < wd; ix++) {
      //char cor = colorpixmap(ixx, iyy, wd);

      if (pixel_set_color(map[iy * hg + ix], ix + x, iy + y) != 0) {
      vg_exit();
      printf("Failed to draw rectangle");
      return 1;
      }
    }
  }


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
                
                    kbd_ih();
    
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

  vg_exit();
  free_mem();

  printf("END!\n");

  return 0;
}


int (video_test_controller)() {
  vg_vbe_contr_info_t info_p;

  get_controller_info(&info_p);

  vg_display_vbe_contr_info(&info_p);

  return 0;
}
