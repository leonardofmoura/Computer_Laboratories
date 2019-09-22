#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

/** @defgroup crosshair crosshair
 * @{
 *
 * Manages the crosshair in the menus and in-game 
 */

/**
 * @brief Stores all the information abou the crosshair
 * 
 */
typedef struct {
    /*@{*/
    int coord_x;        /**<  @brief  Horizontal coordinate of the crosshair*/
    int coord_y;        /**<  @brief  Vertical coordinate of the crosshair*/

    int prev_coord_x;   /**<  @brief  Previews  horizontal coordinate of the crosshair*/
    int prev_coord_y;   /**<  @brief  Previews  vertical coordinate of the crosshair*/

    bool RB_pressed;    /**<  @brief  True if the right mouse button is pressed*/
    bool MB_pressed;    /**<  @brief  True if the middle mouse button is pressed*/
    bool LB_pressed;    /**<  @brief  True if the left mouse button is pressed*/

    xpm_image_t sprite; /**<  @brief  Current sprite of the crosshair*/
    /*@}*/

} crosshair_t;

/**
 * @brief Initializes the crosshair object
 * 
 * @return crosshair_t* 
 */
crosshair_t* crosshair_init();

/**
 * @brief Deletes the crosshair object
 * 
 * Frees the memory
 */
void crosshair_delete();

/**
 * @brief Updates the position of the crosshair
 * 
 * @param pack Mouse packet recieved 
 */
void crosshair_update(struct packet* pack);

/**
 * @brief Draws the crosshair on the screen
 * 
 * That means the second buffer
 */
void crosshair_draw();

/**
 * @brief Changes the sprite of the crosshair to the one used ingame
 * 
 * The actual crosshair
 */
void crosshair_change_ingame();

/**
 * @brief Changes the sprite of the crosshair to the one used in the menu
 * 
 * More like a mouse cursor
 */
void crosshair_change_menu();

/**
 * @brief Highlights the crosshair used in the menu
 * 
 * Just changes the sprite
 */
void highlight_crosshair();

/**
 * @brief Unhighlights the crosshair used in the menu
 * 
 * Just changes the sprite
 */
void unhighlight_crosshair();

/**
 * @brief Get the horizontal coordiate of the object
 * 
 * @return int Horizontal coordiate of the object
 */
int get_crosshairX();

/**
 * @brief Get the vertical coordiate of the object
 * 
 * @return int Vertical coordiate of the object
 */
int get_crosshairY();

/**
 * @brief Get status of the left mouse button
 * 
 * @return true Left mouse button is pressed
 * @return false Right mouse button is pressed
 */
bool get_lb_pressed();

/**
 * @brief Checks if the crosshair is coliding with a colored pixel
 * 
 * @return true Colision detected
 * @return false No colision detected
 */
bool check_colision_with_pixel();

/**@}*/

#endif

