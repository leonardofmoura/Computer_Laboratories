#include <lcom/lcf.h>
#include "../include/crosshair.h"
#include "../include/mouse.h"
#include "../include/kbd.h"
#include "../include/video_card.h"
#include "../include/projectile.h"
#include "../include/key_map.h"
#include "../include/projectile.h"
#include "../include/character.h"
#include "../include/terrain.h"
#include "../include/enemy.h"
#include <math.h>


#include "../sprites/Projectile_00.xpm"
#include "../sprites/Projectile_01.xpm"
#include "../sprites/Projectile_02.xpm"
#include "../sprites/Projectile_03.xpm"
#include "../sprites/Projectile_04.xpm"
#include "../sprites/Projectile_05.xpm"
#include "../sprites/Projectile_06.xpm"
#include "../sprites/Projectile_07.xpm"
#include "../sprites/Projectile_08.xpm"
#include "../sprites/Projectile_09.xpm"
#include "../sprites/Projectile_10.xpm"
#include "../sprites/Projectile_11.xpm"
#include "../sprites/Projectile_12.xpm"
#include "../sprites/Projectile_13.xpm"
#include "../sprites/Projectile_14.xpm"
#include "../sprites/Projectile_15.xpm"
#include "../sprites/Projectile_16.xpm"
#include "../sprites/Projectile_17.xpm"

extern character_t* character;
extern crosshair_t* crosshair;
extern wall_t* walls[30];


