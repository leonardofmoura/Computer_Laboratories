#ifndef _MOUSE_MACROS_H
#define _MOUSE_MACROS_H

#define MOUSE_IRQ               12          //the mouse irq line

#define BIT(n)                  (0x01<<(n))

#define OUT_BUF                 0x60        //output buffer
#define IN_BUF                  0x64        //input buffer

#define STAT_REG                0x64        //status register
#define KBC_CMD_REG             0x64        //command register
#define KBC_ARGS_REG            0x60        //arguments register
#define KBC_RET_REG             0x60        //return values register

//mouse related KBC commands
#define READ_CMD                0x20        //read command byte
#define WRITE_CMD               0x60        //write command byte 
#define MOUS_DISBL              0xA7        //disable mouse
#define MOUSE_ENBL              0xA8        //enable mouse
#define MOUSE_CHECK             0xA9        //check mouse 
#define WRITE_MOUSE             0xD4        //write byte to mouse

//status register 
#define PARITY                  BIT(7)      //parity error
#define TIMEOUT                 BIT(6)      //timeout error
#define AUX                     BIT(5)      //mouse data
#define INH                     BIT(4)      //inhibit flag : 0 if kbd inhibited
#define A2                      BIT(3)      //a2 input line
#define SYS                     BIT(2)      //system flag
#define IBF                     BIT(1)      //input buffer - DONT WRITE COMMANDS OR ARGS
#define OBF                     BIT(0)      //output buffer full 

//commands passed as arguments of 0xD4
#define RESET                   0xFF        //mouse reset
#define RESEND                  0xFE        //For serial comunications errors
#define SET_DEF                 0xF6        //Set default values
#define DISABLE_REP             0xF5        //In stream mode should be sent before any command
#define ENABLE_REP              0xF4        //in stream mode only 
#define SET_SAMPLE_RATE         0xF3        //sets state sampling rate
#define SET_REMOTE_MODE         0xF0        //Send data on request only
#define READ_DATA               0xEB        //Send data packet request
#define SET_STREAM_MODE         0xEA        //Send data on events 
#define STATUS_REQUEST          0xE9        //Get mouse config (3 bytes)
#define SET_RESOLUTION          0xE8        
#define SET_SCALING_2_1         0xE7        //acceleration mode
#define SET_SCALING_1_1         0xE6        //linear mode

//acknowledgement bytes
#define ACK                     0xFA        //everything is ok
#define NACK                    0xFE        //invalid byte
#define ERROR                   0xFC        //second consecutive invalid byte


#define DELAY_US                20000

#endif
