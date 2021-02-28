#ifndef TIMER_H
#define TIMER_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queuesys.h"
#include <time.h>

clock_t start_time;
void start_timer();
int check_time(int seconds);

#endif