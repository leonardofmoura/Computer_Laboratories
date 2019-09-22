#include <lcom/lcf.h>

#include "../include/character.h"
#include "../include/terrain.h"
#include "../include/video_card.h"
#include "../include/serial_port.h"
#include "../include/projectile.h"


#include "../sprites/Sandstone_1.xpm"
#include "../sprites/Sandstone_2.xpm"
#include "../sprites/Sandstone_3.xpm"
#include "../sprites/Sandstone_4.xpm"
#include "../sprites/Sandstone_5.xpm"
#include "../sprites/Sandstone_6.xpm"
#include "../sprites/Sandstone_7.xpm"
#include "../sprites/Sandstone_Block_1.xpm"
#include "../sprites/Sandstone_Block_2.xpm"
#include "../sprites/Sandstone_Block_3.xpm"
#include "../sprites/Sandstone_Block_4.xpm"
#include "../sprites/Sandstone_Block_5.xpm"
#include "../sprites/Sandstone_Block_6.xpm"
#include "../sprites/Sandstone_Block_7.xpm"
#include "../sprites/Pedestal_1.xpm"


static uint32_t* terrain_background;
static xpm_image_t sprite_back;
static xpm_image_t sprite_wall;
wall_t* walls[200];

uint8_t generate_terrain() {
    srand(time(NULL));
    uint8_t seed = rand();

    walls_init();

    int floor_type = seed % 7 + 1;

    switch (floor_type) {
        case 1:
            xpm_load(Sandstone_1_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 2: 
            xpm_load(Sandstone_2_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 3: 
            xpm_load(Sandstone_3_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 4: 
            xpm_load(Sandstone_4_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 5: 
            xpm_load(Sandstone_5_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 6: 
            xpm_load(Sandstone_6_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 7: 
            xpm_load(Sandstone_7_xpm,XPM_8_8_8_8,&sprite_back);
            break;

        default: 
            xpm_load(Sandstone_7_xpm,XPM_8_8_8_8,&sprite_back);
            break;
    }

    int wall_type = (seed + 3 ) % 7 + 1;

    switch (wall_type) {
        case 1:
            xpm_load(Sandstone_Block_1_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 2: 
            xpm_load(Sandstone_Block_2_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 3: 
            xpm_load(Sandstone_Block_3_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 4: 
            xpm_load(Sandstone_Block_4_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 5: 
            xpm_load(Sandstone_Block_5_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 6: 
            xpm_load(Sandstone_Block_6_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 7: 
            xpm_load(Sandstone_Block_7_xpm,XPM_8_8_8_8,&sprite_wall);
            break;

        default: 
            xpm_load(Sandstone_Block_6_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
    }

    terrain_background = create_mem_buf();
    
    for (int i = 0; i < get_XResolution(); i += sprite_back.width) {
        for (int j = 0; j < get_YResolution(); j+= sprite_back.height) {
            load_block(i,j);
        }
    }

    //randomly generate walls
    int randX = seed;
    int randY = seed*seed;

    for (int n = 0; n < 30; n++) {
        randX = ((randX*randY + n) % 35) * 32;
        randY = ((randY*randX + n)  % 26) * 32;

        generate_wall(randX,randY);
    }

    //walls all arround the map
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(i,0);
    }
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(i,get_YResolution()-32);
    }
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(0,i);
    }
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(get_XResolution() - 32,i);
    }

    //generate pedestals
    bool equal = false;
    int generate_count = 0;
    int n = 0;
    while (generate_count < 3) {
        equal = false;
        randX = ((randX*randY + n + 3) % 35) * 32;
        randY = ((randY*randX + n + 7)  % 26) * 32;

        for (int i = 0; i < 200; i++) {
            if (walls[i] == 0) {
                break;
            }
            if (walls[i]->coord_x == randX && walls[i]->coord_y == randY) {
                equal = true;
                break;
            }
        }
        if (!equal) {
            generate_pedestal(randX,randY);
            generate_count++;
        }

        n++;
    }

    return seed;
}

int generate_terrain_seed(uint8_t seed) {
    walls_init();

    int floor_type = seed % 7 + 1;

    switch (floor_type) {
        case 1:
            xpm_load(Sandstone_1_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 2: 
            xpm_load(Sandstone_2_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 3: 
            xpm_load(Sandstone_3_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 4: 
            xpm_load(Sandstone_4_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 5: 
            xpm_load(Sandstone_5_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 6: 
            xpm_load(Sandstone_6_xpm,XPM_8_8_8_8,&sprite_back);
            break;
        case 7: 
            xpm_load(Sandstone_7_xpm,XPM_8_8_8_8,&sprite_back);
            break;

        default: 
            return 1;
    }

    int wall_type = (seed + 3 ) % 7 + 1;

    switch (wall_type) {
        case 1:
            xpm_load(Sandstone_Block_1_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 2: 
            xpm_load(Sandstone_Block_2_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 3: 
            xpm_load(Sandstone_Block_3_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 4: 
            xpm_load(Sandstone_Block_4_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 5: 
            xpm_load(Sandstone_Block_5_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 6: 
            xpm_load(Sandstone_Block_6_xpm,XPM_8_8_8_8,&sprite_wall);
            break;
        case 7: 
            xpm_load(Sandstone_Block_7_xpm,XPM_8_8_8_8,&sprite_wall);
            break;

        default: 
            return 1;
    }

    terrain_background = create_mem_buf();
    
    for (int i = 0; i < get_XResolution(); i += sprite_back.width) {
        for (int j = 0; j < get_YResolution(); j+= sprite_back.height) {
            load_block(i,j);
        }
    }

        int randX = seed;
        int randY = seed*seed;
    for (int n = 0; n < 30; n++) {
        randX = ((randX*randY + n) % 35) * 32;
        randY = ((randY*randX + n)  % 26) * 32;

        generate_wall(randX,randY);
    }    

    //walls all arround the map
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(i,0);
    }
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(i,get_YResolution()-32);
    }
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(0,i);
    }
    for (int i = 0; i < get_XResolution(); i+=32) {
        generate_wall(get_XResolution() - 32,i);
    }

    //generate pedestals
    bool equal = false;
    int generate_count = 0;
    int n = 0;
    while (generate_count < 3) {
        equal = false;
        randX = ((randX*randY + n + 3) % 35) * 32;
        randY = ((randY*randX + n + 7)  % 26) * 32;

        for (int i = 0; i < 200; i++) {
            if (walls[i] == 0) {
                break;
            }
            if (walls[i]->coord_x == randX && walls[i]->coord_y == randY) {
                equal = true;
                break;
            }
        }
        if (!equal) {
            generate_pedestal(randX,randY);
            generate_count++;
        }

        n++;
    }


    return 0;
}


int load_block(int coord_x, int coord_y) {

    uint32_t* map = (uint32_t*) sprite_back.bytes;

    for(int i = 0; i < sprite_back.width; i++) {
        for (int j = 0; j < sprite_back.height; j++) {
            uint32_t color = *(map + i + j*sprite_back.width);

            uint32_t* pixelAdd = terrain_background + coord_x + i + (coord_y + j)* get_XResolution();  

            memcpy(pixelAdd,&color,sizeof(uint32_t));      
        }
    }

    return 0;
}


int terrain_draw() {

    copy_to_sec_buf(terrain_background);

    return 0;
}


void terrain_free() {
    free(terrain_background);
}

void walls_init() {
    memset(walls,0,sizeof(walls));
}


bool generate_wall(int x, int y) {
    wall_t* wall = malloc(sizeof(wall_t));

    wall->coord_x = x;
    wall->coord_y = y;

    wall->sprite = sprite_wall;

    wall->height = 32;
    wall->width = 32;

    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            walls[i] = wall;
            return true;
        }
    }

    return false;
}


bool detect_colision_up(character_t* character) {
    int p1_x = character->pos_x + 4;
    int p1_y = character->pos_y;
    int p2_x = character->pos_x + character->hitbox_width;
    // int p2_y = character->pos_y;

    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            break;
        }

        int wall_height0 = walls[i]->coord_y;
        int w1_x = walls[i]->coord_x;
        int w1_y = walls[i]->coord_y + walls[i]->height - 3;
        int w2_x = walls[i]->coord_x + walls[i]->width;
        // int w2_y = walls[i]->coord_y + walls[i]->height;

        // printf("p1y : %d, w1y:%d\n",p1_y,w1_y);

        if ((p1_y <= w1_y + 3 && p1_y >= wall_height0) && ( (p1_x <= w2_x && p1_x >= w1_x) || (p2_x <= w2_x && p2_x >= w1_x) )) {
            return true;
        }
    }

    return false;
}

bool detect_colision_left(character_t* character) {
    int p1_x = character->pos_x + 4;
    int p1_y = character->pos_y + 3;
    // int p2_x = character->pos_x;
    int p2_y = character->pos_y + character->hitbox_height - 3;

    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            break;
        }

        int wall_width0 = walls[i]->coord_x;
        int w1_x = walls[i]->coord_x + walls[i]->width;
        int w1_y = walls[i]->coord_y;
        // int w2_x = walls[i]->coord_x + walls[i]->width;
        int w2_y = walls[i]->coord_y + walls[i]->height;

        // printf("p1x:%d , w1y: %d\n",p1_x,w1_y );

        if ((p1_x <= w1_x + 3 && p1_x >= wall_width0) && ( (p1_y <= w2_y && p1_y >= w1_y) || (p2_y <= w2_y && p2_y >= w1_y) )) {
            return true;
        }
    }

    return false;
}

bool detect_colision_right(character_t* character) {
    int p1_x = character->pos_x + 4 + character->hitbox_width;
    int p1_y = character->pos_y + 3;
    // int p2_x = character->pos_x;
    int p2_y = character->pos_y + character->hitbox_height - 3;

    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            break;
        }

        int wall_width1 = walls[i]->coord_x + walls[i]->width;
        int w1_x = walls[i]->coord_x;
        int w1_y = walls[i]->coord_y;
        // int w2_x = walls[i]->coord_x;
        int w2_y = walls[i]->coord_y + walls[i]->height;

        // printf("p1x:%d , w1y: %d\n",p1_x,w1_y );

        if ((p1_x >= w1_x - 2 && p1_x <= wall_width1) && ( (p1_y <= w2_y && p1_y >= w1_y) || (p2_y <= w2_y && p2_y >= w1_y) )) {
            return true;
        }
    }

    return false;
}

bool detect_colision_down(character_t* character) {
    int p1_x = character->pos_x + 4;
    int p1_y = character->pos_y + character->hitbox_height - 3;
    int p2_x = character->pos_x + character->hitbox_width;
    // int p2_y = character->pos_y;

    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            break;
        }

        int wall_height1 = walls[i]->coord_y + walls[i]->height;
        int w1_x = walls[i]->coord_x;
        int w1_y = walls[i]->coord_y;
        int w2_x = walls[i]->coord_x + walls[i]->width;
        // int w2_y = walls[i]->coord_y + walls[i]->height;

        // printf("p1y : %d, w1y:%d\n",p1_y,w1_y);

        if ((p1_y >= w1_y - 3 && p1_y <= wall_height1) && ( (p1_x <= w2_x && p1_x >= w1_x) || (p2_x <= w2_x && p2_x >= w1_x) )) {
            return true;
        }
    }

    return false;
}


void draw_walls() {
    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            break;
        }

        uint32_t* map = (uint32_t*) walls[i]->sprite.bytes;

        for(int j = 0; j < walls[i]->sprite.width; j++) {
            for (int k = 0; k < walls[i]->sprite.height; k++) {
                pixel_set_color(*(map + j + k*walls[i]->sprite.width),walls[i]->coord_x+j,walls[i]->coord_y+k);
            }
        } 
    }
}

bool generate_pedestal(int x, int y) {
    wall_t* wall = malloc(sizeof(wall_t));

    wall->coord_x = x;
    wall->coord_y = y;

    xpm_load(Pedestal_1_xpm,XPM_8_8_8_8,&wall->sprite);

    wall->height = 32;
    wall->width = 32;

    for (int i = 0; i < 200; i++) {
        if (walls[i] == 0) {
            walls[i] = wall;
            return true;
        }
    }

    return false;
}



