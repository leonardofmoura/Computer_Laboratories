#ifndef _QUEUE_H_
#define _QUEUE_H_

/** @defgroup queue queue
 * @{
 *
 * A queue data structure class
 */


typedef struct node node_t;

/**
 * @brief Represents a single node of the queue 
 * 
 */
struct node{
    /*@{*/
    uint8_t data;       /**<  @brief  The data contained in a node*/
    node_t* next;       /**<  @brief  A pointer to the next node in the queue*/
    /*@}*/
};


/**
 * @brief Represents the queue itself
 * 
 */
typedef struct {
    /*@{*/
    node_t* front;      /**<  @brief  Pointer to the node in the front of the queue*/
    node_t* rear;       /**<  @brief  Pointer to the node in the rear of the queue*/
    /*@}*/
} queue_t;

/**
 * @brief Creates a new queue object
 * 
 * @return queue_t* Pointer to the queue object created 
 */
queue_t* queue_init();

/**
 * @brief Tells if a queue is empety or not
 * 
 * @param queue Pointer to the queue to be testes 
 * @return true The queue is empet
 * @return false The queue is not empety
 */
bool empty_queue(queue_t* queue);

/**
 * @brief Inserts a new item in the rear of the queue 
 * 
 * @param queue Pointer to the queue we want to insert the character in
 * @param item Item we want to insert in the queue
 * @return int Returns 0 on success, 1 otherwise
 */
int queue_push(queue_t* queue, uint8_t item);

/**
 * @brief Pops the item in the front of the queue
 * 
 * @param queue Pointer to queue we want to pop
 * @return int Returns 0 on success, 1 otherwise
 */
int queue_pop(queue_t* queue);

/**
 * @brief Gets the item in the front of the queue 
 * 
 * @param queue Pointer to the queue we want to get the item
 * @return uint8_t Data contained in the front of the queue
 */
uint8_t get_queue_front(queue_t* queue);

/**
 * @brief Deletes a queue object
 * 
 * @param queue Pointer to the queue to be deleted
 */
void queue_delete(queue_t* queue);

/**@}*/

#endif

