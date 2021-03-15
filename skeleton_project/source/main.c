#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <unistd.h>
#include "queuesys.h"
#include "general.h"
#include "states.h"


int main(){
    head.order.floor = -1;
    door_open = 0;
    ordercount = 0;
    em_stop = 0;
    last_order.floor = -1;
    last_order.type = 1;
    mov = HARDWARE_MOVEMENT_STOP;
    
    

    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    } 
    clear_all_order_lights();
    prestate();

    while(1){
        
        switch (check_state())
        {
        case 4: 
            emergency_stop();
            break;
        case 3:
            obstruction();
            break;
        case 2:
            restart_after_stop();
            break;
        case 1:
            drive();
            break;
        default:
            break;
        }

    }

    return 0;
}
