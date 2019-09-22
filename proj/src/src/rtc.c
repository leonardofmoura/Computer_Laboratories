#include <lcom/lcf.h>

#include "../include/rtc.h"

static int rtc_hook_id;
uint8_t real_time[3];
uint8_t real_date[3];

//subscribe rtc interruptions
int rtc_subscribe(uint8_t* bit_no) {
    rtc_hook_id = RTC_IRQ;
    *bit_no = rtc_hook_id;
    uint32_t temp;


    if (sys_irqsetpolicy(RTC_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,&rtc_hook_id) != 0) {
        printf("Unable to subscribe rtc\n");
        return 1;
    }

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {
        return 1;
    } 

    temp |= RTC_UIE;

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_outb(RTC_DATA_REG,temp) != 0) {
        return 1;
    } 

    return 0;
}

//unsubscribe rtc interruptions
int rtc_unsubscribe() {
    uint32_t temp;
    if (sys_irqrmpolicy(&rtc_hook_id) != 0) {
        printf("Unable to unsubscribe rtc\n");
        return 1;
    }
    
    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {
        return 1;
    } 

    temp &= ~RTC_UIE;

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_outb(RTC_DATA_REG,temp) != 0) {
        return 1;
    } 

    return 0;
}

//disable rtc interrupts
int rtc_disable() {
    if (sys_irqdisable(&rtc_hook_id) != 0) {
        return 1;
    }

    return 0;
}

//enable rtc interrupts
int rtc_enable() {
    if (sys_irqenable(&rtc_hook_id) != 0) {
        return 1;
    }

    return 0;
}


//get the config and put it in the pointer
int rtc_get_conf(uint32_t *conf) {
    uint8_t* conf_vec = (uint8_t*) conf;
    uint32_t temp;

    // rtc_disable();

    if (sys_outb(RTC_ADDR_REG, RTC_REG_A) != 0) {return 1;} 
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {return 1;}

    *conf_vec = (uint8_t) temp;

    if (sys_outb(RTC_ADDR_REG, RTC_REG_B) != 0) {return 1;} 
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {return 1;} 
    *(conf_vec + 1)  = (uint8_t) temp;

    if (sys_outb(RTC_ADDR_REG, RTC_REG_C) != 0) {return 1;} 
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {return 1;} 
    *(conf_vec + 2)  = (uint8_t) temp;

    if (sys_outb(RTC_ADDR_REG, RTC_REG_D) != 0) {return 1;} 
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {return 1;} 
    *(conf_vec + 3)  = (uint8_t) temp;

    // rtc_enable();

    return 0;
}

int rtc_print_config(uint32_t* conf) {
    uint8_t* conf_vec = (uint8_t* ) conf;

    uint8_t regA = *conf_vec;
    uint8_t regB = *(conf_vec + 1);
    uint8_t regC = *(conf_vec + 2);
    uint8_t regD = *(conf_vec + 3);

    printf("Reg A: 0x%x\n",regA);
    printf("Reg B: 0x%x\n",regB);
    printf("Reg C: 0x%x\n",regC);
    printf("Reg D: 0x%x\n",regD);

    printf("\nRate Selector: 0x%x\n",(regA & RATE_SELECTOR));
    if (regA & BIT(7)) {
        printf("Update in progress\n");
    }
    else {
        printf("Update not in progress\n");
    }

    if (regB & BIT(0)) {
        printf("Daylight Savings Time enabeled\n");
    }
    else {
        printf("Daylight Savings Time disabeled\n");
    }

    if (regB & BIT(1)) {
        printf("Hour range: 0 to 23\n");
    }
    else {
        printf("Hours range: 1 to 12\n");
    }

    if (regB & BIT(3)) {
        printf("Square wave generation enabeled\n");
    }
    else {
        printf("Square wave generation disabeled\n");
    }

    if (regB & BIT(7)) {
        printf("Time/date registers update inhibited\n");
    }
    else {
        printf("Time/date registers update not inhibited\n");
    }

    if (regC & BIT(4)) {
        printf("Update interrupt pending\n");
    }

    if (regC & BIT(5)) {
        printf("Alarm interrupt pending\n");
    }

    if (regC & BIT(6)) {
        printf("Periodic interrupt pending\n");
    }

    if (regC & BIT(7)) {
        printf("Periodic interrupt pending\n");
    }
    
    return 0;
}

