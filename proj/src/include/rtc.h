#ifndef _RTC_H_
#define _RTC_H_

#include "rtc_macros.h"

/** @defgroup rtc rtc
 * @{
 *
 * Functions used to program the real time clock
 */

/**
 * @brief Subscribes rtc interrupts
 * 
 * @param bit_no Byte where to put the set bit
 * @return int 0 on success, 1 otherwise
 */
int rtc_subscribe(uint8_t* bit_no);

/**
 * @brief Unsubscribes rtc intrrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int rtc_unsubscribe();

/**
 * @brief Disables rtc interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int rtc_disable();

/**
 * @brief Enables rtc interrupts
 * 
 * @return int 0 on success, 1 otherwise
 */
int rtc_enable();

/**
 * @brief Gets the current configuration of the rtc
 * 
 * @param conf 4byte variable where to store the configuraton
 * @return int 0 on success, 1 otherwise
 */
int rtc_get_conf(uint32_t *conf);

/**
 * @brief Printf the configuration of the rtc
 * 
 * @param conf 4byte variable that contains the configuartion
 * @return int 4byte variable where to store the configuraton
 */
int rtc_print_config(uint32_t* conf);

/**
 * @brief Returns the current day in bcd
 * 
 * @return uint8_t Current day in bcd
 */
uint8_t rtc_get_day();

/**
 * @brief Returns the current month in bcd
 * 
 * @return uint8_t The current month in bcd
 */
uint8_t rtc_get_month();

/**
 * @brief Returns the current year in bcd
 * 
 * @return uint8_t The current year inb bcd
 */
uint8_t rtc_get_year();

/**
 * @brief Returns the current seconds in bcd
 * 
 * @return uint8_t The current seconds in bcd
 */
uint8_t rtc_get_seconds();

/**
 * @brief Returns the current minutes in bcd
 * 
 * @return uint8_t The current minutes in bcd
 */
uint8_t rtc_get_minutes();

/**
 * @brief Returns the current hours in bcd
 * 
 * @return uint8_t The current hours in bcd
 */
uint8_t rtc_get_hours();

/**
 * @brief Disables the updates of the rtc registers
 * 
 * @return int 0 on success, 1 otherwise
 */
int rtc_disable_updates();

/**
 * @brief Reenables updates of the rtc registers
 * 
 * @return int 0 on success, 1 otherwise
 */
int rtc_reenable_updates();

/**
 * @brief Function to change the hour used for debugging
 * 
 * @return int 0 on success, 1 otherwise
 */
int rtc_change_hour();

/**
 * @brief The interrupt handler of the rtc
 * 
 * Reads all the registers
 */
void rtc_ih();

/**
 * @brief Initializes the rtc
 * 
 * Just reads the registers
 */
void rtc_init();

/**
 * @brief Converts a bcd number to decimal
 * 
 * @param bin Number in bcd
 * @return uint8_t Number in decimal
 */
uint8_t bcd_to_dec(uint8_t bin);

/**
 * @brief Converts a decimal number to bcd
 * 
 * @param bcd Number in decimal
 * @return uint8_t Number in bcd
 */
uint8_t dec_to_bcd(uint8_t bcd);

/**
 * @brief Decreases a bcd by one
 * 
 * @param bcd Bcd to be decreased
 * @return uint8_t Decreased bcd
 */
uint8_t decrease_bcd(uint8_t bcd);

/*@}*/

#endif
