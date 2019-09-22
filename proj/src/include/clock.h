#ifndef _CLOCK_H_
#define _CLOCK_H_

/** @defgroup clock clock
 * @{
 *
 * Manages the display of the current date and time on the menu screens
 */

/**
 * @brief Struct that stores all the data of the clock
 * 
 */
typedef struct {

    /*@{*/
    uint8_t first_hour;         /**<  @brief  First digit of the hours*/
    uint8_t second_hour;        /**<  @brief  Second digit of the hours*/
    uint8_t first_minute;       /**<  @brief  First digit of the minutes*/
    uint8_t second_minute;      /**<  @brief  Second digit of the minutes*/
    uint8_t first_second;       /**<  @brief  First digit of the seconds*/
    uint8_t second_second;      /**<  @brief  Second digit of the seconds*/

    uint8_t first_year;         /**<  @brief  First digit of the year*/
    uint8_t second_year;        /**<  @brief  Second digit of the year*/
    uint8_t first_month;        /**<  @brief  First digit of the month*/
    uint8_t second_month;       /**<  @brief  Second digit of the month*/
    uint8_t first_day;          /**<  @brief  First digit of the day*/
    uint8_t second_day;         /**<  @brief  Second digit of the day*/

    int coord_x_clock;          /**<  @brief  Horizontal coordinate of the clock*/
    int coord_y_clock;          /**<  @brief  Vertical coordinate of the clock*/

    int coord_x_date;           /**<  @brief  Horizontal coordinate of the date*/
    int coord_y_date;           /**<  @brief  Vertical coordinate of the date*/

    xpm_image_t numbers[12];    /**<  @brief  Array with the sprites of all the numbers, colon and dot*/
    /*@}*/

} _clock_t;

/**
 * @brief Initializes the clock
 * 
 * @param xc Horizontal coordinate of the clock
 * @param yc Vertical coordinate of the clock
 * @param xd Horizontal coordinate of the date
 * @param yd Vertical coordinate of the date
 * @return _clock_t* Pointer to the clock initialized
 */
_clock_t* clock_init(int xc, int yc, int xd, int yd);

/**
 * @brief Updates all the parameters of the clock to the current time and date
 * 
 */
void clock_update();

/**
 * @brief Prints the current time on the console
 * 
 * 
 * Using printf
 */
void print_clock();

/**
 * @brief Draws the clock on the screen
 * 
 * That means the second buffer
 */
void display_clock();

/**
 * @brief Draws the date on the screen
 * 
 * That means the second buffer
 */
void display_date();

/**
 * @brief Deletes the clock structure
 * 
 * Frees the memory
 */
void clock_delete();

/**@}*/

#endif