uint8_t rtc_get_day() {
    uint32_t temp;

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

        if (sys_outb(RTC_ADDR_REG,RTC_MONTH_DAY) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }

    real_date[2] = (uint8_t) temp;
    return real_date[2];
}

uint8_t rtc_get_month() {
    uint32_t temp;

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

        if (sys_outb(RTC_ADDR_REG,RTC_MONTH) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }

    real_date[1] = (uint8_t) temp;
    return real_date[1];
}

uint8_t rtc_get_year() {
    uint32_t temp;

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

        if (sys_outb(RTC_ADDR_REG,RTC_YEAR) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }

    real_date[0] = (uint8_t) temp;
    return real_date[0];
}

uint8_t rtc_get_seconds() {
    uint32_t temp;

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

        if (sys_outb(RTC_ADDR_REG,RTC_SEC) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }

    real_time[2] = (uint8_t) temp;
    return real_time[2];
}

uint8_t rtc_get_minutes() {
    uint32_t temp;

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

        if (sys_outb(RTC_ADDR_REG,RTC_MIN) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }

    real_time[1] = (uint8_t) temp;
    return real_time[1];
}

uint8_t rtc_get_hours() {
    uint32_t temp;

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

        if (sys_outb(RTC_ADDR_REG,RTC_HOUR) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }

    real_time[0] = (uint8_t) temp;
    return real_time[0];
}


//sets set bit of regB
int rtc_disable_updates() {
    uint32_t temp;

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {
        return 1;
    } 

    temp |= RTC_SET;

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_outb(RTC_DATA_REG,temp) != 0) {
        return 1;
    } 

    return 0;
} 

int rtc_reenable_updates() {
    uint32_t temp;

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_inb(RTC_DATA_REG,&temp) != 0) {
        return 1;
    } 

    temp &= ~RTC_SET;

    if (sys_outb(RTC_ADDR_REG,RTC_REG_B) != 0) {
        return 1;
    }
    if (sys_outb(RTC_DATA_REG,temp) != 0) {
        return 1;
    } 

    return 0;
}

//
int rtc_change_hour() {
    uint32_t temp;

    rtc_disable_updates();

    do  {
        rtc_disable();
        if (sys_outb(RTC_ADDR_REG,RTC_REG_A) != 0) {
            return 1;
        }
        if(sys_inb(RTC_DATA_REG,&temp) != 0) {
            return 0;
        }
        rtc_enable();
    } while(temp & RTC_UIP);

    if (sys_outb(RTC_ADDR_REG,RTC_HOUR) != 0) {
        return 1;
    }
    if(sys_inb(RTC_DATA_REG,&temp) != 0) {
        return 0;
    }

    uint8_t res = dec_to_bcd(2); 

    if (sys_outb(RTC_ADDR_REG,RTC_HOUR) != 0) {
        return 1;
    }
    if(sys_outb(RTC_DATA_REG,res) != 0) {
        return 0;
    }

    rtc_reenable_updates();

    return 0;
}

void rtc_ih() {
    uint32_t regC;

    sys_outb(RTC_ADDR_REG, RTC_REG_C);
    sys_inb(RTC_DATA_REG, &regC);
    
    if( regC & RTC_UF ) {
        rtc_get_seconds();
        rtc_get_minutes();
        rtc_get_seconds();
    }   
    if( regC & RTC_AF ) {}
    if( regC & RTC_PF ) {}

}

void rtc_init() {
    rtc_get_day();
	rtc_get_month();
	rtc_get_year();
	rtc_get_seconds();
	rtc_get_minutes();
	rtc_get_hours();
}

uint8_t bcd_to_dec(uint8_t bin) {
    return FIRST(bin)*10 + SECOND(bin);
}

uint8_t dec_to_bcd(uint8_t bcd) {
    uint8_t first;
    uint8_t second;

    first = (bcd/10) << 4;
    second = bcd % 10;

    return first + second;
}

uint8_t decrease_bcd(uint8_t bcd) {
    return dec_to_bcd(bcd_to_dec(bcd) - 1); 
}
