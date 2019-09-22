#include <lcom/lcf.h>

#include "../include/kbd.h"
#include "../include/mouse.h"

#include <minix/sysutil.h>
#include <stdint.h>

static int hook_id_kbd;
uint8_t scancode_array[2];
bool two_byte_code = false;
extern unsigned int timer_counter;

#ifdef LAB3
uint32_t sys_inb_counter;

void sys_inb_count() {
  sys_inb_counter++;
}
#endif
// Status Register Reader
int Status_Reader (int bit){
    uint32_t Status;
    if (sys_inb (STAT_REG, &Status) != 0) {
        return 1;
    }
    #ifdef LAB3
    sys_inb_count();
    #endif

    if (BIT(6) && Status) {
        //printf("Timeout error - invalid data");
        return 1;
    }
    if (BIT(7) && Status) {
        //printf("Parity error - invalid data");
        return 1;
    }
    switch (bit){
        case _OBF:
            if (BIT(0) && Status) {
                return 0;
            }
            else {return 1;}

        case _IBF:
            if (BIT(1) && Status) {
            return 0;
            }
            else {return 1;}

        case _SYS:
            if (BIT(2) && Status) {
            return 0;
            }
            else {return 1;}

        case _A2:
            if (BIT(3) && Status) {
            return 0;    
            }
            else {return 1;}

        case _INH:
            if (BIT(4) && Status) {
            return 0;    
            }
            else {return 1;}
        
        case _AUX:
            if (BIT(5) && Status) {
            return 0;    
            }
            else {return 1;}

        default:
            return 3;
    }
}

/*subscribes the KBC interrupts*/
int (subscribe_kbc)(uint8_t *bit_no) {
    hook_id_kbd = KBD_IRQ;
    *bit_no = hook_id_kbd;

    if (sys_irqsetpolicy(KBD_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id_kbd) != 0) {
        return 1;
    }

    return 0;
}

/*Unsubscribes the KBC interrupts*/
int (unsubscribe_kbc)(void) {
    uint8_t stat;
    

    if (sys_irqrmpolicy(&hook_id_kbd) != 0) {
        return 1;
    }

     
    kbc_read_status(&stat);

    
     if (stat & OBF) {
         clear_obf();
    }

    return 0;
}

bool test_make(uint8_t code) {
    uint8_t codeb = (uint8_t) code;
    if (codeb & BIT(7)) {
        return false;
    }
    else {
        return true;
    }
}

/*Interrupt handler written in C*/
void (kbd_ih)(void) {
    uint32_t scancode_store = 0;

    if (Status_Reader(_OBF) && Status_Reader(_AUX)) {

        sys_inb(OUT_BUF,&scancode_store);

        #ifdef LAB3
        sys_inb_count();
        #endif
        //printf("[1]:%x\n",scancode_store); debug printf

        if (two_byte_code) {
            scancode_array[1] = (uint8_t) scancode_store;
            two_byte_code = false;
            //printf("CHANGED1\n");
        }
        else if(scancode_store == TWO_BYTE_CODE) {
            scancode_array[0] = (uint8_t) scancode_store;
            two_byte_code = true;
            //printf("CHANGED2\n");

        }
        else {
            scancode_array[0] = (uint8_t) scancode_store;
            //printf("CHANGED3\n");
        }

        //printf("vec:%x,%x\n\n",scancode_array[0],scancode_array[1]); debug printf

    }
}


int KBD_enable() {

  uint32_t temp;

  if (sys_outb(STAT_REG, READ_CMD) != 0) {
    return 1;
  }

  if (sys_inb(OUT_BUF, &temp) != 0) {
    return 1;
  }

  #ifdef LAB3
  sys_inb_count();
  #endif

  temp |= BIT(0);

  if (sys_outb(STAT_REG, OUT_BUF) != 0) {
    return 1;
  }


  if (sys_outb(WRITE_CMD, temp) != 0) {
    return 1;
  }

  return 0;
}
