#include <lcom/lcf.h>

#include "../include/event_manager.h"
#include "../include/video_card.h"
#include "../include/crosshair.h"
#include "../include/character.h"
#include "../include/terrain.h"
#include "../include/button.h"
#include "../include/kbd.h"
#include "../include/key_map.h"
#include "../include/clock.h"
#include "../include/queue.h"
#include "../include/serial_port.h"
#include "../include/projectile.h"
#include "../include/enemy.h"

extern uint8_t scancode_array[2];

extern queue_t* recieved_data_queue;
extern queue_t* transmit_data_queue;

extern bool isPlayerIdle;
extern bool blink;
extern bool attack;

extern character_t* character;

extern unsigned int timer_counter;
extern unsigned int sprite_timer_counter;
extern unsigned int sprite_attack_counter;

//state machine that depending on the event and the current state returns the new state 
void run_event_manager(enum State* curr_state, enum Event event, bool* state_loaded) {
    switch(*curr_state) {
        case LOAD: 
            if (event == INIT_COMPLETE) {
                *state_loaded = false;
                *curr_state = MENU;
                return;
            }
            else {
                return;
            }
            break;
        case MENU: 
            if (event == START_GAME) {
                *state_loaded = false;
                *curr_state = GAME;
                return;
            }
            else if (event == EXIT_GAME){
                *curr_state = EXIT;
                return;
            }
            else {
                return;
            }
            break;

        case GAME: 
            if (event == PAUSE_GAME ) {
                *state_loaded = false;
                *curr_state = PAUSE;
                return;
            }
            else if (event == EXIT_GAME) {
                *curr_state = EXIT;
                return;
            }
            else {
                return;
            }
            break;

        case PAUSE:
            if (event == CONTINUE_GAME) {
                *state_loaded = false;
                *curr_state = GAME_C;
                return;
            } 
            else if (event == EXIT_GAME) {
                *curr_state = EXIT;
                return;
            }
            break;

        case GAME_C: 
            if (event == PAUSE_GAME ) {
                *state_loaded = false;
                *curr_state = PAUSE;
                return;
            }
            else if (event == EXIT_GAME) {
                *curr_state = EXIT;
                return;
            }
            else {
                return;
            }
            break;

        case SPECTATE_WAIT: 
            if (event == INIT_COMPLETE) {
                *state_loaded = false;
                *curr_state = SPECTATE_WAIT;
            }
            else if (event == START_REC) {
                *state_loaded = false;
                *curr_state = SPECTATE_RUNNING;
            }
            else if (event == EXIT_GAME) {
                *curr_state = EXIT; 
            }
            else {
                return;
            }

        case SPECTATE_RUNNING: 
            if (event == EXIT_GAME) {
                *curr_state = EXIT;
            }

        default: 
            return;
    }
}

//function used to load a specific state
int load_state(enum State curr_state) {
    switch (curr_state) {
        case MENU:
            buttons_init();
            clock_init(960,15,32,15);
            logo_init();
            create_button(447,537,MENU_ST);
            create_button(447,675,MENU_EXT);
            return 0;

        case GAME: 
            clear_buttons();
            clock_delete();
            logo_delete();
            crosshair_change_ingame();
            uint8_t seed = generate_terrain();
            serial_port_add_to_transmit_queue(seed);
            character_init();
            enemyStart();
            projectiles_start();
            serial_port_transmit();

            return 0;

        case PAUSE: 
            crosshair_change_menu();
            buttons_init();
            clock_init(928,15,32,15);
            logo_init();
            create_button(447,537,MENU_CONT);
            create_button(447,675,MENU_EXT);
            return 0;

        case GAME_C: 
            crosshair_change_ingame();
            clear_buttons();
            clock_delete();
            return 0;
        
        case SPECTATE_WAIT: 
            printf("Waiting for game to start\n");
            return 0;

        case SPECTATE_RUNNING: {  
            uint8_t seed_rec = serial_port_read_recieved_queue();
            set_graphics_card_mode(0x14c);
            generate_terrain_seed(seed_rec);
            character_init();
            projectiles_start();
            return 0;
        }


        case LOAD: 
            return 0;
        case EXIT: 
            return 0;

        default: 
            return 0;
    }
}

//function used to manage interrupts depending on the state of the game
//returns an event or a NO_EVENT 
enum Event manage_interrupt(enum State curr_state, enum Device device) {
    static button_t* button = NULL; //used to check colision with pixel
    static button_t* highlighted_button = NULL;
    static bool highlighted_crosshair = false;
    static bool just_unhighlighted_crosshair = true;

