#ifndef _RTC_MACROS_
#define _RTC_MACROS_

/** @defgroup rtc_macros rtc_macros
 * @{
 *
 * Constants for programming the real time clock
 */


#ifndef BIT
#define BIT(n)          (0x1<<(n))
#endif

#define RTC_ADDR_REG    0x70    /**<  @brief  used to load with address of the RTC register to access*/
#define RTC_DATA_REG    0x71    /**<  @brief used to transfer data to/from the register accessed*/

#define RTC_IRQ         8       /**<  @brief rtc irq line*/

#define RTC_SEC         0       /**<  @brief rtc seconds register*/
#define RTC_ALARM_SEC   1       /**<  @brief rtc seconds alarm register*/
#define RTC_MIN         2       /**<  @brief rtc minutes register*/
#define RTC_ALARM_MIN   3       /**<  @brief rtc minutes alarm register*/
#define RTC_HOUR        4       /**<  @brief rtc hours register*/
#define RTC_ALARM_HOUR  5       /**<  @brief rtc hours alarm register*/
#define RTC_WEEK_DAY    6       /**<  @brief rtc day of the week register*/
#define RTC_MONTH_DAY   7       /**<  @brief rtc day of the month register*/
#define RTC_MONTH       8       /**<  @brief rtc month register*/
#define RTC_YEAR        9       /**<  @brief rtc year register*/

#define RTC_REG_A       10      /**<  @brief rtc register A*/
#define RTC_REG_B       11      /**<  @briefrtc register B*/
#define RTC_REG_C       12      /**<  @briefrtc register C*/
#define RTC_REG_D       13      /**<  @brief rtc register D*/

#define RTC_UIP         BIT(7)  /**<  @brief uip bit of regA*/
#define RTC_SET         BIT(7)  /**<  @brief set bit of regB*/

#define RTC_UIE         BIT(4)  /**<  @brief enable update interrupts*/

#define RTC_UF          BIT(4)  /**<  @brief update interrupt*/
#define RTC_AF          BIT(5)  /**<  @brief alarm interrupt*/
#define RTC_PF          BIT(6)  /**<  @brief periodic interrupt*/

#define RATE_SELECTOR   0xF     /**<  @brief show rate selector*/

#define FIRST(n)        (n>>4)  /**<  @brief first digit of a bcd*/
#define SECOND(n)       (n&0xF) /**<  @brief second digit of a bcd*/

/*@}*/

#endif

