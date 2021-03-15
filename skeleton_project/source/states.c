 #include "states.h"

int check_state(){
    

    if(hardware_read_stop_signal()){
        hardware_command_stop_light(1);
        return 4;
    }
    hardware_command_stop_light(0);
    read_buttons();

    if(hardware_read_obstruction_signal() && door_open ){
        return 3;
    }

    if(em_stop){
        return 2;
    }

    if(time_since_timer_reset()>=OPEN_DOOR_TIME){
        hardware_command_door_open(0);
        door_open = 0;
        if(time_since_timer_reset()> OPEN_DOOR_TIME){
            last_order.floor = -1;
            last_order.type = 1;
        }       
        if(ordercount){
            return 1;
        }
    }

    return 0;
}

int drive(){
    int destination = head.next->order.floor;
    
    if(destination - last_floor>0){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        dir = 0;
    }
    else if(destination - last_floor<0){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        dir = 2;
    }

    int fl = read_all_floors();
    if(fl){
        update_last_floor(fl-1); //minus 1 since r_a_f is shifted'
        if(order_flags[HARDWARE_ORDER_INSIDE][fl-1]){
            last_order = head.next->order;
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            del_node(fl-1);
            open_door_and_restart_timer();
            return 0;
        }

        switch(dir){
            case 2:
                mov = HARDWARE_MOVEMENT_DOWN;
                if(order_flags[HARDWARE_ORDER_DOWN][fl-1]){
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    del_node(fl-1);
                    open_door_and_restart_timer();
                    return 0;
                }
                break;
            case 0: 
                mov = HARDWARE_MOVEMENT_UP;
                if(order_flags[HARDWARE_ORDER_UP][fl-1]){
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    del_node(fl-1);
                    open_door_and_restart_timer();
                    return 0;
                }
                break;
            default:
                break;
        }

        Node* current = head.next->next; //Dette er nytt husk å teste men jeg tror det skal funke fett
        Node* first = head.next;        // det er også en ny funksjon i queuesys som kan være et problem
        switch(dir){
            case 2:
                if(first->order.type==HARDWARE_ORDER_UP){
                    while(current){
                        if(current->order.type==HARDWARE_ORDER_UP && current->order.floor < first->order.floor){
                            swap_nodes(current,first);
                            return 0;
                        }
                        current = current->next;
                    }
                }
                break;
            case 0:
                if(first->order.type==HARDWARE_ORDER_DOWN){
                    while(current){
                        if(current->order.type==HARDWARE_ORDER_DOWN && current->order.floor > first->order.floor){
                            swap_nodes(current, first);
                            return 0;
                        }
                        current = current->next;
                    }
                }
                break;
            default:
                break;
        }

        if(destination == fl-1){ 
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            del_node(fl-1);
            open_door_and_restart_timer();
        }

        
    }
    return 0;
}

int obstruction(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    open_door_and_restart_timer();
    return 0;
}

int emergency_stop(){
    if(read_all_floors()){
        open_door_and_restart_timer();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    del_all_nodes();
    em_stop = 1;
    return 0;
}

int restart_after_stop(){
    if(read_all_floors()){ //if nothing is in the queue or the elevator is at a floor all is good
        em_stop = 0;
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        return 0;
    }
    if(head.next != NULL){
        if(head.next->order.floor == last_floor){
            switch(mov){
                case 2:
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                    break;
                case 0:
                    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                    break;
                default:
                    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                    break;
            }
            return 0;
        }
        em_stop = 0;
    }
    return 0;
}