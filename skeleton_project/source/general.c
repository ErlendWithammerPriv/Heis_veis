#include "general.h"

int clear_all_order_lights(){ //tregs egentlig ikke men greit bare i tilfelle
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
    return 0;
}
int read_all_floors(){ //returns the floor that the elevator is on +1, this is a bit confusing but it means we kan use 0 for false
    for(int i=0;i<HARDWARE_NUMBER_OF_FLOORS;i++){
        if(hardware_read_floor_sensor(i)){
            hardware_command_floor_indicator_on(i);
            return i+1;
        }
    }
    return 0;
    }

int prestate(){
    if(!read_all_floors()){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        prestate();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    return 0;
}

int open_door_and_restart_timer(){
    start_timer();
    hardware_command_door_open(1);
    door_open = 1;
    return 0;
}

int read_buttons(){
    
    for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
        for(int j=0; j<HARDWARE_NUMBER_OF_BUTTONS;j++){
            if(hardware_read_order(i,j)){
                Order new_order = {.type=j, .floor=i};
                if(new_order.floor == last_order.floor && new_order.type == last_order.type){
                    return 0;
                }
                add_node(new_order); //om orderen faktsk skal inn i queue-en sjekkes i add_node
                //dermed er det naturlig at lyset kun settes der
            }
        }
    }
    return 0;
}
