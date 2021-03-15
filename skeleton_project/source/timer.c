#include "timer.h"

void start_timer()
{
    start_time = clock();
}

int time_since_timer_reset(){
    clock_t difference = clock() - start_time;
    int time_passed = difference / CLOCKS_PER_SEC;
    return time_passed;
}