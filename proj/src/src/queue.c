#include <lcom/lcf.h>
#include "../include/queue.h"


queue_t* queue_init() {
    queue_t* queue = malloc(sizeof(queue_t));

    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

bool empty_queue(queue_t* queue) {
    if (queue->front == NULL && queue->rear == NULL) {
        return true;
    }
    else {
        return false;
    }
}

int queue_push(queue_t* queue, uint8_t item) {
    node_t* new_node = malloc(sizeof(node_t));

    if (new_node == NULL) {
        return 1;
    }

    new_node->data = item;
    new_node->next = NULL;

    //insert first node if the queue is empty
    if (empty_queue(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    }
    else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    return 0;
}

//in this implementation you cant insert the -1 value in the queue!!
int queue_pop(queue_t* queue) {
    if (empty_queue(queue)) {
        return 1;
    }
    else {
        if (queue->front == queue->rear) { //if there is only one element
            node_t* delete = queue->front;
            queue->front = NULL;
            queue->rear = NULL;
            free(delete);
        }
        else {
            node_t* delete = queue->front;
            queue->front = queue->front->next;
            free(delete);
        }
        return 0;
    }
} 

uint8_t get_queue_front(queue_t* queue) { 
    return queue->front->data;
}
 

void queue_delete(queue_t* queue) {
    while(!empty_queue(queue)) {
        queue_pop(queue);
    }
    free(queue);
}

