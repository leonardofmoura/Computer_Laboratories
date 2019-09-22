#ifndef __TERRAIN_H_
#define __TERRAIN_H_

#include "../include/character.h"

/** @defgroup terrain terrain
 * @{
 *
 * Functions that manage terrain generation, and interactions withthe terrain
 */


/**
 * @brief Stores the information about a wall
 * 
 */
typedef struct {
    /*@{*/
    xpm_image_t sprite;     /**<  @brief  Sprite of the wall*/

    int coord_x;            /**<  @brief  Horizontal position of the wall*/
    int coord_y;            /**<  @brief  Vertical position of the wall*/

    int height;             /**<  @brief  Height of the wall*/
    int width;              /**<  @brief  Width of the wall*/
    /*@}*/
} wall_t;

/**
 * @brief Randomly generates the terrain: both the background and places the walls
 * 
 * @return uint8_t Seed used to generate the terrain
 */
uint8_t generate_terrain();

/**
 * @brief Generates the terrain: both the background and places the walls using the seed provided
 * 
 * @param seed The seed to be used
 * @return int 0 on success, 1 otherwise
 */
int generate_terrain_seed(uint8_t seed);

/**
 * @brief Loads a bakgound tile in the background buffer
 * 
 * @param coord_x Horizontal coordinate of the tile
 * @param coord_y Vertical coordinate of the tile
 * @return int 0 on success, 1 otherwise
 */
int load_block(int coord_x, int coord_y);

/**
 * @brief Draws the background on the second buffer
 * 
 * @return int 0 on success, 1 otherwise
 */
int terrain_draw();

/**
 * @brief Frees the memory allocated for the background buffer
 * 
 * Frees the memmory
 */
void terrain_free();

/**
 * @brief Inirtializes the walls array
 * 
 * Sets it all to o
 */
void walls_init();

/**
 * @brief Generates a new wall
 * 
 * @param x Horizontal coordinate of the wall
 * @param y Vertocal coordinate of the wall
 * @return true The wall generated
 * @return false Unable to generate the wall
 */
bool generate_wall(int x, int y);

/**
 * @brief Detects the colision of the character with a wall when going up
 * 
 * @param character Pointer to the character to test
 * @return true Colision detected
 * @return false No colision detected
 */
bool detect_colision_up(character_t* character);

/**
 * @brief Detects the colision of the character with a wall when going left
 * 
 * @param character Pointer to the character to test
 * @return true Colision detected
 * @return false No colision detected
 */
bool detect_colision_left(character_t* character);

/**
 * @brief Detects the colision of the character with a wall when going right
 * 
 * @param character Pointer to the character to test
 * @return true Colision detected
 * @return false No colision detected
 */
bool detect_colision_right(character_t* character);

/**
 * @brief Detects the colision of the character with a wall when going down
 * 
 * @param character Pointer to the character to test
 * @return true Colision detected
 * @return false No colision detected
 */
bool detect_colision_down(character_t* character);

/**
 * @brief Draws all the walls on the screen (That means the second buffer)
 * 
 * Thats means the second buffer
 */
void draw_walls();

/**
 * @brief Genarates a new pedestal
 * 
 * @param x Horizontal coordinate of the wall
 * @param y Vertical coordinate of the wall
 * @return true Pedeatal was generated
 * @return false Pedestal was not generated
 */
bool generate_pedestal(int x, int y);

/**@}*/

#endif

