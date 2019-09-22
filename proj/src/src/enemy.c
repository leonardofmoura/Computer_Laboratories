#include <lcom/lcf.h>
#include "../include/crosshair.h"
#include "../include/mouse.h"
#include "../include/kbd.h"
#include "../include/video_card.h"
#include "../include/character.h"
#include "../include/key_map.h"
#include "../include/terrain.h"
#include "../include/enemy.h"
#include <math.h>

#include "../sprites/EnemyFront_0.xpm"
#include "../sprites/EnemyFront_1.xpm"
#include "../sprites/EnemyBack_0.xpm"
#include "../sprites/EnemySideLeft_0.xpm"
#include "../sprites/EnemySideLeft_1.xpm"
#include "../sprites/EnemySideRight_0.xpm"
#include "../sprites/EnemySideRight_1.xpm"

#include "../sprites/Damage_0.xpm"


extern character_t* character;
extern crosshair_t* crosshair;
extern wall_t* walls[30];


void enemyStart(){
    for (int i = 0; i < 10; i++){
        EnemyInMap[i] = false;
    }

    xpm_image_t EnemySprite;

    xpm_load(EnemyFront_0_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemyFront[0] = EnemySprite;
    xpm_load(EnemyFront_1_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemyFront[1] = EnemySprite;
    xpm_load(EnemyBack_0_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemyBack[0] = EnemySprite;
    xpm_load(EnemyBack_0_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemyBack[1] = EnemySprite;
    xpm_load(EnemySideLeft_0_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemySideLeft[0] = EnemySprite;
    xpm_load(EnemySideLeft_1_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemySideLeft[1] = EnemySprite;
    xpm_load(EnemySideRight_0_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemySideRight[0] = EnemySprite;
    xpm_load(EnemySideRight_1_xpm,XPM_8_8_8_8,&EnemySprite);
    EnemySideRight[1] = EnemySprite;

    xpm_load(Damage_0_xpm,XPM_8_8_8_8,&EnemySprite);
    Damage = EnemySprite;

    for (int j = 0; j < 10; j++){
        enemyCreate();
    }


}

void enemyCreate(){
    enemy_t* enemy_num;
    enemy_num = malloc(sizeof(enemy_t));
    for (int i = 0; i < 10; i++){
        if (!(EnemyInMap[i])){
        EnemyInMap[i] = true;

        enemy_num -> speed = (rand() % 2) + 2;
        enemy_num -> animFrame = 0;
        enemy_num -> sprite = EnemyFront[0];
        enemy_num -> side = 1;
        enemy_num -> life = 10;
        for (int n = 0; n < 1; n++) {
            int randX = ((rand()*rand()) % 35) * 32;
            int randY = ((rand()*rand())  % 26) * 32;
            bool passa = true;
            for (int j = 0; j < 30; j++){
                if (((walls[j]->coord_x) == randX) && ((walls[j]->coord_y) == randY)){
                    n--;
                    passa = false;
                }
            }
            if (passa){
                enemy_num -> pos_x = randX;
                enemy_num -> pos_y = randY;
                enemy_num -> hitbox[0] = randX;
                enemy_num -> hitbox[1] = randY;
                enemy_num -> hitbox[2] = randX + 32;
                enemy_num -> hitbox[3] = randY + 32;
            }
        }

        EnemyInfo[i] = enemy_num;

        break;
        }
    }

}

void enemy_refresh(){
    for(int h = 0; h < 10; h++){
        if(EnemyInMap[h]){
            if(EnemyInfo[h] -> life <= 0){
                EnemyInMap[h] = false;
                break;
            }
            double Dx = 0;
            double Dy = 0;
            Dx = (character->pos_x + 16) - (EnemyInfo[h] -> pos_x + 16);
            Dy = (character->pos_y + 16) - (EnemyInfo[h] -> pos_y + 16);
            double Dlength = sqrt(Dx*Dx + Dy*Dy);

            if(abs(Dx) > abs(Dy)){
                if (Dx < 0){
                    EnemyInfo[h]-> side =  2;
                }
                if (Dx > 0){
                    EnemyInfo[h]-> side = 3;
                }
            }
            else if(abs(Dx) < abs(Dy)){
                if (Dy < 0){
                    EnemyInfo[h]-> side =  0;
                }
                if (Dy > 0){
                    EnemyInfo[h]-> side = 1;
                }
            }
            if(Dx != 0){
                Dx = Dx / Dlength;
            }
            if(Dy != 0){
                Dy = Dy / Dlength;
            }

            switch(EnemyInfo[h] -> side){
                case 0:
                EnemyInfo[h] -> sprite = EnemyBack[EnemyInfo[h] -> animFrame];
                break;
                case 1:
                EnemyInfo[h] -> sprite = EnemyFront[EnemyInfo[h] -> animFrame];
                break;
                case 2:
                EnemyInfo[h] -> sprite = EnemySideLeft[EnemyInfo[h] -> animFrame];
                break;
                case 3:
                EnemyInfo[h] -> sprite = EnemySideRight[EnemyInfo[h] -> animFrame];
                break;
            }

            EnemyInfo[h]->prev_pos_x = EnemyInfo[h]->pos_x;
            EnemyInfo[h]->prev_pos_y = EnemyInfo[h]->pos_y;
            EnemyInfo[h]->pos_x += Dx * EnemyInfo[h]->speed;
            EnemyInfo[h]->pos_y += Dy * EnemyInfo[h]->speed;
            EnemyInfo[h]->hitbox[0] =  EnemyInfo[h]->pos_x;
            EnemyInfo[h]->hitbox[1] =  EnemyInfo[h]->pos_y;
            EnemyInfo[h]->hitbox[2] =  EnemyInfo[h]->pos_x + 32;
            EnemyInfo[h]->hitbox[3] =  EnemyInfo[h]->pos_y + 32;
        }
    }
}

void enemyCheckCollision(){
    for (int i = 0; i < 10; i++){
        if(EnemyInMap[i]){
            // other enemies
            for(int j = 0; j < 10; j++){
                if (j == i) {
                    break;
                }
                // EnemyInfo
                if (  (( ((EnemyInfo[j] -> pos_x) <= (EnemyInfo[i] -> hitbox[0])) && ((EnemyInfo[i] -> hitbox[0]) <= ((EnemyInfo[j] -> pos_x) + 32)) ) || ( ((EnemyInfo[j] -> pos_x) <= (EnemyInfo[i] -> hitbox[2])) && ((EnemyInfo[i] -> hitbox[2]) <= ((EnemyInfo[j] -> pos_x) + 32)) )) && (( ((EnemyInfo[j] -> pos_y) <= (EnemyInfo[i] -> hitbox[1])) && ((EnemyInfo[i] -> hitbox[1]) <= ((EnemyInfo[j] -> pos_y) + 32)) ) || ( ((EnemyInfo[j] -> pos_y) <= (EnemyInfo[i] -> hitbox[3])) && ((EnemyInfo[i] -> hitbox[3]) <= ((EnemyInfo[j] -> pos_y) + 32)) ))  ){
                    /*// right side collision
                    if ( ((EnemyInfo[i] -> prev_pos_x) - (EnemyInfo[j] -> pos_x + 32)) >= 0 ){
                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) > 0){
                            EnemyInfo[i] -> pos_x = (EnemyInfo[j] -> pos_x) + 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) <= 0){
                            EnemyInfo[i] -> pos_x = (EnemyInfo[j] -> pos_x) + 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                    // left side collision
                    if ( ((EnemyInfo[i] -> prev_pos_x + 32) - (EnemyInfo[j] -> pos_x)) <= 0 ){
                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) > 0){
                            EnemyInfo[i] -> pos_x = (EnemyInfo[j] -> pos_x) - 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) <= 0){
                            EnemyInfo[i] -> pos_x = (EnemyInfo[j] -> pos_x) - 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                    // up side collision
                    if ( ((EnemyInfo[i] -> prev_pos_y + 32) - (EnemyInfo[j] -> pos_y)) <= 0 ){
                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) > 0){
                            EnemyInfo[i] -> pos_y = (EnemyInfo[j] -> pos_y) - 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) <= 0){
                            EnemyInfo[i] -> pos_y = (EnemyInfo[j] -> pos_y) - 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                    // down side collision
                    if ( ((EnemyInfo[i] -> prev_pos_y) - (EnemyInfo[j] -> pos_y + 32)) >= 0 ){
                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) > 0){
                            EnemyInfo[i] -> pos_y = (EnemyInfo[j] -> pos_y) + 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) <= 0){
                            EnemyInfo[i] -> pos_y = (EnemyInfo[j] -> pos_y) + 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x - ((EnemyInfo[i] -> speed)/2);
                        }
                    } */

                    EnemyInfo[i] -> pos_x = EnemyInfo[i] -> prev_pos_x;
                    EnemyInfo[i] -> pos_y = EnemyInfo[i] -> prev_pos_y;
                }                
            }
            // walls
            for(int j = 0; j < 30; j++){
                if (walls[j] == 0) {
                    break;
                }
                // walls
                if (  (( ((walls[j] -> coord_x) <= (EnemyInfo[i] -> hitbox[0])) && ((EnemyInfo[i] -> hitbox[0]) <= ((walls[j] -> coord_x) + 32)) ) || ( ((walls[j] -> coord_x) <= (EnemyInfo[i] -> hitbox[2])) && ((EnemyInfo[i] -> hitbox[2]) <= ((walls[j] -> coord_x) + 32)) )) && (( ((walls[j] -> coord_y) <= (EnemyInfo[i] -> hitbox[1])) && ((EnemyInfo[i] -> hitbox[1]) <= ((walls[j] -> coord_y) + 32)) ) || ( ((walls[j] -> coord_y) <= (EnemyInfo[i] -> hitbox[3])) && ((EnemyInfo[i] -> hitbox[3]) <= ((walls[j] -> coord_y) + 32)) ))  ){
                    // right side collision
                    if ( ((EnemyInfo[i] -> prev_pos_x) - (walls[j] -> coord_x + 32)) >= 0 ){
                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) > 0){
                            EnemyInfo[i] -> pos_x = (walls[j] -> coord_x) + 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) <= 0){
                            EnemyInfo[i] -> pos_x = (walls[j] -> coord_x) + 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                    // left side collision
                    if ( ((EnemyInfo[i] -> prev_pos_x + 32) - (walls[j] -> coord_x)) <= 0 ){
                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) > 0){
                            EnemyInfo[i] -> pos_x = (walls[j] -> coord_x) - 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_y) - (EnemyInfo[i] -> prev_pos_y) <= 0){
                            EnemyInfo[i] -> pos_x = (walls[j] -> coord_x) - 33;
                            EnemyInfo[i] -> pos_y = EnemyInfo[i] -> pos_y - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                    // up side collision
                    if ( ((EnemyInfo[i] -> prev_pos_y + 32) - (walls[j] -> coord_y)) <= 0 ){
                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) > 0){
                            EnemyInfo[i] -> pos_y = (walls[j] -> coord_y) - 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) <= 0){
                            EnemyInfo[i] -> pos_y = (walls[j] -> coord_y) - 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                    // down side collision
                    if ( ((EnemyInfo[i] -> prev_pos_y) - (walls[j] -> coord_y + 32)) >= 0 ){
                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) > 0){
                            EnemyInfo[i] -> pos_y = (walls[j] -> coord_y) + 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x + ((EnemyInfo[i] -> speed)/2);
                        }

                        if ((character->pos_x) - (EnemyInfo[i] -> prev_pos_x) <= 0){
                            EnemyInfo[i] -> pos_y = (walls[j] -> coord_y) + 33;
                            EnemyInfo[i] -> pos_x = EnemyInfo[i] -> pos_x - ((EnemyInfo[i] -> speed)/2);
                        }
                    }
                }                
            }
        }
    }

}

void enemyDraw(){
    for(int h = 0; h < 10; h++){
        if(EnemyInMap[h]){
            uint32_t* map2 = (uint32_t*) EnemyInfo[h]->sprite.bytes;
            for(int i = 0; i < EnemyInfo[h]->sprite.width; i++) {
                for (int j = 0; j < EnemyInfo[h]->sprite.height; j++) {
                    pixel_set_color(*(map2 + i + j*(EnemyInfo[h]->sprite.width)),(EnemyInfo[h]->pos_x+i),EnemyInfo[h]->pos_y+j);
                    //pixel_set_color(*(map2 + i + j*(EnemyInfo[h]->spriteProj.width)),((EnemyInfo[h]->pos_x+i)*cos(EnemyInfo[h]->rotation)) - ((EnemyInfo[h]->pos_y+j)*sin(EnemyInfo[h]->rotation)) , ((EnemyInfo[h]->pos_x+i)*sin(EnemyInfo[h]->rotation)) + ((EnemyInfo[h]->pos_y+j)*cos(EnemyInfo[h]->rotation)));
                }
            }
        }
    }
}


void enemyAnim(){
    for(int h = 0; h < 10; h++){
if (EnemyInMap[h]){
    switch (EnemyInfo[h]->side){
        case 0:
        if (EnemyInfo[h]->animFrame < 1){
            EnemyInfo[h]-> sprite = EnemyBack[1];
            EnemyInfo[h]->animFrame = 1;
        }
        else if (EnemyInfo[h]->animFrame == 1){
            EnemyInfo[h]-> sprite = EnemyBack[0];
            EnemyInfo[h]->animFrame = 0;
        }
        break;

        case 1:
        if (EnemyInfo[h]->animFrame < 1){
            EnemyInfo[h]-> sprite = EnemyFront[1];
            EnemyInfo[h]->animFrame = 1;
        }
        else if (EnemyInfo[h]->animFrame == 1){
            EnemyInfo[h]-> sprite = EnemyFront[0];
            EnemyInfo[h]->animFrame = 0;
        }
        break;

        case 2:
        if (EnemyInfo[h]->animFrame < 1){
            EnemyInfo[h]-> sprite = EnemySideLeft[1];
            EnemyInfo[h]->animFrame = 1;
        }
        else if (EnemyInfo[h]->animFrame == 1){
            EnemyInfo[h]-> sprite = EnemySideLeft[0];
            EnemyInfo[h]->animFrame = 0;
        }
        break;

        case 3:
        if (EnemyInfo[h]->animFrame < 1){
            EnemyInfo[h]-> sprite = EnemySideRight[1];
            EnemyInfo[h]->animFrame = 1;
        }
        else if (EnemyInfo[h]->animFrame == 1){
            EnemyInfo[h]-> sprite = EnemySideRight[0];
            EnemyInfo[h]->animFrame = 0;
        }
        break;

    }
    }
}
}

