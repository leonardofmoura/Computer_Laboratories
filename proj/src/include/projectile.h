#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

/** @defgroup projectile projectile
 * @{
 *
 * Funcions that control the projectile fired by the main character
 */


/**
 * @brief Structure that stores all the information of the projectile
 * 
 */
typedef struct {
    /*@{*/
    int pos_x;              /**<  @brief  Horizontal coordinate of the projectile*/
    int pos_y;              /**<  @brief  Vertical coordinate of the projectile*/

    int hitbox[4];          /**<  @brief  Hitbox of the projectile*/
    /* (x1 | y1)............
       .....................
       ............(x4 | y4) */

    int prev_pos_x;         /**<  @brief  previews horizontal coordinate of the projectile*/
    int prev_pos_y;         /**<  @brief  previews vertical coordinate of the projectile*/

    double speed;           /**<  @brief  speed of the projectile*/

    xpm_image_t spriteProj; /**<  @brief Current sprite of the projectile*/

    int animFrame;          /**<  @brief  Current frame of the animation*/
    float rotation;         /**<  @brief  Rotation of the projectile*/

    double Dx;              /**<  @brief  Horizontal deviation of the projectile*/        
    double Dy;              /**<  @brief  Vertical deviation of the projectile*/ 
    /*@}*/

} projectile_t;

/**
 * @brief Stores the information about the desintegration anumation of the projectile
 * 
 */
typedef struct {
    /*@{*/
    bool isIt;              /**<  @brief  Tells if the projectile is desintegrating*/
    int pos_x;              /**<  @brief  Horizontal coordinate of the projectile*/
    int pos_y;              /**<  @brief  Vertical coordinate of the projectile*/
    float rotation;         /**<  @brief  Rotation of the projectile*/
    int animFrame;          /**<  @brief  Current frame of the animation*/
    xpm_image_t sprite;     /**<  @brief  Current sprite of the animation*/
    /*@}*/

} desint_t;

xpm_image_t ProjAnimation[18];

desint_t* ProjectilesDesintegrating[50];

bool ProjectilesInMap [50];

projectile_t* ProjectilesInfo [50];

/**
 * @brief Checks if the projectile is coliding with a wall, and starts the animation
 * 
 * Uses the functions in terrain.h
 */
void projectile_check_collision();

/**
 * @brief Draws a projectile on the screen
 * 
 * That means the second buffer
 */
void projectile_draw();

/**
 * @brief Plays the projectile bobbing animation
 * 
 * By keeping track of the counter
 */
void projectile_bobbing();

/**
 * @brief Plays the projectile coliding animation
 * 
 * By keeping track of the counter
 */
void projectile_collide_anim();

/**
 * @brief Refreshes the position of the projectile
 * 
 * Updates the position
 */
void projectile_refresh();

/**
 * @brief Initializes the projectiles 
 * 
 * Allocates memory in the projectile array
 */
void projectiles_start();

/**
 * @brief Creates a new projectile
 * 
 * Allocates memory for a new project
 */
void projectile_create();

/**@}*/

#endif
