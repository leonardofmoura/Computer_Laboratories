#ifndef _VIDEO_CARD_H_
#define _VIDEO_CARD_H_

int set_graphics_card_mode(uint16_t mode);

int pixel_set_color(uint32_t color, uint16_t hor, uint16_t vert);

int vbe_mode_info(uint16_t mode, vbe_mode_info_t* mode_info_p);

uint16_t get_XResolution();

uint16_t get_YResolution();

uint8_t get_BitsPerPixel();

uint32_t R(uint16_t col, uint16_t step, uint32_t first);

uint32_t G(uint16_t row, uint16_t , uint32_t first);

uint32_t B(uint16_t col, uint16_t row, uint16_t step, uint32_t first);

uint8_t index_col(uint16_t col,uint16_t row, uint16_t step, uint32_t first, uint8_t no_rectangles);

uint32_t create_red_mask();

uint32_t create_blue_mask();

uint32_t create_green_mask();

int colorpixmap(uint16_t x, uint16_t y, int wd);

int free_mem();

int get_controller_info(vg_vbe_contr_info_t *info_p);

#endif