    switch (device) {
        case TIMER: 
            if (curr_state == MENU || curr_state == PAUSE) {
                draw_logo();
                draw_buttons();
                button = check_colision_with_crosshair();
                display_clock();
                display_date();
                screen_refresh();
                if (timer_counter % 10 == 0) {
                    logo_update();
                }
            }
            else if (curr_state == GAME) {
                if (!empty_queue(transmit_data_queue) && timer_counter % 2 == 0) {
                    serial_port_transmit();
                }
                
                //&& !(character->damaged_blink)

                if(!(isPlayerIdle)){
                    character_IdleCounter(0);
                    attack = true;
                }
                if(!(isPlayerIdle) && (timer_counter % 15 == 0)){
                    projectile_create();
                }
                if (timer_counter % 4 == 0){
                    projectile_bobbing();
                    enemyAnim();
                    projectile_collide_anim();
                }
                
                if ((attack) && (sprite_attack_counter % 4 == 0)){
                    character_attack();
                    serial_port_add_to_transmit_queue(START_ATTACK);
                }
                if((blink) && (sprite_timer_counter % 4 == 0) && (!(attack))){
                    character_blink();
                }
                if ((sprite_timer_counter % 300 == 0) && (!(attack))){
                    blink = true;
                    character_IdleCounter(0);
                }            
                if (!(blink) && (sprite_timer_counter % 30 == 0) && (!(attack))){
                    character_bobbing();
                }
                
                character_refresh();
                projectile_refresh();
                enemy_refresh();
                projectile_check_collision();
                enemyCheckCollision();
                if(character->damaged && (timer_counter % 15 <= 6) && character->damaged_blink){
                    character->sprite = Damage;
                    character-> damaged_blink = false;
                }
                else if(character->damaged && (timer_counter % 15 >= 7) && !(character->damaged_blink)){
                    character-> damaged_blink = true;
                }
                if(character->damaged && (timer_counter % 15 == 14) && (character->damaged_blink)){
                    character -> damaged_counter--;
                }
                if(character->damaged_counter==0){
                    character->damaged = false;
                    character->damaged_blink = false;
                }
                terrain_draw();
                draw_walls();
                enemyDraw();
                character_draw();
                projectile_draw();
                print_bars();
                print_life();
                screen_refresh();
                if (character->life == 0) {
                    printf("GAME OVER\n");
                    return EXIT_GAME;
                }
                return NO_EVENT;
            }
            else if (curr_state == GAME_C) {
                if (!empty_queue(transmit_data_queue) && timer_counter % 2 == 0) {
                    serial_port_transmit();
                }
                if(!(isPlayerIdle)){
                    character_IdleCounter(0);
                    attack = true;
                }
                if(!(isPlayerIdle) && (timer_counter % 15 == 0)){
                    projectile_create();
                }
                if (timer_counter % 4 == 0){
                    projectile_bobbing();
                    enemyAnim();
                    projectile_collide_anim();
                }
                if (timer_counter % 4 == 0){
                    projectile_collide_anim();
                }
                if ((attack) && (sprite_attack_counter % 4 == 0)){
                    character_attack();
                    serial_port_add_to_transmit_queue(START_ATTACK);
                }
                if((blink) && (sprite_timer_counter % 4 == 0) && (!(attack))){
                    character_blink();
                }
                if ((sprite_timer_counter % 300 == 0) && (!(attack))){
                    blink = true;
                    character_IdleCounter(0);
                }            
                if (!(blink) && (sprite_timer_counter % 30 == 0) && (!(attack))){
                    character_bobbing();
                }

                if(character->damaged && (timer_counter % 15 == 0) && character->damaged_blink){
                    character->sprite = Damage;
                    character-> damaged_blink = false;
                }
                else if(character->damaged && (timer_counter % 15 == 0) && !(character->damaged_blink)){
                    character-> damaged_blink = true;
                    character -> damaged_counter--;
                }
                if(character->damaged_counter==0){
                    character->damaged = false;
                    character->damaged_blink = false;
                }

                character_refresh();
                projectile_refresh();
                enemy_refresh();
                projectile_check_collision();
                enemyCheckCollision();
                terrain_draw();
                draw_walls();
                enemyDraw();
                character_draw();
                projectile_draw();
                print_bars();
                print_life();
                screen_refresh();
                if (character->life == 0) {
                    printf("GAME OVER\n");
                    return EXIT_GAME;
                }
                return NO_EVENT;
            }
            else if (curr_state == SPECTATE_RUNNING) {
                if (!empty_queue(recieved_data_queue)) {
                    manage_comunication(serial_port_read_recieved_queue());
                }
                if(!(isPlayerIdle)){
                    character_IdleCounter(0);
                    attack = true;
                }
                if(!(isPlayerIdle) && (timer_counter % 30 == 0)){
                    projectile_create();
                }
                if (timer_counter % 4 == 0){
                    projectile_bobbing();
                }
                if (timer_counter % 4 == 0){
                    projectile_collide_anim();
                }
                if ((attack) && (sprite_attack_counter % 4 == 0)){
                    character_attack();
                }
                if((blink) && (sprite_timer_counter % 4 == 0) && (!(attack))){
                    character_blink();
                }
                if ((sprite_timer_counter % 300 == 0) && (!(attack))){
                    blink = true;
                    character_IdleCounter(0);
                }            
                if (!(blink) && (sprite_timer_counter % 30 == 0) && (!(attack))){
                    character_bobbing();
                }
                character_refresh();
                projectile_refresh();
                projectile_check_collision();
                terrain_draw();
                draw_walls();
                
                character_draw();
                screen_refresh_no_crosshair();
            }
            return NO_EVENT;

        case MOUSE: 
            if (curr_state == MENU || curr_state == PAUSE) {
                just_unhighlighted_crosshair = false;
                if (get_lb_pressed() && !highlighted_crosshair) {
                    highlight_crosshair();
                    highlighted_crosshair = true;
                }
                else if (highlighted_crosshair && !get_lb_pressed()) {
                    unhighlight_crosshair();
                    highlighted_crosshair = false;
                    just_unhighlighted_crosshair = true;
                }
                if (button != NULL && highlighted_button == NULL) {
                    button_highlight(button);
                    highlighted_button = button;
                }
                else if (button == NULL && highlighted_button != NULL){
                    button_unhighlight(highlighted_button);
                    highlighted_button = NULL;
                }
                if (highlighted_button != NULL && !get_lb_pressed() && just_unhighlighted_crosshair) {
                    return run_button_event(highlighted_button);
                }
                return NO_EVENT;
            }
            else if (curr_state == GAME || curr_state == GAME_C) {
                // static bool prev_idle = false;
                // if (isPlayerIdle && !prev_idle) {
                //     serial_port_add_to_transmit_queue(STOP_ATTACK);
                //     prev_idle = true;
                // }
                // else if (!isPlayerIdle && prev_idle){
                //     serial_port_add_to_transmit_queue(START_ATTACK);
                //     prev_idle = false;
                // }
                character_idle(isPlayerIdle);
                return NO_EVENT;
            }
            return NO_EVENT;

        case KEYBOARD: 
            if (curr_state == GAME) {
                character_update(scancode_array);
                if (scancode_array[0] == ESC_BREAK_CODE) {
                    return PAUSE_GAME;
                }
                return NO_EVENT;
            }
            else if (curr_state == GAME_C) {
                character_update(scancode_array);
                if (scancode_array[0] == ESC_BREAK_CODE) {
                    return PAUSE_GAME;
                }
                return NO_EVENT;
            }
            else if(curr_state == SPECTATE_WAIT) {
                if (scancode_array[0] == ESC_BREAK_CODE) {
                    return EXIT_GAME;
                }
                return NO_EVENT;
            }
            else if (curr_state == SPECTATE_RUNNING) {
                if (scancode_array[0] == ESC_BREAK_CODE) {
                    vg_exit();
                    free_mem();
                    free_second_buf();
                    return EXIT_GAME;
                }
                return NO_EVENT;
            }

        case RTC: 
            if (curr_state == MENU || curr_state == PAUSE) {
                clock_update();
            }
            return NO_EVENT;

        case SERIAL_PORT: 
            if (curr_state == GAME) {
 
                return NO_EVENT;
            }
            if (curr_state == SPECTATE_WAIT) {
                if (!empty_queue(recieved_data_queue)) {
                    return START_REC;
                }
                return NO_EVENT;
            }
            // else if (curr_state == SPECTATE_RUNNING) {
            //     if (!empty_queue(recieved_data_queue)) {
                    
            //     }
            // }

        default:
            return NO_EVENT;
    }
}


void manage_comunication(uint8_t data_received) {
    switch(data_received) {
        case W_KEY_CODE_BREAK: 
            character_update_rec(data_received);
            break;

        case W_KEY_CODE_MAKE: 
            character_update_rec(data_received);
            break;

        case A_KEY_CODE_MAKE: 
            character_update_rec(data_received);
            break;

        case A_KEY_CODE_BREAK: 
            character_update_rec(data_received);
            break;

        case S_KEY_CODE_BREAK: 
            character_update_rec(data_received);
            break;

        case S_KEY_CODE_MAKE:
            character_update_rec(data_received);
            break;

        case D_KEY_CODE_BREAK: 
            character_update_rec(data_received);
            break;            

        case D_KEY_CODE_MAKE: 
            character_update_rec(data_received);
            break;

        case START_ATTACK: 
            attack = true;
            break;

        case STOP_ATTACK: 
            attack = false;
            break;

        default: 
            return;
    }
}

