#ifndef _KDB_MACROS_H_
#define _KDB_MACROS_H_

#define KBD_IRQ                 1

#define BIT(n)                  (0x01<<(n))

#define OUT_BUF                 0x60    //output buffer
#define IN_BUF                  0x64    //input buffer

#define STAT_REG                0x64    //Status register
#define KBC_CMD_REG             0x64

/*Keybord related KBC commands*/
#define READ_CMD                0x20    //read command byte
#define WRITE_CMD               0x60    //write command byte 
#define KCB_CHECK               0xAA    //Check KBC (self-test)
#define KBD_INT_CHECK           0xAB    //Check keybord interface
#define KBD_INT_DISABLE         0xAD    //Disable KBD interface
#define KBD_INT_ENABLE          0xAE    //Enable KBD interface 

#define ESC_BREAK_CODE          0x81    //Break code of the Esc key

#define TWO_BYTE_CODE           0xe0    //To test when a code is two bytes long

#define DELAY_US                20000   //delay used in the delay function

#define _OBF                    0
#define _IBF                    1
#define _SYS                    2
#define _A2                     3
#define _INH                    4
#define _AUX                    5

#endif
