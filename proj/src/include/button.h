#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <lcom/lcf.h>
#include "../include/event_manager.h"

/** @defgroup button button
 * @{
 *
 * Manages buttons and the main menu logo
 */

/**
 * @brief The type of a button
 * 
 */
enum ButtonType  {
    MENU_ST = 0,    /**<  @brief  Start Game button in the menu*/
    MENU_EXT,       /**<  @brief  Exit Game button in the menu*/
    MENU_CONT       /**<  @brief Continue game buton in the menu*/
};

/**
 * @brief Keeps the information of a button
 * 
 */
typedef struct {
    /*@{*/
    int coord_x;            /**<  @brief Horizontal coordinate*/
    int coord_y;            /**<  @brief Vertical coordinate*/

    enum ButtonType type;   /**<  @brief The type of the button*/

    xpm_image_t sprite;     /**<  @brief The sprite of the button*/
    /*@}*/

} button_t; 

/**
 * @brief Keeps the information of the logo
 * 
 */
typedef struct {
    /*@{*/
    int frame_number;       /**<  @brief The number of the current frame of the animation*/

    xpm_image_t sprite[3];  /**<  @brief Array with all the sprites of the animation*/
    /*@}*/

}logo_t;

/**
 * @brief Initializes the button array, needs to be called before creating any button
 * 
 */
void buttons_init();

/**
 * @brief Create a button object
 * 
 * @param x Horizontal coordinate of the button
 * @param y Vertical coordinate of the button
 * @param ButtonType Type of the button
 * @return true Button was created
 * @return false Unable to create the button
 */
bool create_button(int x, int y, enum ButtonType tp);

/**
 * @brief Checks if any button is coliding with the crosshair
 * 
 * @return button_t* Pointer to the button that is colliding (NULL if no colision was detected)
 */
button_t* check_colision_with_crosshair();

/**
 * @brief Highlights a button
 * 
 * @param button Pointer to the button being highlighted
 */
void button_highlight(button_t* button);

/**
 * @brief Unhighlights a button
 * 
 * @param button Pointer to the button being unhighlighted
 */
void button_unhighlight(button_t* button);

/**
 * @brief Draws all the buttons on the screen
 * 
 * Draw buttons 
 */
void draw_buttons();

/**
 * @brief Runs the event of a button
 * 
 * @param button Button to run the event
 * @return enum run_button_event Event that results in pressing the button
 */
enum Event run_button_event(button_t* button);

/**
 * @brief Deletes a button
 * 
 * @param button Pointer to the button being deleted
 */
void delete_button(button_t* button);

/**
 * @brief Sets the array of all the buttons to 0
 * 
 * Clears all 
 * 
 */
void clear_buttons();

/**
 * @brief Deallocs the memory of all the buttons
 * 
 * Frees the memory
 * 
 */
void free_buttons();

/**
 * @brief Initializes the logo
 * 
 * @return logo_t* Pointer to the logo initialized
 */
logo_t* logo_init();

/**
 * @brief Draws the logo on the screen
 * 
 * That means the second buffer
 */
void draw_logo();

/**
 * @brief Updates the animation frame of the logo
 * 
 * Increments the counter and changes the sprite
 */
void logo_update();

/**
 * @brief Deletes the logo
 * 
 * Frees the memory
 * 
 */
void logo_delete();

/**@}*/


#endif

