/**
 * @file
 * @brief Timer
 *
 */
#ifndef TIMER_H
#define TIMER_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queuesys.h"
#include <time.h>

/**
 * @brief Time of last restart
*/
clock_t start_time;
/**
 * @brief Starts the timer 
 */
void start_timer();
/**
 * @brief Checks when last restart happend
 * @return Returns the time of the last restart
*/
int time_since_timer_reset();


#endif