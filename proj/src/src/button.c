#include <lcom/lcf.h>

#include "../include/button.h"
#include "../include/video_card.h"
#include "../include/crosshair.h"
#include "../include/event_manager.h"

#include "../sprites/Menu_1.xpm"
#include "../sprites/Menu_2.xpm"
#include "../sprites/Menu_3.xpm"
#include "../sprites/Menu_4.xpm"
#include "../sprites/Menu_5.xpm"
#include "../sprites/Menu_6.xpm"
#include "../sprites/Logo_1.xpm"
#include "../sprites/Logo_2.xpm"
#include "../sprites/Logo_3.xpm"

static button_t* buttons[3];   
static logo_t* logo; 

bool create_button(int x, int y, enum ButtonType tp) {
    button_t* button = malloc(sizeof(button_t));

    for (int i = 0; i < 3; i++) {
        if (buttons[i] == 0) {
            button->coord_x = x;
            button->coord_y = y;
            button->type = tp;

            switch (tp) {
                case MENU_ST: 
                    xpm_load(Menu_1_xpm,XPM_8_8_8_8,&button->sprite);
                    break;
                case MENU_EXT: 
                    xpm_load(Menu_3_xpm,XPM_8_8_8_8,&button->sprite);
                    break;
                case MENU_CONT:     
                    xpm_load(Menu_5_xpm,XPM_8_8_8_8,&button->sprite); //TEMPORARY
                    break;
 
                default: 
                    free(button);
                    return false;
            }    

            buttons[i] = button;

            return true;
        }
    }

    free(button);
    return false;
}

void buttons_init() {
    memset(buttons,0,sizeof(buttons));
}

void button_highlight(button_t* button) {
    switch (button->type) {
        case MENU_ST: 
            xpm_load(Menu_2_xpm,XPM_8_8_8_8,&button->sprite);
            break;
        case MENU_EXT: 
            xpm_load(Menu_4_xpm,XPM_8_8_8_8,&button->sprite);
            break;
        case MENU_CONT: 
            xpm_load(Menu_6_xpm,XPM_8_8_8_8,&button->sprite); //TEMPORARY
            break;
         default: 
            xpm_load(Menu_1_xpm,XPM_8_8_8_8,&button->sprite);
            break;
    }    
}

void button_unhighlight(button_t* button) {
    switch (button->type) {
        case MENU_ST: 
            xpm_load(Menu_1_xpm,XPM_8_8_8_8,&button->sprite);
            break;
        case MENU_EXT: 
            xpm_load(Menu_3_xpm,XPM_8_8_8_8,&button->sprite);
            break;
        case MENU_CONT:    
            xpm_load(Menu_5_xpm,XPM_8_8_8_8,&button->sprite); //TEMPORARY
            break;
        default: 
            xpm_load(Menu_1_xpm,XPM_8_8_8_8,&button->sprite);
            break;
    }    
       
}

void draw_buttons() {
    for (int k = 0; k < 3; k++ ) {
        if (buttons[k] == 0) {
            break;
        }
        uint32_t* map = (uint32_t*) buttons[k]->sprite.bytes;

        for(int i = 0; i < buttons[k]->sprite.width; i++) {
            for (int j = 0; j < buttons[k]->sprite.height; j++) {
                // printf("loop %d %d.....",i,j);
                pixel_set_color(*(map + i + j*buttons[k]->sprite.width),buttons[k]->coord_x+i,buttons[k]->coord_y+j);
            }
        } 
    }
}

button_t* check_colision_with_crosshair() {
    for (int i = 0; i < 3; i++) {
        if (buttons[i] == 0) {
            break;
        }

        int crossY = get_crosshairY();

        if (check_colision_with_pixel() && crossY >= buttons[i]->coord_y && crossY <= buttons[i]->coord_y + buttons[i]->sprite.height - 48) {
            return buttons[i];
        }
    }

    return NULL;
}

//returns the event when a button is pressed 
enum Event run_button_event(button_t* button) {
    switch (button->type) {
        case MENU_ST: 
            return START_GAME;
        case MENU_EXT: 
            return EXIT_GAME;
        case MENU_CONT: 
            return CONTINUE_GAME;
        default: 
            xpm_load(Menu_1_xpm,XPM_8_8_8_8,&button->sprite);
            break;
    }  
}

void delete_button(button_t* button) {
    free(button);
}

void clear_buttons() {
    memset(buttons,0,sizeof(buttons));
}

void delete_buttons() {
    for(int i = 0; i < 3; i++) {
        if (buttons[i] != 0) {
            free(buttons[i]);
        }
    }
}

logo_t* logo_init() {
    logo = malloc(sizeof(*logo));

    logo->frame_number = 0;

    xpm_load(Logo_1_xpm,XPM_8_8_8_8,&logo->sprite[0]);
    xpm_load(Logo_2_xpm,XPM_8_8_8_8,&logo->sprite[1]);
    xpm_load(Logo_3_xpm,XPM_8_8_8_8,&logo->sprite[2]);

    return logo;
}

void draw_logo() {
    uint32_t* map = (uint32_t*) logo->sprite[logo->frame_number].bytes;

    copy_to_sec_buf(map);
}

void logo_update() {
    switch (logo->frame_number) {
        case 0: 
            logo->frame_number = 1;
            break;
        
        case 1: 
            logo->frame_number = 2; 
            break;

        case 2: 
            logo->frame_number = 0;
            break;

        default: 
            logo->frame_number = 0;
            break;
        
    }
}

void logo_delete() {
    free(logo);
}

