#ifndef _ENEMY_H_
#define _ENEMY_H_

/** @defgroup enemy enemy
 * @{
 *
 * The enemy
 */


typedef struct {
    /*@{*/
    int pos_x;          /**<  @brief  Horizontal position of the enemy*/   
    int pos_y;          /**<  @brief  Vertical position of the enemy*/
    int prev_pos_x;     /**<  @brief  Previews horizontal position of the enemy*/
    int prev_pos_y;     /**<  @brief  Previews vertical position of the enemy*/

    int speed;         /**<  @brief  Vertical speed of the enemy*/

    int hitbox[4];      /**<  @brief  Hitbox of the enemy*/
    /* (x1 | y1)............
       .....................
       ............(x4 | y4) */

    xpm_image_t sprite; /**<  @brief  Current sprite of the enemy*/
    
    int side;       /**<  @brief  Side the enemy is facing */ // 0 = up, 1= down, 2 = side left, 3 = side right

    int animFrame;  /**<  @brief  Current frame of the enemy animation*/

    int life;       /**<  @brief  Hit points of the enemy*/
    /*@}*/

} enemy_t;

xpm_image_t EnemyFront[2];      /**<  @brief  Array wih the sprites of the front animation of the enemy*/
xpm_image_t EnemyBack[2];       /**<  @brief  Array wih the sprites of the back animation of the enemy*/
xpm_image_t EnemySideLeft[2];   /**<  @brief  Array wih the sprites of the left animation of the enemy*/
xpm_image_t EnemySideRight[2];  /**<  @brief  Array wih the sprites of the right animation of the enemy*/

xpm_image_t Damage;             /**<  @brief  DEmage sprite of the enemy*/


enemy_t* EnemyInfo[10];         /**<  @brief  Array where the enemies are stored*/

bool EnemyInMap[10];            /**<  @brief  Tells if an enemy of the array is in the map*/


/**
 * @brief Starts the enemies array
 * 
 * Allocates the memory
 */
void enemyStart();

/**
 * @brief Creates a new enemy
 * 
 */
void enemyCreate();

/**
 * @brief Draws all the enemies 
 * 
 * On the second buffer
 */
void enemyDraw();

/**
 * @brief Refreshed the position of an enemy
 * 
 */
void enemy_refresh();

/**
 * @brief Manages the animation of an enemy
 * 
 */
void enemyAnim();

/**
 * @brief Checks if the enemies are coliding with walls or with other enemies
 * 
 */
void enemyCheckCollision();


/**@}*/

#endif
