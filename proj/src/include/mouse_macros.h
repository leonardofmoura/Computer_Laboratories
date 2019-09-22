#ifndef _MOUSE_MACROS_H
#define _MOUSE_MACROS_H

/** @defgroup mouse_macros mouse_macros
 * @{
 *
 * Constants for programming the mouse
 */

#define MOUSE_IRQ               12          /**< @brief  IRQ line of the mouse*/

#define BIT(n)                  (0x01<<(n))

#define OUT_BUF                 0x60        /**<  @brief  Output buffer*/
#define IN_BUF                  0x64        /**<  @brief  Input buffer*/

#define STAT_REG                0x64        /**<  @brief  Status register*/
#define KBC_CMD_REG             0x64        /**<  @brief  Command register*/
#define KBC_ARGS_REG            0x60        /**<  @brief  Arguments register*/
#define KBC_RET_REG             0x60        /**<  @brief  Values register*/

//mouse related KBC commands
#define READ_CMD                0x20        /**<  @brief  Read command byte*/
#define WRITE_CMD               0x60        /**<  @brief  Write command byte*/
#define MOUS_DISBL              0xA7        /**<  @brief  Disable mouse*/
#define MOUSE_ENBL              0xA8        /**<  @brief  Enable mouse*/
#define MOUSE_CHECK             0xA9        /**<  @brief  Check mouse*/ 
#define WRITE_MOUSE             0xD4        /**<  @brief  Write byte to mouse*/

//status register 
#define PARITY                  BIT(7)      /**<  @brief  Parity error*/
#define TIMEOUT                 BIT(6)      /**<  @brief  Timeout error*/
#define AUX                     BIT(5)      /**<  @brief  Mouse data*/
#define INH                     BIT(4)      /**<  @brief  Inhibit flag*/
#define A2                      BIT(3)      /**<  @brief  A2 input line*/
#define SYS                     BIT(2)      /**<  @brief  System flag*/
#define IBF                     BIT(1)      /**<  @brief  Input buffer full*/
#define OBF                     BIT(0)      /**<  @brief  Output buffer full*/

//commands passed as arguments of 0xD4
#define RESET                   0xFF        /**<  @brief  AMouse reset*/
#define RESEND                  0xFE        /**<  @brief  For serial comunications errors*/
#define SET_DEF                 0xF6        /**<  @brief  Set default values*/
#define DISABLE_REP             0xF5        /**<  @brief  In stream mode should be sent before any command*/
#define ENABLE_REP              0xF4        /**<  @brief  In stream mode only*/
#define SET_SAMPLE_RATE         0xF3        /**<  @brief  Sets state sampling rate*/
#define SET_REMOTE_MODE         0xF0        /**<  @brief  Send data request on packet only*/
#define READ_DATA               0xEB        /**<  @brief  Send data packet request*/
#define SET_STREAM_MODE         0xEA        /**<  @brief  Send data on events*/ 
#define STATUS_REQUEST          0xE9        /**<  @brief  Get mouse configuration (3 bytes)*/
#define SET_RESOLUTION          0xE8        
#define SET_SCALING_2_1         0xE7        /**<  @brief  Accelaration mode*/
#define SET_SCALING_1_1         0xE6        /**<  @brief  Linear mode*/

//acknowledgement bytes
#define ACK                     0xFA        /**<  @brief  Everything is ok*/
#define NACK                    0xFE        /**<  @brief  Invalid byte*/
#define ERROR                   0xFC        /**<  @brief  Second consecutive invalid byte*/


#define DELAY_US                20000       /**< @brief  Delay used in the delay funcion*/

/**@}*/

#endif
