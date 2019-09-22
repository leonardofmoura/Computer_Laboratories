#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#define START_SEND      0xFF

/** @defgroup event_manager event_manager
 * @{
 *
 * Controls all the flow of the game and manages interrupts from different devices
 */


/**
 * @brief All the game states
 * 
 */
enum State {
    /*@{*/
    LOAD = 0,               /**<  @brief  Loading the game*/
    MENU,                   /**<  @brief  Main menu*/
    GAME,                   /**<  @brief  In-game*/
    PAUSE,                  /**<  @brief  Pause menu*/
    GAME_C,                 /**<  @brief  In-game but the game was resumed*/
    EXIT,                   /**<  @brief  Exit game*/
    SPECTATE_WAIT,          /**<  @brief  Waiting for game to start*/
    SPECTATE_WAITING_INFO,  /**<  @brief  Waiting to recieve terrain generation seed*/
    SPECTATE_RUNNING        /**<  @brief  Spectating a running game*/
    /*@}*/
};

/**
 * @brief All the possible events
 * 
 */
enum Event {
    /*@{*/
    INIT_COMPLETE = 0,      /**<  @brief  Loading complete*/
    START_GAME,             /**<  @brief  Start game*/      
    EXIT_GAME,              /**<  @brief  Exit game*/
    PAUSE_GAME,             /**<  @brief  Pause game*/
    CONTINUE_GAME,          /**<  @brief  Continue game*/
    START_REC,              /**<  @brief  Recieved start game packet*/
    NO_EVENT                /**<  @brief  No event ocurred*/
    /*@}*/
};

/**
 * @brief All the devices that generate interrupts
 * 
 */
enum Device {
    TIMER = 0,      /**<  @brief  The Timer*/
    KEYBOARD,       /**<  @brief  The Keyboard*/
    MOUSE,          /**<  @brief  The mouse*/
    RTC,            /**<  @brief  The Real Time Clock*/
    SERIAL_PORT     /**<  @brief  The Serial Port*/
};

/**
 * @brief Runs the event manager for a game state and an event
 * 
 * @param curr_state Current game state 
 * @param event The event that ocurred
 * @param state_loaded Tells if the returned state is to be loaded or not
 */
void run_event_manager(enum State* curr_state, enum Event event, bool* state_loaded);

/**
 * @brief Loads a game state
 * 
 * @param State Game state to be loaded
 * @return int 0 if the load was successfull, 1 otherwise
 */
int load_state(enum State curr_state);

/**
 * @brief Manages and interrupt according to a device and a game state
 * 
 * @param curr_state Current state of the game 
 * @param device Device that generated the interruput 
 * @return enum Event Event that results with that interrupt 
 */
enum Event manage_interrupt(enum State curr_state, enum Device device);

/**
 * @brief Manages a comunication: does the required action according to the adata received
 * 
 * @param data_received Byte received through the serial port
 */
void manage_comunication(uint8_t data_received);

/**@}*/

#endif
