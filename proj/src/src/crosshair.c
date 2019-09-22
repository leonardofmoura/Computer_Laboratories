#include <lcom/lcf.h>
#include "../include/crosshair.h"
#include "../include/mouse.h"
#include "../include/kbd.h"
#include "../include/serial_port.h"
#include "../include/video_card.h"
#include "../sprites/Cursor-6.xpm"
#include "../sprites/Cursor_4.xpm"
#include "../sprites/Cursor_5.xpm"

crosshair_t* crosshair;

bool isPlayerIdle = true;

crosshair_t* crosshair_init() {
    crosshair = malloc(sizeof(*crosshair));

    crosshair->coord_x = get_XResolution()/2;
    crosshair->coord_y = get_YResolution()/2;
    crosshair->prev_coord_x = get_YResolution()/2;
    crosshair->prev_coord_y = get_YResolution()/2;
    crosshair->RB_pressed = false;
    crosshair->MB_pressed = false;
    crosshair->LB_pressed = false;

    xpm_load(Cursor_5_xpm,XPM_8_8_8_8,&crosshair->sprite);


    return crosshair;
}


void crosshair_update(struct packet* pack) {
    crosshair->prev_coord_x = crosshair->coord_x;
    crosshair->prev_coord_y = crosshair->coord_y;

    if (crosshair->coord_x + pack->delta_x >= get_XResolution()) {
        crosshair->coord_x = get_XResolution();
    }
    else if (crosshair->coord_x + pack->delta_x <= 0) {
        crosshair->coord_x = 0;
    }
    else {
        crosshair->coord_x += pack->delta_x;
    }

    
    if (crosshair->coord_y - pack->delta_y >= get_YResolution()) {
        crosshair->coord_y = get_YResolution();
    }
    else if (crosshair->coord_y - pack->delta_y <= 0) {
        crosshair->coord_y = 0;
    }
    else {
        crosshair->coord_y -= pack->delta_y;
    }
    
    crosshair->RB_pressed = pack->rb;
    crosshair->MB_pressed = pack->mb;
    crosshair->LB_pressed = pack->lb;

    if(crosshair->LB_pressed){
        isPlayerIdle = false;
    }
    else{
        isPlayerIdle = true;
    }

    //printf("x:%d, y:%d px:%d py:%d\n",crosshair->coord_x,crosshair->coord_y,pack->delta_x,pack->delta_y);

}

void crosshair_draw() {
    uint32_t* map = (uint32_t*) crosshair->sprite.bytes;


    for(int i = 0; i < crosshair->sprite.width; i++) {
        for (int j = 0; j < crosshair->sprite.height; j++) {
            pixel_set_color(*(map + i + j*crosshair->sprite.width),crosshair->coord_x + i - 7,crosshair->coord_y + j - 7);
        }
    } 

} 

void crosshair_change_ingame() {
    xpm_load(Cursor_6_xpm,XPM_8_8_8_8,&crosshair->sprite);
}

void crosshair_change_menu() {
    xpm_load(Cursor_5_xpm,XPM_8_8_8_8,&crosshair->sprite);
}

void highlight_crosshair() {
    xpm_load(Cursor_4_xpm,XPM_8_8_8_8,&crosshair->sprite);
}

void unhighlight_crosshair() {
    xpm_load(Cursor_5_xpm,XPM_8_8_8_8,&crosshair->sprite);
}

int get_crosshairX() {
    return crosshair->coord_x;
}

int get_crosshairY() {
    return crosshair->coord_y;
}

bool get_lb_pressed() {
    return crosshair->LB_pressed;
}

bool check_colision_with_pixel() {
    uint32_t pixelAdd = crosshair->coord_x + get_XResolution()*crosshair->coord_y;
    if (get_sec_buf_content(pixelAdd) != 0xff000000 && get_sec_buf_content(pixelAdd) != 0x0) {
        return true;
    }

    return false;
}


void crosshair_delete() {
    free(crosshair);
}




