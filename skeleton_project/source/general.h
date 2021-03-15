/**
 * @file
 * @brief general functions for the elevator behaviour.

 */
#ifndef GENERAL_H
#define GENERAL_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include "queuesys.h"
#include "timer.h"

#define OPEN_DOOR_TIME 3
/** 
 * @brief Clears all order lights,
 * used for turning off any odd light in the initializing phase
 */
int clear_all_order_lights();
/**
 * @brief Loop through all floor indicators and checks for the elevator
 * The return value of the first floor is 1, second floor 2 etc.
 * Note: This function is not zero-indexed unlike the rest of the program
 * @return Returns the floor number where the elevator is located incremented by 1, otherwise 0. 
 */
int read_all_floors();
/**
 * @brief Sends the elevator to the closest floor down if in an undefined state, otherwise nothing
 */
int prestate();

/**
 * @brief Opens the door and restarts the open door timer
 */
int open_door_and_restart_timer();
/**
 * @brief Polls all the buttons for new orders and adds them to the queue
 */
int read_buttons();

/**
 * @brief Flag for unhandled stop event
 */
int em_stop;
/**
 * @brief Flag for door state,
 * 1 for open 0 for closed
 */
int door_open;
/**
 * @brief Direction of movement
 */
HardwareMovement mov;


#endif