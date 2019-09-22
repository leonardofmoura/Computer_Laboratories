#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#include <lcom/lcf.h>

/** @defgroup character character
 * @{
 *
 * Manages the main character and its animations
 */


/**
 * @brief Structure that stores all the information of the character
 * 
 */
typedef struct {
    /*@{*/
    int pos_x;                      /**<  @brief  Horizontal coordinate of the character*/
    int pos_y;                      /**<  @brief  Vertical coordinate of the character*/

    int speed;                      /**<  @brief  Speed of the character (how many pixels it moves at a time)*/

    int hitbox_width;               /**<  @brief  Width of the hitbox of the character*/
    int hitbox_height;              /**<  @brief  Height of the hitbox of the character*/

    xpm_image_t sprite;             /**<  @brief  Current sprite of the character*/
    
    int side;                       /**<  @brief  Side the character is facing*/  // 0 = up, 1= down, 2 = side left, 3 = side right
    bool idle;                      /**<  @brief  If the character is idle or not*/
    bool damaged;
    bool damaged_blink;
    int damaged_counter;

    int IdleCounter;                /**<  @brief  Tracks the idle animation*/
    xpm_image_t FrontIdle[12];      /**<  @brief  Array that contains the front idle sprites*/
    xpm_image_t BackIdle[12];       /**<  @brief  Array that contains the back idle sprites*/
    xpm_image_t SideLeftIdle[12];   /**<  @brief  Array that contains the left idle sprites*/
    xpm_image_t SideRightIdle[12];  /**<  @brief  Array that contains the right idle sprites*/

    int AttackCounter;              /**<  @brief  Tracks the attack animation*/
    xpm_image_t FrontAttack[8];     /**<  @brief  Array that contains the front attack sprites*/
    xpm_image_t BackAttack[8];      /**<  @brief  Array that contains the back attack sprites*/
    xpm_image_t SideLeftAttack[8];  /**<  @brief  Array that contains the left attack sprites*/
    xpm_image_t SideRightAttack[8]; /**<  @brief  Array that contains the right attack sprites*/

    int life;                       /**<  @brief  Current hit points of the character*/
    /*@}*/

} character_t;

xpm_image_t Bars[2];
xpm_image_t Life[3];
xpm_image_t Damage;

/**
 * @brief Initializes the character object
 * 
 * @return character_t* Pointer to the character created
 */
character_t* character_init();

/**
 * @brief Updates the position of the character
 * 
 * @param scancode_array Array with the scancode(s) of the key pressed
 */
void character_update(uint8_t* scancode_array);

/**
 * @brief Tells the program a valid key was pressed and updates the character sprite acordingly
 * 
 * @param scancode Single byte scancode of the key pressed
 */
void character_update_rec(uint8_t scancode);

/**
 * @brief Updates the position of the character
 * 
 * Updates all the parameters
 */
void character_refresh();

/**
 * @brief Draws the character on the screen
 * 
 * That means the second buffer
 * 
 */
void character_draw();

/**
 * @brief Deletes the character object
 * 
 * Frees the memory
 */
void character_delete();

/**
 * @brief Manages the idle animation of the character
 * 
 * By keepying track of the counter
 */
void character_bobbing();

/**
 * @brief Plays the blink animation of the character
 * 
 * By keepying track of the counter
 */
void character_blink();

/**
 * @brief Plays the attack animation of the character
 * 
 * By keepying track of the counter
 */
void character_attack();

/**
 * @brief Changes the idle parameter of the character acordingly to the IsItIdle parameter
 * 
 * @param IsItIdle Tells if the character is idle or not
 */
void character_idle( bool IsItIdle);

/**
 * @brief Changes to idle counter of the character to count
 * 
 * @param count Number to change the idle parameter to
 */
void character_IdleCounter(int count);

/**
 * @brief Changes to attack counter of the character to count
 * 
 * @param count Number to change the attack parameter to
 */
void character_AttackCounter(int count);

/**
 * @brief Gets the side the character is facing
 * 
 * @return int Side the character is facing
 */
int character_getSide();

/**
 * @brief Prints the hit points of the character
 * 
 */
void print_life();

/**
 * @brief Prints the bars on the bottom of the screen
 * 
 */
void print_bars();

/**@}*/

#endif
