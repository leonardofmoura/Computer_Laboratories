#ifndef _KBD_H_
#define _KBD_H_

#include "kbd_macros.h"

/** @defgroup kbd kbd
 * @{
 *
 * Functions used to program the keyboard
 */

/**
 * @brief Subscribes keyboard interrupts
 * 
 * @param bit_no Byte where to put the set bit
 * @return int 0 on success, 1 otherwise
 */
int (subscribe_kbc)(uint8_t *bit_no);

/**
 * @brief Unsubscribes keyboard interrupts
 * 
 * @return int Returns 0 on success, 1 otherwise
 */
int (unsubscribe_kbc)(void);

/**
 * @brief Interrupt handler written in C
 * 
 * Reads the ouput buffer
 */
void(kbd_ih)(void);

// Status Register Reader (returns 0,1 and 3: 0 = true, 1 = false , 3 = error)
/**
 * @brief 
 * 
 */
int (Status_Reader)(int bit);

/**
 * @brief Tests if the code is a make code
 * 
 * @param code Code to test
 * @return true The code is a make code
 * @return false The code is not a make code
 */
bool test_make(uint8_t code);

int (timer_test_int)(uint8_t time);

/**
 * @brief Enables keyboard interrupts
 * 
 * @return int 
 */
int KBD_enable();

/**
 * @brief counts sys_inb calls
 * 
 * Increments the counter
 */
void sys_inb_count();

/**@}*/

#endif
