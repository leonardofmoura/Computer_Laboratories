#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"


static int hook_id;
unsigned int timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  if (freq < 19) {  //test minimum freuency value
    printf("Frequency value too low!\n");
    return 1;
  }

  uint8_t B;
  if (timer_get_conf(timer,&B) != 0) {return 1;}
  //printf("B:%x\n",B);
	uint8_t MSB;
  uint8_t LSB;
	uint32_t MsbLsb = (TIMER_FREQ / freq);  // Novo Msb+Lsb (freq)
	util_get_LSB(MsbLsb,&LSB);  // Definicao novos Lsb
  util_get_MSB(MsbLsb,&MSB); // Definicao novos Msb

  if (timer == 0) {
			B = ((B & (BIT(0) | BIT(1) | BIT(2) | BIT(3))) | TIMER_SEL0 | TIMER_LSB_MSB); // Nova control word
      //printf("Control:%x \n",B);
			if (sys_outb(TIMER_CTRL, B) != 0) {return 1;}
			if (sys_outb(TIMER_0, LSB) != 0) {return 1;}
			if (sys_outb(TIMER_0, MSB) != 0) {return 1;}
      return 0;
  }
  if (timer == 1) {
  		B = ((B & (BIT(0) | BIT(1) | BIT(2) | BIT(3))) | TIMER_SEL1 | TIMER_LSB_MSB); // Nova control word
			if (sys_outb(TIMER_CTRL, B) != 0) {return 1;}
			if (sys_outb(TIMER_1, LSB) != 0) {return 1;}
			if (sys_outb(TIMER_1, MSB) != 0) {return 1;}
      return 0;
  }
  if (timer == 2) {
			B = ((B & (BIT(0) | BIT(1) | BIT(2) | BIT(3))) | TIMER_SEL2 | TIMER_LSB_MSB); // Nova control word
			if (sys_outb(TIMER_CTRL, B) != 0) {return 1;}
			if (sys_outb(TIMER_2, LSB) != 0) {return 1;}
			if (sys_outb(TIMER_2, MSB) != 0) {return 1;}
      return 0;
  }
  else {
    return 1;
  }
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = 0; 
  *bit_no = hook_id;

  if (sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id) != 0) {
    return 1;
  }

  return 0;
}

int (timer_unsubscribe_int)() {

  if (sys_irqrmpolicy(&hook_id) != 0 ) {
    return 1;
  }

  return 0;
}

void (timer_int_handler)() {
  timer_counter++;
}


int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be completey to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon succed by the students */

  uint32_t temp;  //temporary variable to store the value read by the read-back command
  uint32_t mask = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer)); // mask of the read-back 
                                                                          //command 

  if (sys_outb(TIMER_CTRL,mask) != 0) {
    return 1;
  }  //writes the read-back command in the control byte and tests for errors

  switch (timer) {
    case 0:
      if (sys_inb(TIMER_0,&temp) != 0) {
        return 1;
      }  //reads the timer couter (status) and stores it in the temp variable

      break;

    case 1:
      if (sys_inb(TIMER_1,&temp) != 0) {
        return 1;
      }  //reads the timer couter (status) and stores it in the temp variable

      break;

    case 2:
      if (sys_inb(TIMER_2,&temp) != 0) {
        return 1;
      }  //reads the timer couter (status) and stores it in the temp variable

      break;

    default:
      printf("Unable to find timer %d",timer);
      return 1;
  }


  *st = (uint8_t) temp;  //writes the LSB of temp in the pointer

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  union timer_status_field_val conf;
  
  switch (field) {
    case all:
      conf.byte = st;
      break;

    case initial: 
      if (st & TIMER_MSB ) { //tests if both bits are active
        if (st & TIMER_LSB) {
          conf.in_mode = MSB_after_LSB;
        }
        else {
          conf.in_mode = MSB_only;
        } 
      }

      else if (st & TIMER_LSB) {
        conf.in_mode = LSB_only;
      }
      else {
        conf.in_mode = INVAL_val;
      }
      break;
    
    case mode:

      if (st & TIMER_RATE_GEN) {
        if (st & BIT(1)) {
          conf.count_mode = 3;
        }
        else {
          conf.count_mode = 2;
        }
      }

      else if (st & (BIT(3))) {
        if (st & BIT(1)) {
          conf.count_mode = 5;
        }
        else {
          conf.count_mode = 4;
        }
      }

      else if (st & BIT(1)) {
        conf.count_mode = 1;
      }


      else {
        printf("Invalid mode \n");
        return 1;
      }
      break;

    case base: 
      if (st & TIMER_BCD) { //tests if the counter is in BCD
        conf.bcd = true;
      }
      else {
        conf.bcd = false;
      }
      break;
      
      default:
        printf("Invalid field \n");
        return 1;
  }
  //printf("FIELD: %d \n",field); // for debuging purposes  
  
  if (timer_print_config(timer,field,conf) != 0){
    return 1;
  }

  return 0;
}
