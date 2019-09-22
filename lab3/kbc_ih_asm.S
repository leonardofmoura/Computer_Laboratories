#include <machine/asm.h>
#include "kbd_macros.h"


/*void kbc_ih_asm(); */
/*using _C_LABEL from <machine/asm.h>*/

/*.global _C_LABEL(two_byte_code)
.global _C_LABEL(scan_code_array)*/
.global _C_LABEL(kbc_asm_ih)

/*.data 
_C_LABEL(two_byte_code):
    .byte 0
_C_LABEL(scan_code_array):
    .byte 0
    .byte 0
*/

.text
_C_LABEL(kbc_asm_ih):
        movb _C_LABEL(two_byte_code), %bl /*moves two_byte_code to bl*/
        inb $STAT_REG, %al        /*reads status register*/     
        testb $0x01, %al           /*checks if the output buffer is full*/
        jnz cont                    /*if its full continues*/
        ret                         /*if the output buffer is not full returns */

cont:   inb $OUT_BUF, %al         /*reads the output buffer*/
        cmpb $0x00, %bl             /*checks if two_byte_code is active*/
        jnz byte1                      /*if it is jupmps to byte1*/
        cmpb $(TWO_BYTE_CODE), %al      /*checks if the code is two bytes long*/
        jz byte0                    /*if it is jumps to byte0*/

        movb %al, _C_LABEL(scancode_array) /*moves the scancode to the vector*/
        ret

byte1:  movb %al, _C_LABEL(scancode_array) + 1   /*moves the scancode to array's position 1*/
        movb $0x00, _C_LABEL(two_byte_code)     /* sets two_byte_code to not active*/
        ret 

byte0:  movb %al, _C_LABEL(scancode_array)     /*moves the scancode to array's position 0*/
        movb $0x01, _C_LABEL(two_byte_code)   /*sets two_byte code to active*/
        ret

end:    ret



