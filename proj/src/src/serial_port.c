#include <lcom/lcf.h>
#include "../include/serial_port.h"
#include "../include/serial_port_macros.h"
#include "../include/queue.h"

static uint8_t config[2];
static int hook_id;
queue_t* recieved_data_queue;
queue_t* transmit_data_queue;
bool valid_interrupt = false;
bool able_to_transmit = false;

int serial_port_get_config(uint32_t base_addr) {
    uint32_t temp;

    if(sys_inb(base_addr + UART_LCR,&temp) != 0) {
        return 1;
    }
    config[0] = (uint8_t) temp;

    if (sys_inb(base_addr + UART_IER,&temp) != 0) {
        return 1;
    }
    config[1] = (uint8_t) temp;

    return 0;
}

int print_serial_port_config() {
    //printf the lcf reg
    uint8_t lcr = config[0];
    printf("Word length: %x\n",lcr&LCR_NUMBER_OF_BITS_PER_CHAR);
    printf("No. of stop bits: %x\n",lcr&LCR_STOP_BIT);
    printf("Parity: %x\n",lcr&LCR_PARITY_CONTROL);
    printf("DLAB: %x\n",lcr&LCR_DLAB);
    printf("%x\n",lcr);

    return 0;
}


int serial_port_send(uint8_t msg) {
    if (able_to_transmit) {
        if (sys_outb(UART_COM1 + UART_THR,msg) != 0) {
            return 1;
        }
    }
    able_to_transmit = false;
    // tickdelay(micros_to_ticks(20000));

    return 0;
}

int serial_port_send_force(uint8_t msg) {
        if (sys_outb(UART_COM1 + UART_THR,msg)) {
            return 1;
        }

    return 0;
}

uint8_t serial_port_recieve() {
    uint32_t temp;
    sys_inb(UART_COM1 + UART_THR,&temp);

    return (uint8_t) temp;
}

//subscribes serial port interrupts for recived transmition
int serial_port_subscribe_rec(uint8_t* bit_no) {
    hook_id = UART_COM1_IRQ;
    *bit_no = hook_id;

    if (sys_irqsetpolicy(UART_COM1_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id) != 0) {
        return 1;
    }

    //set the recieved data interrupt
    uint32_t temp;
    if (sys_inb(UART_COM1 + UART_IER,&temp) != 0) {
        return 1;
    }
    uint8_t mask = ((uint8_t) temp) | IER_ENABLE_DATA_INTERRUPT;

    if (sys_outb(UART_COM1 + UART_IER,mask) != 0) {
        return 1;
    }

    //initialize recieved data queue
    recieved_data_queue = queue_init();

    return 0;
}

int serial_port_subscribe_trans(uint8_t* bit_no) {
    hook_id = UART_COM1_IRQ;
    *bit_no = hook_id;

    if (sys_irqsetpolicy(UART_COM1_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id) != 0) {
        return 1;
    }

    //set the recieved data interrupt
    uint32_t temp;
    if (sys_inb(UART_COM1 + UART_IER,&temp) != 0) {
        return 1;
    }
    uint8_t mask = /*((uint8_t) temp) |*/ IER_ENABLE_TRANS_EMPTY_INT;

    if (sys_outb(UART_COM1 + UART_IER,mask) != 0) {
        return 1;
    }

    //initialize recieved data queue
    transmit_data_queue = queue_init();

    return 0;
}

int serial_port_unsubscribe_rec() {
    if (sys_irqrmpolicy(&hook_id) != 0 ) {
        return 1;
    }

    //disable the recieved data interrupt
    uint32_t temp;
    if (sys_inb(UART_COM1 + UART_IER,&temp) != 0) {
        return 1;
    }
    uint8_t mask = ((uint8_t) temp) & ~IER_ENABLE_DATA_INTERRUPT;

    if (sys_outb(UART_COM1 + UART_IER,mask) != 0) {
        return 1;
    }

    queue_delete(recieved_data_queue);

  return 0;
}

int serial_port_unsubscribe_trans() {
    if (sys_irqrmpolicy(&hook_id) != 0 ) {
        return 1;
    }

    //disable the recieved data interrupt
    uint32_t temp;
    if (sys_inb(UART_COM1 + UART_IER,&temp) != 0) {
        return 1;
    }
    uint8_t mask = ((uint8_t) temp) & ~IER_ENABLE_TRANS_EMPTY_INT;

    if (sys_outb(UART_COM1 + UART_IER,mask) != 0) {
        return 1;
    }

    queue_delete(transmit_data_queue);

  return 0;
}

void serial_port_ih() {
    uint32_t temp;

    sys_inb(UART_COM1 + UART_IIR,&temp);

    if ((temp & IIR_INTERRUPT_STATUS) == 0) {
        if (temp & IIR_REC_DATA_AVAILABLE) {
            queue_push(recieved_data_queue,serial_port_recieve());
            // valid_interrupt = true;
            // printf("valid\n");
        }
        else if (temp & IIR_TRANS_HOLD) {
            able_to_transmit = true;
        }
        else {
            printf("not_valid\n");
        }
    }
}


void serial_port_transmit() {
    if (!empty_queue(transmit_data_queue)) {
        serial_port_send(get_queue_front(transmit_data_queue));
        queue_pop(transmit_data_queue);
    }
}

void serial_port_add_to_transmit_queue(uint8_t elem) {
    queue_push(transmit_data_queue,elem);
}

uint8_t serial_port_read_recieved_queue() {
    uint8_t elem = get_queue_front(recieved_data_queue);
    queue_pop(recieved_data_queue);
    return elem;
}

