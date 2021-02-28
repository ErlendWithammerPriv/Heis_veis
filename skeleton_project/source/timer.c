#include "timer.h"

void start_timer()
{
    start_time = clock();
}

int check_time(int seconds)
{
    clock_t difference = clock() - start_time;
    int time_passed = difference / CLOCKS_PER_SEC;
    return time_passed == seconds;
}
  