#include <lcom/lcf.h>
#include "../include/crosshair.h"
#include "../include/mouse.h"
#include "../include/kbd.h"
#include "../include/video_card.h"
#include "../include/character.h"
#include "../include/key_map.h"
#include "../include/terrain.h"
#include "../include/serial_port.h"
#include "../include/queue.h"
#include "../include/enemy.h"

// Idle Character Sprites
#include "../sprites/FrontIdle_00.xpm"
#include "../sprites/FrontIdle_01.xpm"
#include "../sprites/FrontIdle_02.xpm"
#include "../sprites/FrontIdle_03.xpm"
#include "../sprites/FrontIdle_04.xpm"
#include "../sprites/FrontIdle_05.xpm"
#include "../sprites/FrontIdle_06.xpm"
#include "../sprites/FrontIdle_07.xpm"
#include "../sprites/FrontIdle_08.xpm"
#include "../sprites/FrontIdle_09.xpm"
#include "../sprites/FrontIdle_10.xpm"
#include "../sprites/FrontIdle_11.xpm"
#include "../sprites/BackIdle_00.xpm"
#include "../sprites/BackIdle_01.xpm"
#include "../sprites/BackIdle_02.xpm"
#include "../sprites/BackIdle_03.xpm"
#include "../sprites/BackIdle_04.xpm"
#include "../sprites/BackIdle_05.xpm"
#include "../sprites/BackIdle_06.xpm"
#include "../sprites/BackIdle_07.xpm"
#include "../sprites/BackIdle_08.xpm"
#include "../sprites/BackIdle_09.xpm"
#include "../sprites/BackIdle_10.xpm"
#include "../sprites/BackIdle_11.xpm"
#include "../sprites/SideLeftIdle_00.xpm"
#include "../sprites/SideLeftIdle_01.xpm"
#include "../sprites/SideLeftIdle_02.xpm"
#include "../sprites/SideLeftIdle_03.xpm"
#include "../sprites/SideLeftIdle_04.xpm"
#include "../sprites/SideLeftIdle_05.xpm"
#include "../sprites/SideLeftIdle_06.xpm"
#include "../sprites/SideLeftIdle_07.xpm"
#include "../sprites/SideLeftIdle_08.xpm"
#include "../sprites/SideLeftIdle_09.xpm"
#include "../sprites/SideLeftIdle_10.xpm"
#include "../sprites/SideLeftIdle_11.xpm"
#include "../sprites/SideRightIdle_00.xpm"
#include "../sprites/SideRightIdle_01.xpm"
#include "../sprites/SideRightIdle_02.xpm"
#include "../sprites/SideRightIdle_03.xpm"
#include "../sprites/SideRightIdle_04.xpm"
#include "../sprites/SideRightIdle_05.xpm"
#include "../sprites/SideRightIdle_06.xpm"
#include "../sprites/SideRightIdle_07.xpm"
#include "../sprites/SideRightIdle_08.xpm"
#include "../sprites/SideRightIdle_09.xpm"
#include "../sprites/SideRightIdle_10.xpm"
#include "../sprites/SideRightIdle_11.xpm"

// Attack Character Sprites
#include "../sprites/FrontAttack_0.xpm"
#include "../sprites/FrontAttack_1.xpm"
#include "../sprites/FrontAttack_2.xpm"
#include "../sprites/FrontAttack_3.xpm"
#include "../sprites/FrontAttack_4.xpm"
#include "../sprites/FrontAttack_5.xpm"
#include "../sprites/FrontAttack_6.xpm"
#include "../sprites/FrontAttack_7.xpm"
#include "../sprites/BackAttack_0.xpm"
#include "../sprites/BackAttack_1.xpm"
#include "../sprites/BackAttack_2.xpm"
#include "../sprites/BackAttack_3.xpm"
#include "../sprites/BackAttack_4.xpm"
#include "../sprites/BackAttack_5.xpm"
#include "../sprites/BackAttack_6.xpm"
#include "../sprites/BackAttack_7.xpm"
#include "../sprites/SideLeftAttack_0.xpm"
#include "../sprites/SideLeftAttack_1.xpm"
#include "../sprites/SideLeftAttack_2.xpm"
#include "../sprites/SideLeftAttack_3.xpm"
#include "../sprites/SideLeftAttack_4.xpm"
#include "../sprites/SideLeftAttack_5.xpm"
#include "../sprites/SideLeftAttack_6.xpm"
#include "../sprites/SideLeftAttack_7.xpm"
#include "../sprites/SideRightAttack_0.xpm"
#include "../sprites/SideRightAttack_1.xpm"
#include "../sprites/SideRightAttack_2.xpm"
#include "../sprites/SideRightAttack_3.xpm"
#include "../sprites/SideRightAttack_4.xpm"
#include "../sprites/SideRightAttack_5.xpm"
#include "../sprites/SideRightAttack_6.xpm"
#include "../sprites/SideRightAttack_7.xpm"

