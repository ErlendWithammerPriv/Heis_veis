#include "drive.h"



int drive_lift(){
    int to_floor = head.next->order.floor;
    HardwareMovement movement;
    
    while(to_floor != last_floor){
        while(hardware_read_obstruction_signal()){
            read_buttons();
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            //printf("obs er 1 og i er %lld\n",i);
            
            print_queue();
        }
        while(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
        int direction = to_floor-last_floor; //positiv direction betyr heisen skal opp
        //printf("obs er 0 og direction er %d\n ",direction);
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
        read_buttons();
        update_last_floor();
    }
    start_timer();
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_door_open(1);
    while(!check_time(1)){
    
    }
    
    del_node(to_floor);
    return 0;
}

int drive_to_first(){
    while(!hardware_read_floor_sensor(0)){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        printf("dette er sensor i første: %d\n", hardware_read_floor_sensor(0));
    }
    return 0;
}