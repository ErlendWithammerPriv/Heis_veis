/**
 * @file
 * @brief The different states of the state machine
 *
 */
#ifndef STATES_H
#define STATES_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "general.h"
#include "queuesys.h"
/**
 * @brief Drives the elevator to the floor of the first element in the queue
 */

int drive();
/**
 * @brief Stops the elevator and deletes the queue if the stop button is pressed
 */
int emergency_stop();
/**
 * @brief Holds the door open and the elevator stopped if obstuction signal is high
 */
int obstruction();
/**
 * @brief Handles restart process if @c em_stop flag is high
 */
int restart_after_stop();
/**
 * @brief Checks the state the elevator should be in
 * @return 4 if stop button is pressed, 
 * 3 if obstruction is high and the door is open, 
 * 2 if there is an unhandled stop incident, 
 * 1 if the door has been open for OPEN_DOOR_TIME and orderqueue is non-zero
 * 0 otherwise.
 */
int check_state();

int open_door_once;
int dir;

#endif