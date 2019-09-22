#ifndef _VIDEO_CARD_H_
#define _VIDEO_CARD_H_

#include "video_card_macros.h"

/** @defgroup video_card video_card
 * @{
 *
 * Functions that program the graphics card
 */

/**
 * @brief Stores the information abou the controller being used
 * 
 * 
 */
typedef struct __attribute__((packed))
{
    char        VESASignature[4];       /**<  @brief 'VESA' 4 byte signature          */
    uint8_t    VBEVersion[2];           /**<  @brief VBE version number               */
    uint32_t    OEMStringPtr;           /**<  @brief Pointer to OEM string            */
    uint32_t    Capabilities;           /**<  @brief Capabilities of video card       */
    uint32_t    VideoModePtr;           /**<  @brief Pointer to supported modes       */
    uint16_t    TotalMemory;            /**<  @brief Number of 64kb memory blocks     */

    /*added in VBE 2.0*/
    uint16_t    OEMSoftwareRev;          /**<  @brief VBE implementation Software revision*/
    uint32_t    OEMVendorNamePtr;        /**<  @brief Pointer to Vendor Name String     */
    uint32_t    OEMProductNamePtr;       /**<  @brief Pointer to Product Name String   */
    uint32_t    OEMProductRevPtr;        /**<  @brief Pointer to Product Revision String */

    char        reserved[222];           /**<  @brief Reserved for VBE implementation scratch area*/
    char        OEMData[256];            /**<  @brief Data Area for OEM Strings */
} VbeInfoBlock_t;


/**
 * @brief Set the graphics card mode. Allocate the video memory and the memory for the second buffer
 * 
 * @param mode The mode we want to set the graphics card to
 * @return int 0 on success, 1 otherwise
 */
int set_graphics_card_mode(uint16_t mode);

/**
 * @brief Sets the color of a pixel in the second buffer
 * 
 * @param color Color we want to set the pixel
 * @param hor Horizontal coordinate of the pixel
 * @param vert Vertical cooridinate of the pixel
 * @return int 0 on success, 1 otherwise
 */
int pixel_set_color(uint32_t color, uint16_t hor, uint16_t vert);

/**
 * @brief Copies an entire buffer to the second buffer 
 * 
 * @param mem 
 * @return int 
 */
int copy_to_sec_buf(uint32_t* mem);

/**
 * @brief Gets the color of a single pixel in the second buffer
 * 
 * @param pos Position in the second buffer
 * @return uint32_t The color of the pixel in that position
 */
uint32_t get_sec_buf_content(uint32_t pos);

/**
 * @brief Creates a new buffer the size of the video memory buffer
 * 
 * @return uint32_t* Pointer to the new buffer
 */
uint32_t* create_mem_buf();

/**
 * @brief Sets the screen to be all black
 * 
 * @return int 0 on success, 1 otherwise
 */
int set_black_screen();

/**
 * @brief Refreshes the screen
 * 
 * @return int 0 on success, 1 otherwise
 */
int screen_refresh();

/**
 * @brief Refreshed the screen but does not draw the crosshair
 * 
 * @return int 0 on success, 1 otherwise
 */
int screen_refresh_no_crosshair();

/**
 * @brief Gets the information needed to allocate the video memory buffer
 * 
 * @param mode Current mode we are using
 * @param mode_info_p Structure where we are going to place the information
 * @return int 0 on success, 1 otherwise
 */
int vbe_mode_info(uint16_t mode, vbe_mode_info_t* mode_info_p);

/**
 * @brief Get the current horizontal resolution
 * 
 * @return uint16_t Current horiontal resolution
 */
uint16_t get_XResolution();

/**
 * @brief Get the current vertical resolution
 * 
 * @return uint16_t Current vertical resolution
 */
uint16_t get_YResolution();

/**
 * @brief Get the number of bits of color each pixel uses
 * 
 * @return uint8_t The number of bit of color of each pixel
 */
uint8_t get_BitsPerPixel();

/**
 * @brief Red function for the pattern funciton in lab5
 * 
 * @param col The column of the matrix
 * @param step The step we are using
 * @param first The color of the first position of the matrix
 * @return uint32_t The new color
 */
uint32_t R(uint16_t col, uint16_t step, uint32_t first);

/**
 * @brief Green function for the pattern funciton in lab5
 * 
 * @param col The column of the matrix
 * @param step The step we are using
 * @param first The color of the first position of the matrix
 * @return uint32_t The new color
 */
uint32_t G(uint16_t row, uint16_t , uint32_t first);

/**
 * @brief Blue function for the pattern funciton in lab5
 * 
 * @param col The column of the matrix
 * @param step The step we are using
 * @param first The color of the first position of the matrix
 * @return uint32_t The new color
 */
uint32_t B(uint16_t col, uint16_t row, uint16_t step, uint32_t first);
/**
 * @brief Function used for the pattern function in lab5 for indexed color mode
 * 
 * @param col The column of the matrix
 * @param row The row of the matrix
 * @param step The step we are using
 * @param first The color of the first rectangle
 * @param no_rectangles The total number of rectangles
 * @return uint8_t The new color
 */
uint8_t index_col(uint16_t col,uint16_t row, uint16_t step, uint32_t first, uint8_t no_rectangles);

/**
 * @brief Create a mask for the red color 
 * 
 * @return uint32_t The mask itsef
 */
uint32_t create_red_mask();

/**
 * @brief Create a mask for the blue color 
 * 
 * @return uint32_t The mask itsef
 */
uint32_t create_blue_mask();

/**
 * @brief Create a mask for the green color 
 * 
 * @return uint32_t The mask itsef
 */
uint32_t create_green_mask();

/**
 * @brief Frees the memory allocated for the video memory buffer
 * 
 * @return int 0 on success, 1 otherwise
 */
int free_mem();

/**
 * @brief Frees the memoru allocated for the second buffer
 * 
 * @return int 0 on success, 1 otherwise
 */
int free_second_buf();

/**
 * @brief Gets the information about the graphics controller being used
 * 
 * @param info_p pointer to the struct where to place the information 
 * @return int 0 on success, 1 otherwise
 */
int get_controller_info(vg_vbe_contr_info_t *info_p);

/**
 * @brief Set the background to be solid green
 * 
 * Not used anymore
 */
void set_background_green();

/**@}*/

#endif

