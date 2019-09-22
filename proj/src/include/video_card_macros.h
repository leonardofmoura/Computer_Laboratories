#ifndef _VIDEO_CARD_MACROS_H_
#define _VIDEO_CARD_MACROS_H_

/** @defgroup video_card_macros video_card_macros
 * @{
 *
 * Constants for programming the graphics card
 */


#define BIOS_VIDEO              0x10        /**<  @brief BIOS video services*/ 

#define CALL_VBE                0x4F        /**<  @brief Call VBE*/

#define INDEXED_COLOR           0x105       /**<  @brief Indexed color mode*/


/*MACROS USED TO SET GRAPHIC MODE*/
#define VBE_SET_MODE            0x02        /**<  @brief Sets graphic mode*/
#define LINEAR_FRAME_FUFFER     (0x1<<14)   /**<  @brief Use linear/flat frame buffer model*/
#define WINDOW_FRAME_BUFFER     (0x0<<14)   /**<  @brief Use windowed frame buffer model*/
#define CLEAR_DISPLAY_MEM       (0x0<<15)   /**<  @brief Clear display memory*/
#define _CLEAR_DISPLAY_MEM      (0x1<<15)   /**<  @brief Don't clear display memory*/


/*MACROS USED TO GET MODE INFO*/
#define GET_MODE_INFO           0x01        /**<  @brief Get mode information*/


/*MACROS USED TO GET CONTROLLER INFO*/
#define GET_CONTR_INFO          0x00        /**<  @brief Get controller information*/

/*@}*/


#endif