#include "../sprites/Damage_0.xpm"

#include "../sprites/Bar_0.xpm"
#include "../sprites/Bar_1.xpm"
#include "../sprites/Life_0.xpm"
#include "../sprites/Life_1.xpm"
#include "../sprites/Life_2.xpm"

extern unsigned int sprite_timer_counter;
extern unsigned int sprite_attack_counter;
bool blink = false;
bool attack = false;
extern bool isPlayerIdle;

character_t* character;

static bool w_key_pressed = false;
static bool a_key_pressed = false;
static bool s_key_pressed = false;
static bool d_key_pressed = false;

character_t* character_init() {
character = malloc(sizeof(*character));

    character->pos_x = 200;
    character->pos_y = 200;
    character->speed = 3;
    character->idle = true;
    character->damaged = false;
    character->side = 1;
    character->hitbox_height = 32;
    character->hitbox_width = 26;
    character->life = 4;
    
    xpm_image_t spriteIt; 

    // Idle Character Sprites
    xpm_load(FrontIdle_00_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[0] = spriteIt;
    xpm_load(FrontIdle_01_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[1] = spriteIt;
    xpm_load(FrontIdle_02_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[2] = spriteIt;
    xpm_load(FrontIdle_03_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[3] = spriteIt;
    xpm_load(FrontIdle_04_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[4] = spriteIt;
    xpm_load(FrontIdle_05_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[5] = spriteIt;
    xpm_load(FrontIdle_06_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[6] = spriteIt;
    xpm_load(FrontIdle_07_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[7] = spriteIt;
    xpm_load(FrontIdle_08_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[8] = spriteIt;
    xpm_load(FrontIdle_09_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[9] = spriteIt;
    xpm_load(FrontIdle_10_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[10] = spriteIt;
    xpm_load(FrontIdle_11_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontIdle[11] = spriteIt;

    xpm_load(BackIdle_00_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[0] = spriteIt;
    xpm_load(BackIdle_01_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[1] = spriteIt;
    xpm_load(BackIdle_02_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[2] = spriteIt;
    xpm_load(BackIdle_03_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[3] = spriteIt;
    xpm_load(BackIdle_04_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[4] = spriteIt;
    xpm_load(BackIdle_05_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[5] = spriteIt;
    xpm_load(BackIdle_06_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[6] = spriteIt;
    xpm_load(BackIdle_07_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[7] = spriteIt;
    xpm_load(BackIdle_08_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[8] = spriteIt;
    xpm_load(BackIdle_09_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[9] = spriteIt;
    xpm_load(BackIdle_10_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[10] = spriteIt;
    xpm_load(BackIdle_11_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackIdle[11] = spriteIt;

    xpm_load(SideLeftIdle_00_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[0] = spriteIt;
    xpm_load(SideLeftIdle_01_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[1] = spriteIt;
    xpm_load(SideLeftIdle_02_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[2] = spriteIt;
    xpm_load(SideLeftIdle_03_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[3] = spriteIt;
    xpm_load(SideLeftIdle_04_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[4] = spriteIt;
    xpm_load(SideLeftIdle_05_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[5] = spriteIt;
    xpm_load(SideLeftIdle_06_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[6] = spriteIt;
    xpm_load(SideLeftIdle_07_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[7] = spriteIt;
    xpm_load(SideLeftIdle_08_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[8] = spriteIt;
    xpm_load(SideLeftIdle_09_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[9] = spriteIt;
    xpm_load(SideLeftIdle_10_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[10] = spriteIt;
    xpm_load(SideLeftIdle_11_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftIdle[11] = spriteIt;

    xpm_load(SideRightIdle_00_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[0] = spriteIt;
    xpm_load(SideRightIdle_01_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[1] = spriteIt;
    xpm_load(SideRightIdle_02_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[2] = spriteIt;
    xpm_load(SideRightIdle_03_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[3] = spriteIt;
    xpm_load(SideRightIdle_04_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[4] = spriteIt;
    xpm_load(SideRightIdle_05_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[5] = spriteIt;
    xpm_load(SideRightIdle_06_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[6] = spriteIt;
    xpm_load(SideRightIdle_07_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[7] = spriteIt;
    xpm_load(SideRightIdle_08_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[8] = spriteIt;
    xpm_load(SideRightIdle_09_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[9] = spriteIt;
    xpm_load(SideRightIdle_10_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[10] = spriteIt;
    xpm_load(SideRightIdle_11_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightIdle[11] = spriteIt;

    // Attack Character Sprites
    xpm_load(FrontAttack_0_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[0] = spriteIt;
    xpm_load(FrontAttack_1_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[1] = spriteIt;
    xpm_load(FrontAttack_2_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[2] = spriteIt;
    xpm_load(FrontAttack_3_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[3] = spriteIt;
    xpm_load(FrontAttack_4_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[4] = spriteIt;
    xpm_load(FrontAttack_5_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[5] = spriteIt;
    xpm_load(FrontAttack_6_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[6] = spriteIt;
    xpm_load(FrontAttack_7_xpm,XPM_8_8_8_8,&spriteIt);
    character->FrontAttack[7] = spriteIt;

    xpm_load(BackAttack_0_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[0] = spriteIt;
    xpm_load(BackAttack_1_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[1] = spriteIt;
    xpm_load(BackAttack_2_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[2] = spriteIt;
    xpm_load(BackAttack_3_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[3] = spriteIt;
    xpm_load(BackAttack_4_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[4] = spriteIt;
    xpm_load(BackAttack_5_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[5] = spriteIt;
    xpm_load(BackAttack_6_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[6] = spriteIt;
    xpm_load(BackAttack_7_xpm,XPM_8_8_8_8,&spriteIt);
    character->BackAttack[7] = spriteIt;

    xpm_load(SideLeftAttack_0_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[0] = spriteIt;
    xpm_load(SideLeftAttack_1_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[1] = spriteIt;
    xpm_load(SideLeftAttack_2_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[2] = spriteIt;
    xpm_load(SideLeftAttack_3_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[3] = spriteIt;
    xpm_load(SideLeftAttack_4_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[4] = spriteIt;
    xpm_load(SideLeftAttack_5_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[5] = spriteIt;
    xpm_load(SideLeftAttack_6_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[6] = spriteIt;
    xpm_load(SideLeftAttack_7_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideLeftAttack[7] = spriteIt;

    xpm_load(SideRightAttack_0_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[0] = spriteIt;
    xpm_load(SideRightAttack_1_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[1] = spriteIt;
    xpm_load(SideRightAttack_2_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[2] = spriteIt;
    xpm_load(SideRightAttack_3_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[3] = spriteIt;
    xpm_load(SideRightAttack_4_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[4] = spriteIt;
    xpm_load(SideRightAttack_5_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[5] = spriteIt;
    xpm_load(SideRightAttack_6_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[6] = spriteIt;
    xpm_load(SideRightAttack_7_xpm,XPM_8_8_8_8,&spriteIt);
    character->SideRightAttack[7] = spriteIt;

    xpm_load(Bar_0_xpm,XPM_8_8_8_8,&spriteIt);
    Bars[0] = spriteIt;
    xpm_load(Bar_1_xpm,XPM_8_8_8_8,&spriteIt);
    Bars[1] = spriteIt;

    xpm_load(Life_0_xpm,XPM_8_8_8_8,&spriteIt);
    Life[0] = spriteIt;
    xpm_load(Life_1_xpm,XPM_8_8_8_8,&spriteIt);
    Life[1] = spriteIt;
    xpm_load(Life_2_xpm,XPM_8_8_8_8,&spriteIt);
    Life[2] = spriteIt;

    xpm_load(Damage_0_xpm,XPM_8_8_8_8,&spriteIt);
    Damage = spriteIt;


    character->sprite = character->FrontIdle[0];
    character->IdleCounter = 0;


    return character;
}

void character_refresh() {
    if (w_key_pressed && character->pos_y >= 0 &&  !detect_colision_up(character)) {
        character->pos_y -= character->speed; 
    }
    if (a_key_pressed && character->pos_x >= 0 && !detect_colision_left(character)) {
        character->pos_x -= character->speed;
    }
    if (s_key_pressed && character->pos_y <= get_YResolution() - 32 && !detect_colision_down(character)) {
        character->pos_y += character->speed;
    }
    if (d_key_pressed && character->pos_x <= get_XResolution() - 32 && !detect_colision_right(character)) {
        character->pos_x += character->speed;
    }

    for(int j = 0; j < 10; j++){
    if (EnemyInMap[j]) {
        if ((  (( ((EnemyInfo[j] -> hitbox[0]) <= (character -> pos_x + 3)) && ((character -> pos_x + 3) <= ((EnemyInfo[j] -> hitbox[2]))) ) || ( ((EnemyInfo[j] -> hitbox[0]) <= (character -> pos_x + 29)) && ((character -> pos_x + 29) <= ((EnemyInfo[j] -> hitbox[2]))) )) && (( ((EnemyInfo[j] -> hitbox[1]) <= (character -> pos_y)) && ((character -> pos_y) <= ((EnemyInfo[j] -> hitbox[3]))) ) || ( ((EnemyInfo[j] -> hitbox[1]) <= (character -> pos_y + 32)) && ((character -> pos_y + 32) <= ((EnemyInfo[j] -> hitbox[3]) )) ))  ) && !(character->damaged) ){
            character-> damaged = true;
            character-> damaged_counter = 10;
            character-> damaged_blink = true;
            character-> life--;
            EnemyInfo[j] -> pos_x = EnemyInfo[j] -> prev_pos_x;
            EnemyInfo[j] -> pos_y = EnemyInfo[j] -> prev_pos_y;
        }
    }
    }

    switch (character->side){
        case 0:
        if (!(attack)){
            character-> sprite = character->BackIdle[character->IdleCounter];
        }
        if (attack){
            character-> sprite = character->BackAttack[character->AttackCounter];
        }
        break; 

        case 1:
        if (!(attack)){
            character-> sprite = character->FrontIdle[character->IdleCounter];
        }
        if (attack){
            character-> sprite = character->FrontAttack[character->AttackCounter];
        }
        break; 

        case 2:
        if (!(attack)){
            character-> sprite = character->SideLeftIdle[character->IdleCounter];
        }
        if (attack){
            character-> sprite = character->SideLeftAttack[character->AttackCounter];
        }
        break; 

        case 3:
        if (!(attack)){
            character-> sprite = character->SideRightIdle[character->IdleCounter];
        }
        if (attack){
            character-> sprite = character->SideRightAttack[character->AttackCounter];
        }
        break; 

    }
}

void character_update(uint8_t* scancode_array) {
    //printf("%x,%x\n",scancode_array[0],scancode_array[1]);
    static uint8_t last_code_trans = 0;

    if (scancode_array[0] == W_KEY_CODE_MAKE) {
        if (last_code_trans != W_KEY_CODE_MAKE) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        w_key_pressed = true;
        character->side = 0;
    }
    else if (scancode_array[0] == A_KEY_CODE_MAKE) {
        if (last_code_trans != A_KEY_CODE_MAKE) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        a_key_pressed = true;
        character->side = 2;
    }
    else if (scancode_array[0] == S_KEY_CODE_MAKE) {
        if (last_code_trans != S_KEY_CODE_MAKE) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        s_key_pressed = true;
        character->side = 1;
    }
    else if (scancode_array[0] == D_KEY_CODE_MAKE) {
        if (last_code_trans != D_KEY_CODE_MAKE) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        d_key_pressed = true;
        character->side = 3;
    }
    else if (scancode_array[0] == W_KEY_CODE_BREAK) {
        if (last_code_trans != W_KEY_CODE_BREAK) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        w_key_pressed = false;
    }
    else if (scancode_array[0] == A_KEY_CODE_BREAK) {
        if (last_code_trans != A_KEY_CODE_BREAK) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        a_key_pressed = false;
    }
    else if (scancode_array[0] == S_KEY_CODE_BREAK) {
        if (last_code_trans != S_KEY_CODE_BREAK) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        s_key_pressed = false;
    }
    else if (scancode_array[0] == D_KEY_CODE_BREAK) {
        if (last_code_trans != D_KEY_CODE_BREAK) {
            serial_port_add_to_transmit_queue(scancode_array[0]);    
        }
        d_key_pressed = false;
    }
    last_code_trans = scancode_array[0];
}

void character_update_rec(uint8_t scancode) {
    //printf("%x,%x\n",scancode_array[0],scancode_array[1]);

    if (scancode == W_KEY_CODE_MAKE) {
        w_key_pressed = true;
        character->side = 0;
    }
    else if (scancode == A_KEY_CODE_MAKE) {
        a_key_pressed = true;
        character->side = 2;
    }
    else if (scancode == S_KEY_CODE_MAKE) {
        s_key_pressed = true;
        character->side = 1;
    }
    else if (scancode == D_KEY_CODE_MAKE) {
        d_key_pressed = true;
        character->side = 3;
    }
    else if (scancode == W_KEY_CODE_BREAK) {
        w_key_pressed = false;
    }
    else if (scancode == A_KEY_CODE_BREAK) {
        a_key_pressed = false;
    }
    else if (scancode == S_KEY_CODE_BREAK) {
        s_key_pressed = false;
    }
    else if (scancode == D_KEY_CODE_BREAK) {
        d_key_pressed = false;
    }
}

void character_draw() {
    uint32_t* map = (uint32_t*) character->sprite.bytes;

    for(int i = 0; i < character->sprite.width; i++) {
        for (int j = 0; j < character->sprite.height; j++) {
            pixel_set_color(*(map + i + j*character->sprite.width),character->pos_x+i,character->pos_y+j);
        }
    } 

} 


void character_delete() {
    free(character);
}


void character_bobbing() {
    if (character->idle){
    switch (character->side){
        case 0:
        if (character->IdleCounter < 11){
            character-> sprite = character->BackIdle[11];
            character->IdleCounter = 11;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->BackIdle[0];
            character->IdleCounter = 0;
        }
        break;

        case 1:
        if (character->IdleCounter < 11){
            character-> sprite = character->FrontIdle[11];
            character->IdleCounter = 11;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->FrontIdle[0];
            character->IdleCounter = 0;
        }
        break;

        case 2:
        if (character->IdleCounter < 11){
            character-> sprite = character->SideLeftIdle[11];
            character->IdleCounter = 11;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->SideLeftIdle[0];
            character->IdleCounter = 0;
        }
        break;

        case 3:
        if (character->IdleCounter < 11){
            character-> sprite = character->SideRightIdle[11];
            character->IdleCounter = 11;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->SideRightIdle[0];
            character->IdleCounter = 0;
        }
        break;

    }
    }
}


void character_idle( bool IsItIdle){
    if (IsItIdle) { 
        character->idle = true;
    }
    else {character->idle = false;}
}

void character_IdleCounter(int count){
    character->IdleCounter = count;
}

void character_AttackCounter(int count){
    character->AttackCounter = count;
}


int character_getSide(){
    return character->side;
}


void character_blink(){
    if (character->idle){
    switch (character->side){
        case 0:
        if (character->IdleCounter < 11){
            character-> sprite = character->BackIdle[(character->IdleCounter) + 1];
            (character->IdleCounter)++;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->BackIdle[0];
            character_IdleCounter(0);
            blink = false;
            sprite_timer_counter = 1;
        }
        break;

        case 1:
        if (character->IdleCounter < 11){
            character-> sprite = character->FrontIdle[(character->IdleCounter) + 1];
            (character->IdleCounter)++;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->FrontIdle[0];
            character_IdleCounter(0);
            blink = false;
            sprite_timer_counter = 1;
        }
        break;

        case 2:
        if (character->IdleCounter < 11){
            character-> sprite = character->SideLeftIdle[(character->IdleCounter) + 1];
            (character->IdleCounter)++;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->SideLeftIdle[0];
            character_IdleCounter(0);
            blink = false;
            sprite_timer_counter = 1;
        }
        break;

        case 3:
        if (character->IdleCounter < 11){
            character-> sprite = character->SideRightIdle[(character->IdleCounter) + 1];
            (character->IdleCounter)++;
        }
        else if (character->IdleCounter == 11){
            character-> sprite = character->SideRightIdle[0];
            character_IdleCounter(0);
            blink = false;
            sprite_timer_counter = 1;
        }
        break;

    }
    }
}

void character_attack(){
    if (attack){
    switch (character->side){
        case 0:
        if (character->AttackCounter < 7){
            character->sprite = character->BackAttack[(character->AttackCounter) + 1];
            (character->AttackCounter)++;
        }
        else if (character->AttackCounter == 7){
            character->sprite = character->BackAttack[0];
            character_AttackCounter(0);
            sprite_attack_counter = 1;
            attack = false;
        }
        break;

        case 1:
        if (character->AttackCounter < 7){
            character->sprite = character->FrontAttack[(character->AttackCounter) + 1];
            (character->AttackCounter)++;
        }
        else if (character->AttackCounter == 7){
            character->sprite = character->FrontAttack[0];
            character_AttackCounter(0);
            sprite_attack_counter = 1;
            attack = false;
        }
        break;

        case 2:
        if (character->AttackCounter < 7){
            character->sprite = character->SideLeftAttack[(character->AttackCounter) + 1];
            (character->AttackCounter)++;
        }
        else if (character->AttackCounter == 7){
            character-> sprite = character->SideLeftAttack[0];
            character_AttackCounter(0);
            sprite_attack_counter = 1;
            attack = false;
        }
        break;

        case 3:
        if (character->AttackCounter < 7){
            character->sprite = character->SideRightAttack[(character->AttackCounter) + 1];
            (character->AttackCounter)++;
        }
        else if (character->AttackCounter == 7){
            character->sprite = character->SideRightAttack[0];
            character_AttackCounter(0);
            sprite_attack_counter = 1;
            attack = false;
        }
        break;

    }
    }
}



void print_bars(){
    uint32_t* map = (uint32_t*) Bars[0].bytes;

    for(int i = 0; i < Bars[0].width; i++) {
        for (int j = 0; j < Bars[0].height; j++) {
            pixel_set_color(*(map + i + j*Bars[0].width),get_XResolution() - 640 + i, get_YResolution() - 640 + j);
        }
    }

    uint32_t* map2 = (uint32_t*) Bars[1].bytes;

    for(int i = 0; i < Bars[1].width; i++) {
        for (int j = 0; j < Bars[1].height; j++) {
            pixel_set_color(*(map2 + i + j*Bars[1].width),i,get_YResolution() - 640 + j);
        }
    } 
}



void print_life(){
    if(character->life >= 4){
        uint32_t* map = (uint32_t*) Life[0].bytes;

        for(int i = 0; i < Life[0].width; i++) {
        for (int j = 0; j < Life[0].height; j++) {
            pixel_set_color(*(map + i + j*Life[0].width),get_XResolution() - 310 + i, get_YResolution() - 165 + j);
        }
    }
    }
    if(character->life == 3){
        uint32_t* map = (uint32_t*) Life[1].bytes;

        for(int i = 0; i < Life[1].width; i++) {
        for (int j = 0; j < Life[1].height; j++) {
            pixel_set_color(*(map + i + j*Life[1].width),get_XResolution() - 310 + i, get_YResolution() - 165 + j);
        }
    }
    }


    if(character->life >= 2){
        uint32_t* map = (uint32_t*) Life[0].bytes;

        for(int i = 0; i < Life[0].width; i++) {
        for (int j = 0; j < Life[0].height; j++) {
            pixel_set_color(*(map + i + j*Life[0].width),get_XResolution() - 165 + i, get_YResolution() - 165 + j);
        }
    }
    }
    if(character->life == 1){
        uint32_t* map = (uint32_t*) Life[1].bytes;

        for(int i = 0; i < Life[1].width; i++) {
        for (int j = 0; j < Life[1].height; j++) {
            pixel_set_color(*(map + i + j*Life[1].width),get_XResolution() - 165 + i, get_YResolution() - 165 + j);
        }
    }
    }
    if(character->life == 0){
        uint32_t* map = (uint32_t*) Life[2].bytes;

        for(int i = 0; i < Life[2].width; i++) {
        for (int j = 0; j < Life[2].height; j++) {
            pixel_set_color(*(map + i + j*Life[2].width),get_XResolution() - 165 + i, get_YResolution() - 165 + j);
        }
    }
    }
}