void projectiles_start(){


    for (int i = 0; i < 50; i++){
        ProjectilesInMap[i] = false;
    }

    for (int h = 0; h < 50; h++){
       desint_t* desint_num;
       desint_num = malloc(sizeof(desint_t));
       desint_num -> isIt = false;
       desint_num -> pos_x = 0;
       desint_num -> pos_y = 0;
       desint_num -> animFrame = 0;
       desint_num -> rotation = 0;
       ProjectilesDesintegrating[h] = desint_num;
    }

    xpm_image_t ProjSprite;

    xpm_load(Projectile_00_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[0] = ProjSprite;
    xpm_load(Projectile_01_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[1] = ProjSprite;
    xpm_load(Projectile_02_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[2] = ProjSprite;
    xpm_load(Projectile_03_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[3] = ProjSprite;
    xpm_load(Projectile_04_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[4] = ProjSprite;
    xpm_load(Projectile_05_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[5] = ProjSprite;
    xpm_load(Projectile_06_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[6] = ProjSprite;
    xpm_load(Projectile_07_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[7] = ProjSprite;
    xpm_load(Projectile_08_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[8] = ProjSprite;
    xpm_load(Projectile_09_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[9] = ProjSprite;
    xpm_load(Projectile_10_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[10] = ProjSprite;
    xpm_load(Projectile_11_xpm,XPM_8_8_8_8,&ProjSprite);
    ProjAnimation[11] = ProjSprite;

}






void projectile_draw(){
    for(int h = 0; h < 50; h++){
        if(ProjectilesInMap[h]){
            uint32_t* map2 = (uint32_t*) ProjectilesInfo[h]->spriteProj.bytes;
            for(int i = 0; i < ProjectilesInfo[h]->spriteProj.width; i++) {
                for (int j = 0; j < ProjectilesInfo[h]->spriteProj.height; j++) {
                    //pixel_set_color(*(map2 + i + j*(ProjectilesInfo[h]->spriteProj.width)),(ProjectilesInfo[h]->pos_x+i),ProjectilesInfo[h]->pos_y+j);
                    //pixel_set_color(*(map2 + i + j*(ProjectilesInfo[h]->spriteProj.width)),ProjectilesInfo[h]->pos_x+(i*cos(ProjectilesInfo[h]->rotation) - j*sin(ProjectilesInfo[h]->rotation)),ProjectilesInfo[h]->pos_y - (i*sin(ProjectilesInfo[h]->rotation) + j*cos(ProjectilesInfo[h]->rotation)));
                    pixel_set_color(*(map2 + i + j*(ProjectilesInfo[h]->spriteProj.width)),ProjectilesInfo[h]->pos_x + 8 +((i-8)*cos(ProjectilesInfo[h]->rotation) - (j-8)*sin(ProjectilesInfo[h]->rotation)),ProjectilesInfo[h]->pos_y + 8 - ((i-8)*sin(ProjectilesInfo[h]->rotation) + (j-8)*cos(ProjectilesInfo[h]->rotation)));
                }
            }
        }
        if(ProjectilesDesintegrating[h]-> isIt){
            uint32_t* map3 = (uint32_t*) ProjectilesDesintegrating[h]->sprite.bytes;
            for(int k = 0; k < ProjectilesDesintegrating[h]->sprite.width; k++) {
                for (int l = 0; l < ProjectilesDesintegrating[h]->sprite.height; l++) {
                    //pixel_set_color(*(map3 + k + l*(ProjectilesDesintegrating[h]->sprite.width)),ProjectilesDesintegrating[h]->pos_x+(k*cos(ProjectilesDesintegrating[h]->rotation) - l*sin(ProjectilesDesintegrating[h]->rotation)),ProjectilesDesintegrating[h]->pos_y - (k*sin(ProjectilesDesintegrating[h]->rotation) + l*cos(ProjectilesDesintegrating[h]->rotation)));
                    pixel_set_color(*(map3 + k + l*(ProjectilesDesintegrating[h]->sprite.width)),ProjectilesDesintegrating[h]->pos_x + 8 +((k-8)*cos(ProjectilesDesintegrating[h]->rotation) - (l-8)*sin(ProjectilesDesintegrating[h]->rotation)),ProjectilesDesintegrating[h]->pos_y + 8 - ((k-8)*sin(ProjectilesDesintegrating[h]->rotation) + (l-8)*cos(ProjectilesDesintegrating[h]->rotation)));
                }
            }
        }
    }
}

void projectile_bobbing(){
    for(int h = 0; h < 50; h++){
        if(ProjectilesInMap[h]){
            if (ProjectilesInfo[h]->animFrame == 0){
                ProjectilesInfo[h]-> spriteProj = ProjAnimation[1];
                ProjectilesInfo[h]->animFrame = 1;
                }
            else if (ProjectilesInfo[h]->animFrame == 1){
                ProjectilesInfo[h]-> spriteProj = ProjAnimation[0];
                ProjectilesInfo[h]->animFrame = 0;
            }
        }
    }
}

void projectile_collide_anim(){
    for(int h = 0; h < 50; h++){
        if(ProjectilesDesintegrating[h]-> isIt){
            if (ProjectilesDesintegrating[h]->animFrame < 17){
                ProjectilesDesintegrating[h]->sprite = ProjAnimation[(ProjectilesDesintegrating[h]->animFrame) + 1];
                (ProjectilesDesintegrating[h]->animFrame)++;
                }
                else if (ProjectilesDesintegrating[h]->animFrame == 17){
                    ProjectilesDesintegrating[h]->sprite = ProjAnimation[0];
                    ProjectilesDesintegrating[h]->animFrame = 0;
                    ProjectilesDesintegrating[h]->isIt = false;
                }
        }           
    }
}

void projectile_refresh(){
    for(int h = 0; h < 50; h++){
        if(ProjectilesInMap[h]){
            ProjectilesInfo[h]->pos_x -= (ProjectilesInfo[h]->Dx * ProjectilesInfo[h]->speed);
            ProjectilesInfo[h]->pos_y -= (ProjectilesInfo[h]->Dy * ProjectilesInfo[h]->speed);
            ProjectilesInfo[h]->hitbox[0] =  ProjectilesInfo[h]->pos_x;
            ProjectilesInfo[h]->hitbox[1] =  ProjectilesInfo[h]->pos_y;
            ProjectilesInfo[h]->hitbox[2] =  ProjectilesInfo[h]->pos_x + 16;
            ProjectilesInfo[h]->hitbox[3] =  ProjectilesInfo[h]->pos_y + 16;
        }
    }


}



void projectile_create(){
    projectile_t* proj_num;
    proj_num = malloc(sizeof(projectile_t));
    for (int i = 0; i < 50; i++){
        if (!(ProjectilesInMap[i])){
        ProjectilesInMap[i] = true;

        proj_num -> speed = 8;
        proj_num -> animFrame = 0;
        proj_num -> rotation = -1.57079 + atan2((character->pos_y + 8) - (crosshair->coord_y), (crosshair->coord_x) - (character->pos_x + 8));
        proj_num -> spriteProj = ProjAnimation[0];
        proj_num -> pos_x = character->pos_x + 8;
        proj_num -> pos_y = character->pos_y + 8;
        proj_num -> Dx = (character->pos_x + 8) - (crosshair->coord_x);
        proj_num -> Dy = (character->pos_y + 8) - (crosshair->coord_y);

        double Dlength = sqrt((proj_num -> Dx)*(proj_num -> Dx) + (proj_num -> Dy)*(proj_num -> Dy));
        if((proj_num -> Dx) != 0){
            proj_num -> Dx = (proj_num -> Dx) / Dlength;
        }
        if((proj_num -> Dy) != 0){
            proj_num -> Dy = (proj_num -> Dy) / Dlength;
        }

        ProjectilesInfo[i] = proj_num;

        break;
        }
    }
}



void projectile_check_collision(){
    for(int i = 0; i < 50; i++){
        if(ProjectilesInMap[i]){
            for(int j = 0; j < 200; j++){
                if (walls[j] == 0) {
                    break;
                }

                if (  (( ((walls[j] -> coord_x) <= (ProjectilesInfo[i] -> hitbox[0])) && ((ProjectilesInfo[i] -> hitbox[0]) <= ((walls[j] -> coord_x) + 32)) ) || ( ((walls[j] -> coord_x) <= (ProjectilesInfo[i] -> hitbox[2])) && ((ProjectilesInfo[i] -> hitbox[2]) <= ((walls[j] -> coord_x) + 32)) )) && (( ((walls[j] -> coord_y) <= (ProjectilesInfo[i] -> hitbox[1])) && ((ProjectilesInfo[i] -> hitbox[1]) <= ((walls[j] -> coord_y) + 32)) ) || ( ((walls[j] -> coord_y) <= (ProjectilesInfo[i] -> hitbox[3])) && ((ProjectilesInfo[i] -> hitbox[3]) <= ((walls[j] -> coord_y) + 32)) ))  ){
                    ProjectilesInMap[i] = false;
                    for (int h = 0; h < 50; h++){
                        if (!(ProjectilesDesintegrating[h] -> isIt)){
                            ProjectilesDesintegrating[h] -> isIt = true;
                            ProjectilesDesintegrating[h] -> pos_x = ProjectilesInfo[i] -> pos_x;
                            ProjectilesDesintegrating[h] -> pos_y = ProjectilesInfo[i] -> pos_y;
                            ProjectilesDesintegrating[h] -> rotation = ProjectilesInfo[i] -> rotation;
                            ProjectilesDesintegrating[h] -> animFrame = ProjectilesInfo[i] -> animFrame;
                            ProjectilesDesintegrating[h] -> sprite = ProjectilesInfo[i] -> spriteProj;
                            break;
                        }
                    }
                }
            }
            //Enemy
            for(int j = 0; j < 10; j++){
                if (EnemyInMap[j]) {

                if (  (( ((EnemyInfo[j] -> hitbox[0]) <= (ProjectilesInfo[i] -> hitbox[0])) && ((ProjectilesInfo[i] -> hitbox[0]) <= ((EnemyInfo[j] -> hitbox[2]))) ) || ( ((EnemyInfo[j] -> hitbox[0]) <= (ProjectilesInfo[i] -> hitbox[2])) && ((ProjectilesInfo[i] -> hitbox[2]) <= ((EnemyInfo[j] -> hitbox[2]))) )) && (( ((EnemyInfo[j] -> hitbox[1]) <= (ProjectilesInfo[i] -> hitbox[1])) && ((ProjectilesInfo[i] -> hitbox[1]) <= ((EnemyInfo[j] -> hitbox[3]))) ) || ( ((EnemyInfo[j] -> hitbox[1]) <= (ProjectilesInfo[i] -> hitbox[3])) && ((ProjectilesInfo[i] -> hitbox[3]) <= ((EnemyInfo[j] -> hitbox[3]) )) ))  ){
                    ProjectilesInMap[i] = false;
                    for (int h = 0; h < 50; h++){
                           if (!(ProjectilesDesintegrating[h] -> isIt)){
                                ProjectilesDesintegrating[h] -> isIt = true;
                               ProjectilesDesintegrating[h] -> pos_x = ProjectilesInfo[i] -> pos_x;
                                ProjectilesDesintegrating[h] -> pos_y = ProjectilesInfo[i] -> pos_y;
                                ProjectilesDesintegrating[h] -> rotation = ProjectilesInfo[i] -> rotation;
                                ProjectilesDesintegrating[h] -> animFrame = ProjectilesInfo[i] -> animFrame;
                                ProjectilesDesintegrating[h] -> sprite = ProjectilesInfo[i] -> spriteProj;
                                EnemyInfo[j] -> life--;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}





