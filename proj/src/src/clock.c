#include <lcom/lcf.h>
#include "../include/clock.h"
#include "../include/rtc.h"
#include "../include/video_card.h"

#include "../sprites/numbers_00.xpm"
#include "../sprites/numbers_01.xpm"
#include "../sprites/numbers_02.xpm"
#include "../sprites/numbers_03.xpm"
#include "../sprites/numbers_04.xpm"
#include "../sprites/numbers_05.xpm"
#include "../sprites/numbers_06.xpm"
#include "../sprites/numbers_07.xpm"
#include "../sprites/numbers_08.xpm"
#include "../sprites/numbers_09.xpm"
#include "../sprites/numbers_10.xpm"
#include "../sprites/numbers_11.xpm"

static _clock_t* clock_;
extern uint8_t real_time[3];
extern uint8_t real_date[3];


_clock_t* clock_init(int xc, int yc, int xd, int yd) {
    clock_ = malloc(sizeof(*clock_));

    rtc_init();

    clock_->first_hour = FIRST(real_time[0]);
    clock_->second_hour = SECOND(real_time[0]);
    clock_->first_minute = FIRST(real_time[1]);
    clock_->second_minute = SECOND(real_time[1]);
    clock_->first_second = FIRST(real_time[2]);
    clock_->second_second = SECOND(real_time[2]);

    clock_->first_year = FIRST(real_date[0]);
    clock_->second_year = SECOND(real_date[0]);
    clock_->first_month = FIRST(real_date[1]);
    clock_->second_month = SECOND(real_date[1]);
    clock_->first_day = FIRST(real_date[2]);
    clock_->second_day = SECOND(real_date[2]);    

    clock_->coord_x_clock = xc;
    clock_->coord_y_clock = yc;

    clock_->coord_x_date = xd;
    clock_->coord_y_date = yd;

    xpm_load(numbers_09,XPM_8_8_8_8,&clock_->numbers[0]);
    xpm_load(numbers_00,XPM_8_8_8_8,&clock_->numbers[1]);
    xpm_load(numbers_01,XPM_8_8_8_8,&clock_->numbers[2]);
    xpm_load(numbers_02,XPM_8_8_8_8,&clock_->numbers[3]);
    xpm_load(numbers_03,XPM_8_8_8_8,&clock_->numbers[4]);
    xpm_load(numbers_04,XPM_8_8_8_8,&clock_->numbers[5]);
    xpm_load(numbers_05,XPM_8_8_8_8,&clock_->numbers[6]);
    xpm_load(numbers_06,XPM_8_8_8_8,&clock_->numbers[7]);
    xpm_load(numbers_07,XPM_8_8_8_8,&clock_->numbers[8]);
    xpm_load(numbers_08,XPM_8_8_8_8,&clock_->numbers[9]);
    xpm_load(numbers_10,XPM_8_8_8_8,&clock_->numbers[10]);
    xpm_load(numbers_11,XPM_8_8_8_8,&clock_->numbers[11]);

    return clock_;
}

void clock_update() {
    clock_->first_hour = FIRST(real_time[0]);
    clock_->second_hour = SECOND(real_time[0]);
    clock_->first_minute = FIRST(real_time[1]);
    clock_->second_minute = SECOND(real_time[1]);
    clock_->first_second = FIRST(real_time[2]);
    clock_->second_second = SECOND(real_time[2]);

    clock_->first_year = FIRST(real_date[0]);
    clock_->second_year = SECOND(real_date[0]);
    clock_->first_month = FIRST(real_date[1]);
    clock_->second_month = SECOND(real_date[1]);
    clock_->first_day = FIRST(real_date[2]);
    clock_->second_day = SECOND(real_date[2]); 
}

void print_clock() {
    printf("%d%d:%d%d:%d%d\n",clock_->first_hour,clock_->second_hour,clock_->first_minute,clock_->second_minute,
       clock_->first_second,clock_->second_second);
}

