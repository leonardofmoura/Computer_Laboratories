#ifndef _KBD_H_
#define _KBD_H_

/*Subscribes yhe the KBC interrupts*/
int (subscribe_kbc)(uint8_t *bit_no);

/*Unsubscribes the KBC interrupts*/
int (unsubscribe_kbc)(void);

/*interrupt handler written in C*/
void(kbd_ih)(void);

// Status Register Reader (returns 0,1 and 3: 0 = true, 1 = false , 3 = error)
int (Status_Reader)(int bit);

bool test_make(uint8_t code);

int (timer_test_int)(uint8_t time);

int KBD_enable();

void sys_inb_count();

#endif
