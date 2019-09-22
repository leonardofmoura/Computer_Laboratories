#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "mouse_macros.h"

/** @defgroup mouse mouse 
 * @{
 *
 * Functions used to program the mouse
 */

/**
 * @brief Subscribes mouse interrupts
 * 
 * @param bit_no Byte where to put the set bit
 * @return int 0 on success, 1 otherwise
 */
int subscribe_mouse(uint8_t *bit_no);

/**
 * @brief Unsubscribes mouse interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int unsubscribe_mouse();

/**
 * @brief Disable mouse interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int disable_mouse();

/**
 * @brief Reads the status of the kbc
 * 
 * @param status Pointer to a byte where to put the status
 * @return int 0 on success, 1 otherwise
 */
int kbc_read_status(uint8_t * status);

/**
 * @brief Checks if the output buffer is empety
 * 
 * @return true Output buffer is empety
 * @return false Output buffer is full
 */
bool empty_obf();

/**
 * @brief Checks if the input buffer is empety
 * 
 * @return true Input buffer is empety
 * @return false Input buffer is full
 */
bool empty_ibf();

/**
 * @brief Writes a command to the mouse controller
 * 
 * @param command Command to be sent to the controller
 * @return int 0 on success, 1 otherwise
 */
int write_mouse_command(uint8_t command);

/**
 * @brief Send argument to the mouse controller
 * 
 * @param command Argument to be sent to the controller
 * @return int 0 on success, 1 otherwise
 */
int send_arg(uint8_t command);

/**
 * @brief Sets the mouse to operate in stream mode
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_set_stream_mode();

/**
 * @brief Sets the mouse to operate in remote mode
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_set_remote_mode();

/**
 * @brief Enables data reporting in the mouse
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_enable_data_rep();

/**
 * @brief Disables data reporting in the mouse
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_disable_data_rep();

/**
 * @brief Clears the output buffer
 * 
 * @return int 0 on success, 1 otherwise
 */
int clear_obf();

/**
 * @brief Convert the 2 complement to decimal in the horizontal axis
 * 
 * @param num Number in 2 complement
 * @return uint16_t Number in decimal
 */
uint16_t revert_2_complement_x(uint8_t num);

/**
 * @brief Convert the 2 complement to decimal in the vertical axis
 * 
 * @param num Number in 2 complement
 * @return uint16_t Number in decimal
 */
uint16_t revert_2_complement_y(uint8_t num);

/**
 * @brief Disable mouse interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_disable();

/**
 * @brief Enables mouse interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_enable();

/**
 * @brief Builds a mouse packet
 * 
 * @param pac Packet struct pointer where to put the built packet
 */
void build_packet(struct packet * pac);

/**
 * @brief Reads data sent by the mouse
 * 
 * @return int 0 on success, 1 otherwise
 */
int mouse_read_data();

/**
 * @brief Writes a command to the kbc
 * 
 * @param command Command to send to the kbc
 * @return int 0 on success, 1 otherwise
 */
int write_kbc_command(uint8_t command);

/**@}*/

#endif