void display_clock() {
    //draw hours
    uint32_t* map = (uint32_t*) clock_->numbers[clock_->first_hour].bytes;
    for(int i = 0; i < clock_->numbers[clock_->first_hour].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->first_hour].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->first_hour].width),clock_->coord_x_clock+i,clock_->coord_y_clock+j);
        }
    } 
    map = (uint32_t*) clock_->numbers[clock_->second_hour].bytes;
    for(int i = 0; i < clock_->numbers[clock_->second_hour].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->second_hour].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->second_hour].width),clock_->coord_x_clock+i+32,clock_->coord_y_clock+j);
        }
    } 

    //draw the colon
    map = (uint32_t*) clock_->numbers[10].bytes;
    for(int i = 0; i < clock_->numbers[10].width; i++) {
        for (int j = 0; j < clock_->numbers[10].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[10].width),clock_->coord_x_clock+i+64,clock_->coord_y_clock+j);
        }
    }

    //draw minutes
    map = (uint32_t*) clock_->numbers[clock_->first_minute].bytes;
    for(int i = 0; i < clock_->numbers[clock_->first_minute].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->first_minute].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->first_minute].width),clock_->coord_x_clock+i+96,clock_->coord_y_clock+j);
        }
    }
    map = (uint32_t*) clock_->numbers[clock_->second_minute].bytes;
    for(int i = 0; i < clock_->numbers[clock_->second_minute].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->second_minute].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->second_minute].width),clock_->coord_x_clock+i+128,clock_->coord_y_clock+j);
        }
    }
     
}

void display_date() {
    //draw day
    uint32_t* map = (uint32_t*) clock_->numbers[clock_->first_day].bytes;
    for(int i = 0; i < clock_->numbers[clock_->first_day].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->first_day].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->first_day].width),clock_->coord_x_date+i,clock_->coord_y_date+j);
        }
    } 
    map = (uint32_t*) clock_->numbers[clock_->second_day].bytes;
    for(int i = 0; i < clock_->numbers[clock_->second_day].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->second_day].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->second_day].width),clock_->coord_x_date+i+32,clock_->coord_y_date+j);
        }
    } 

    //draw the point
    map = (uint32_t*) clock_->numbers[11].bytes;
    for(int i = 0; i < clock_->numbers[11].width; i++) {
        for (int j = 0; j < clock_->numbers[11].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[11].width),clock_->coord_x_date+i+64,clock_->coord_y_date+j);
        }
    }

    //draw month
    map = (uint32_t*) clock_->numbers[clock_->first_month].bytes;
    for(int i = 0; i < clock_->numbers[clock_->first_month].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->first_month].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->first_month].width),clock_->coord_x_date+i+96,clock_->coord_y_date+j);
        }
    }
    map = (uint32_t*) clock_->numbers[clock_->second_month].bytes;
    for(int i = 0; i < clock_->numbers[clock_->second_month].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->second_month].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->second_month].width),clock_->coord_x_date+i+128,clock_->coord_y_date+j);
        }
    }

    //draw the point
    map = (uint32_t*) clock_->numbers[11].bytes;
    for(int i = 0; i < clock_->numbers[11].width; i++) {
        for (int j = 0; j < clock_->numbers[11].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[11].width),clock_->coord_x_date+i+160,clock_->coord_y_date+j);
        }
    }

    //draw the year
    map = (uint32_t*) clock_->numbers[clock_->first_year].bytes;
    for(int i = 0; i < clock_->numbers[clock_->first_year].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->first_year].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->first_day].width),clock_->coord_x_date+i+192,clock_->coord_y_date+j);
        }
    }
    map = (uint32_t*) clock_->numbers[clock_->second_year].bytes;
    for(int i = 0; i < clock_->numbers[clock_->second_year].width; i++) {
        for (int j = 0; j < clock_->numbers[clock_->second_year].height; j++) {
            // printf("loop %d %d.....",i,j);
            pixel_set_color(*(map + i + j*clock_->numbers[clock_->second_year].width),clock_->coord_x_date+i+224,clock_->coord_y_date+j);
        }
    }
}


void clock_delete() {
    free(clock_);
}


