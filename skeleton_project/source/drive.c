#include "drive.h"



int drive_lift(){
    int to_floor = head.next->order.floor;
    HardwareMovement movement;
    
    while(to_floor != last_floor){
        int direction = to_floor-last_floor; //positiv direction betyr heisen skal opp
        if(direction>0){
            movement=HARDWARE_MOVEMENT_UP;
        }
        else{
            movement=HARDWARE_MOVEMENT_DOWN;
        }
        /*printf("Differanse mellom floor: %d \n",to_floor-last_floor);
        printf("Last_floor: %d \n",last_floor);
        printf("To_floor: %d \n",to_floor);*/
        hardware_command_door_open(0); //Lukker døren før vi kjører
        hardware_command_movement(movement);
        update_last_floor();
    }
    start_timer();
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_door_open(1);
    while(!check_time(3)){
    
    }
    //Åpner døren
    del_node(to_floor);
    return 0;
}