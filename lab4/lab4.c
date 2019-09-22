// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "mouse_macros.h"
#include "mouse_state_machine.h"
#include "i8254.h"

// Any header files included below this line should have been created by you

extern struct packet pack;
extern int byte_no;
extern unsigned int timer_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {

    int ipc_status;
    message msg;
    uint8_t bit_no;
    uint32_t r;
    uint32_t irq_set = BIT(MOUSE_IRQ);

    if (subscribe_mouse(&bit_no) != 0) {
        return 1;
    }

    mouse_enable_data_rep();

    while( cnt > 0 ) { /* You may want to use a different condition */
        /* Get a request message. */
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

                        mouse_ih();

                        if (byte_no % 3 == 0) {
                            
                            build_packet(&pack);
                            
                            cnt--;
                            mouse_print_packet(&pack);
                            
                            //printf("C:%d\n",cnt);
                        } 

                        //tickdelay(micros_to_ticks(DELAY_US));
                        
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
 
    if (mouse_disable_data_rep() != 0) {
        printf("Could not disable data reporting\n");
        return 1;
    }

    if (unsubscribe_mouse() != 0 ){
        return 1;
    }

    printf("End\n");
    return 0;
    
}


int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    uint8_t bit_no;
    uint8_t def_byte;

    if (subscribe_mouse(&bit_no) != 0) { //to disable minix IH
        return 1;
    }

    if (mouse_disable_data_rep() != 0) {
        return 1;
    }
    mouse_disable();

    if(mouse_set_remote_mode() != 0) {
        return 1;
    }

    while(cnt > 0) {
        if(mouse_read_data() != 0) {
            return 1;
        }

        mouse_ih();

        tickdelay(micros_to_ticks(DELAY_US));

        mouse_ih();

        tickdelay(micros_to_ticks(DELAY_US));

        mouse_ih();

        tickdelay(micros_to_ticks(DELAY_US));

        build_packet(&pack);

        mouse_print_packet(&pack);

        cnt--;

        //printf("%d\n",cnt);
        tickdelay(micros_to_ticks(period*1000));        
    }

    if (mouse_set_stream_mode() != 0) {
        return 1;
    }

    mouse_enable();
    if (mouse_disable_data_rep() != 0) {
        return 1;
    }
    
    if(unsubscribe_mouse() != 0) {
        return 1;
    }
    
    def_byte = minix_get_dflt_kbc_cmd_byte();

    if (write_kbc_command(def_byte) != 0) {
        return 1;
    }

    printf("END\n");
    return 0;
}


int (mouse_test_async)(uint8_t idle_time) {

    int ipc_status;
    message msg;
    uint8_t bit_no_mouse;
    uint8_t bit_no_timer;
    uint32_t r;
    uint32_t irq_set_mouse = BIT(MOUSE_IRQ);
    uint32_t irq_set_timer = BIT(TIMER0_IRQ);


    if (subscribe_mouse(&bit_no_mouse) != 0) {
        return 1;
    }

    if (timer_subscribe_int(&bit_no_timer) != 0) {
        return 1;
    }

    mouse_enable_data_rep();

    while( timer_counter/60 < idle_time ) { /* You may want to use a different condition */
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
                            
                            mouse_print_packet(&pack);
                            
                            timer_counter = 0;
                        } 

                        //tickdelay(micros_to_ticks(DELAY_US));
                        break;
                    }
                    
                    else if (msg.m_notify.interrupts & irq_set_timer) {
                        timer_int_handler();
                        break;
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

    if (timer_unsubscribe_int() != 0){
        return 1;
    }
 
    if (mouse_disable_data_rep() != 0) {
        printf("Could not disable data reporting\n");
        return 1;
    }

    if (unsubscribe_mouse() != 0 ){
        return 1;
    }

    printf("End\n");
    return 0;
    
}


int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    
    int ipc_status;
    message msg;
    uint8_t bit_no;
    uint32_t r;
    uint32_t irq_set = BIT(MOUSE_IRQ);
    int x_len_up = 0;
    int x_len_down = 0;

    enum State current_mouse_state = INITIAL_STATE; 
    enum State prev_mouse_state;


    if (subscribe_mouse(&bit_no) != 0) {
        return 1;
    }

    mouse_enable_data_rep();

    while(current_mouse_state != FINAL_STATE || x_len_up < x_len || x_len_down < x_len) { /* You may want to use a different condition */
        /* Get a request message. */
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

                        mouse_ih();

                        if (byte_no % 3 == 0) {
                            
                            build_packet(&pack);
                
                            mouse_print_packet(&pack);

                            prev_mouse_state = current_mouse_state;

                            current_mouse_state = run_state_machine(current_mouse_state,process_event(&pack,tolerance));
                            
                            if (prev_mouse_state == INITIAL_STATE && current_mouse_state == GOING_UP) {
                                x_len_up = 0;
                                x_len_up += pack.delta_x;
                            }
                            else if (prev_mouse_state == RELEASED && current_mouse_state == GOING_DOWN) {
                                x_len_down = 0;
                                x_len_down += pack.delta_x;
                            }
                            else if (prev_mouse_state == GOING_UP && current_mouse_state == GOING_UP) {
                                x_len_up += pack.delta_x;
                            }
                            else if (prev_mouse_state == GOING_DOWN && current_mouse_state == GOING_DOWN) {
                                x_len_down += pack.delta_x;
                            }

                            printf("%d     ",current_mouse_state);
                            printf("%d     %d\n",x_len_up,x_len_down);
                        } 

                        //tickdelay(micros_to_ticks(DELAY_US));
                        
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
 

    if (mouse_disable_data_rep() != 0) {
        printf("Could not disable data reporting\n");
        return 1;
    }

    if (unsubscribe_mouse() != 0 ){
        return 1;
    }

    printf("End\n");
    return 0;
    
}



