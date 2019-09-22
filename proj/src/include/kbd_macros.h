#ifndef _KDB_MACROS_H_
#define _KDB_MACROS_H_

/** @defgroup kbd_macros kbd_macros
 * @{
 *
 * Constants for programming the keyboard
 */

#define KBD_IRQ                 1               /**< @brief  IRQ line of the keyboard*/

#define BIT(n)                  (0x01<<(n))

#define OUT_BUF                 0x60            /**< @brief  Output buffer*/   
#define IN_BUF                  0x64            /**< @brief  Input buffer*/       

#define STAT_REG                0x64            /**< @brief  Status register*/
#define KBC_CMD_REG             0x64

/*Keybord related KBC commands*/
#define READ_CMD                0x20            /**< @brief  Read command byte*/
#define WRITE_CMD               0x60            /**< @brief  Writ command byte*/
#define KCB_CHECK               0xAA            /**< @brief  Check kbc*/ 
#define KBD_INT_CHECK           0xAB            /**< @brief  Check keyboard interface*/   
#define KBD_INT_DISABLE         0xAD            /**< @brief  Disable kbd interface*/
#define KBD_INT_ENABLE          0xAE            /**< @brief  Enable kbd interface*/ 

#define ESC_BREAK_CODE          0x81            /**< @brief  Break code of the ESC key*/ 

#define TWO_BYTE_CODE           0xe0            /**< @brief  To test when a code is two bytes long*/ 

#define DELAY_US                20000           /**< @brief  Delay used in the delay funcion*/

#define _OBF                    0               /**< @brief  Ouput buffer full*/
#define _IBF                    1               /**< @brief  Input buffer full*/
#define _SYS                    2               /**< @brief  System flag*/
#define _A2                     3               /**< @brief  A2 input line*/
#define _INH                    4               /**< @brief  Inhibit flag*/
#define _AUX                    5               /**< @brief  Mouse data*/

/**@}*/

#endif
