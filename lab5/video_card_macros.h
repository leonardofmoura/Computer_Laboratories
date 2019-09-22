#ifndef _VIDEO_CARD_MACROS_H_
#define _VIDEO_CARD_MACROS_H_

#define BIOS_VIDEO              0x10        //BIOS video services 

#define CALL_VBE                0x4F        //Call VBE

#define INDEXED_COLOR           0x105       //Indexed color mode


/*MACROS USED TO SET GRAPHIC MODE*/
#define VBE_SET_MODE            0x02        //Sets graphic mode
#define LINEAR_FRAME_FUFFER     (0x1<<14)   //Use linear/flat frame buffer model
#define WINDOW_FRAME_BUFFER     (0x0<<14)   //Use windowed frame buffer model
#define CLEAR_DISPLAY_MEM       (0x0<<15)   //Clear display memory
#define _CLEAR_DISPLAY_MEM      (0x1<<15)   //Don't clear display memory


/*MACROS USED TO GET MODE INFO*/
#define GET_MODE_INFO           0x01        //Get mode info


/*MACROS USED TO GET CONTROLLER INFO*/
#define GET_CONTR_INFO          0x00        //Get controller information


#endif

