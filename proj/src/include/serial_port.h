#ifndef _SERIAL_PORT_H
#define _SERIAL_PORT_H

#include <lcom/lcf.h>
#include "queue.h"
#include "serial_port_macros.h"

/** @defgroup serial_port serial_port
 * @{
 *
 * Functions used to program the serial port 
 */

/**
 * @brief Gets the serial port configuration (places it in a global array)
 * 
 * @param base_addr Base address of the serial port we want to get the configuration
 * @return int 0 on success, 1 otherwise
 */
int serial_port_get_config(uint32_t base_addr);

/**
 * @brief Prints the serial port configuration
 * 
 * @return int 0 on success, 1 otherwise
 */
int print_serial_port_config();

/**
 * @brief Sends a byte through the serial port (checks if the transmition can be done)
 * 
 * @param msg Message to be sent
 * @return int 0 on success, 1 otherwise
 */
int serial_port_send(uint8_t msg);

/**
 * @brief  Sends a byte through the serial port (does not check if the transmition can be done!)
 * 
 * @param msg Message to be sent
 * @return int 0 on success, 1 otherwise
 */
int serial_port_send_force(uint8_t msg);

/**
 * @brief Reads the receiver buffer register    
 * 
 * @return uint8_t Data read from the receiver buffer
 */
uint8_t serial_port_recieve();

/**
 * @brief Subsribes data received serial port interrupts
 * 
 * @param bit_no Byte where to put the set bit
 * @return int 0 on success, 1 otherwise
 */
int serial_port_subscribe_rec(uint8_t* bit_no);

/**
 * @brief Subsribes transmiter buffer holding serial port interrupts
 * 
 * @param bit_no Byte where to put the set bit
 * @return int 0 on success, 1 otherwise
 */
int serial_port_subscribe_trans(uint8_t* bit_no);

/**
 * @brief Unsubsribes data received serial port interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int serial_port_unsubscribe_rec();

/**
 * @brief Unsubsribes transmiter buffer holding serial port interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int serial_port_unsubscribe_trans();

/**
 * @brief The serial port interrupt handler, if the interrupt was a transmiter buffer holding
 * sets the flag that tells we can send information. If it's a received data interrupt
 * places the received data in the received_data_queue  
 * 
 * So it handles the two types of interrupts differently
 */
void serial_port_ih();

/**
 * @brief Transmits the front value of the transmit_data_queue
 * 
 * It also pops the value
 */
void serial_port_transmit();

/**
 * @brief Adds a value to the rear of the received_data_queue
 * 
 * @param elem Element to be added to the queue 
 */
void serial_port_add_to_transmit_queue(uint8_t elem);

/**
 * @brief Reads the front element of the received_data_queue, it also pops that element
 * 
 * @return uint8_t Element read from the received_data_queue
 */
uint8_t serial_port_read_recieved_queue();

/*@}*/

#endif
