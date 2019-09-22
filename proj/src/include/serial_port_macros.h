#ifndef _SERIAL_PORT_MACROS_H_
#define _SERIAL_PORT_MACROS_H_

#ifndef BIT
#define BIT(n)          (0x1<<(n))
#endif

/** @defgroup serial_port_macros serial_port_macros
 * @{
 *
 * Constants for programming the serial port
 */


//com adresses
#define UART_COM1       0x3F8   /**<  @brief Base adress of com1*/
#define UART_COM1_IRQ   4       /**<  @brief com1 irq line*/

#define UART_COM2       0x2F8   /**<  @brief Base adress of com2*/
#define UART_COM2_IRQ   3       /**<  @brief com2 irq line*/

//uart registers
#define UART_RBR                        0       /**<  @brief receiver buffer register              R*/
#define UART_THR                        0       /**<  @brief transmiter holding register           W*/
#define UART_DLL                        0       /**<  @brief divisor latch lsb                     R/W*/
#define UART_IER                        1       /**<  @brief interrupt enable register             R/W*/
#define UART_DLM                        1       /**<  @brief divisor latch msb                     R/W*/
#define UART_IIR                        2       /**<  @brief ineterrupt identification register    R*/
#define UART_FCR                        2       /**<  @brief fifo control register                 W*/
#define UART_LCR                        3       /**<  @brief line control register                 R/W*/
#define UART_MCR                        4       /**<  @brief modem control register                R/W*/
#define UART_LSR                        5       /**<  @brief line status register                  R*/
#define UART_MSR                        6       /**<  @brief modem status resgiter                 R*/
#define UART_SR                         7       /**<  @brief scratchpad register                   R/W*/

//line control register (R/W)   LCR
#define LCR_NUMBER_OF_BITS_PER_CHAR     (BIT(0)&BIT(1))         /**< @brief number of bytes per char*/
#define LCR_STOP_BIT                    BIT(2)                  /**< @brief stop bit*/
#define LCR_PARITY_CONTROL              BIT(3)&BIT(4)&BIT(5)    /**< @brief parity control*/      
#define LCR_BREAK_CONTROL               BIT(6)                  /**< @brief break control*/
#define LCR_DLAB                        BIT(7)                  /**< @brief DLAB*/

//line status register (R)  LSR
#define LSR_RECIVER_DATA                BIT(0)      /**<  @brief Set to 1 when there is data for receiving*/
#define LSR_OVERRUN_ERROR               BIT(1)      /**<  @brief Set to 1 when a characters received is overwritten by another one */
#define LSR_PARITY_ERROR                BIT(2)      /**<  @brief Set to 1 when a character with a parity error is received*/
#define LSR_FRAMING_ERROR               BIT(3)      /**<  @brief Set to 1 when a received character does not have a valid Stop bit*/
#define LSR_BREAK_INTERRUPT             BIT(4)      /**<  @brief Set to 1 when the serial data input line is held in the low level for longer than a full “word” transmission*/
#define LSR_TRANSM_HOLD_EMPTY           BIT(5)      /**<  @brief When set, means that the UART is ready to accept a new character for transmitting*/
#define LSR_TRANSM_EMPTY_REG            BIT(6)      /**<  @brief When set, means that both the THR and the Transmitter Shift Register are both empty*/
#define LSR_FIFO_ERROR                  BIT(7)      /**<  @brief Set to 1 when there is at least one parity error or fram-
                                                     * ing error or break indication in the FIFO
                                                     * Reset to 0 when the LSR is read, if there are no sub-
                                                     * sequent errors in the FIFO
                                                     */


//interrupt enable register (R/W) IER
#define IER_ENABLE_DATA_INTERRUPT       BIT(0)      /**<  @brief Enable data interrupt */
#define IER_ENABLE_TRANS_EMPTY_INT      BIT(1)      /**<  @brief Enable transmiter empety interrupt*/
#define IER_ENABLE_REC_LINE_STAT_INT    BIT(2)      /**<  @brief Enable received line status interupt*/
#define IER_ENABLE_MODEM_STAT_INT       BIT(3)      /**<  @brief Enable modem status interrupt*/

//interrupt identification register (R) IIR
#define IIR_INTERRUPT_STATUS            BIT(0)                  /**<  @brief Interrupt status*/
#define IIR_INTERRUPT_ORIGIN            BIT(1)&BIT(2)&BIT(3)    /**<  @brief Interrupt origin*/    
#define IIR_64_BYTE_FIFO                BIT(5)                  /**<  @brief 64 byte fifo*/
#define IIR_FIFO_STATUS                 BIT(6)&BIT(7)           /**<  @brief fifo status*/
#define IIR_REC_DATA_AVAILABLE          BIT(2)                  /**<  @brief received data available*/
#define IIR_TRANS_HOLD                  BIT(1)                  /**<  @brief Transmition holding*/


#define START_ATTACK                    0xFF        /**<  @brief Start attack animation*/
#define STOP_ATTACK                     0xFE        /**<  @brief Stop animation attack*/

/*@}*/

#endif
