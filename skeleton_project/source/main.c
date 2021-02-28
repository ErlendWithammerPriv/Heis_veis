#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <unistd.h>
#include "queuesys.h"
#include "drive.h"

static void clear_all_order_lights(){
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
}/*
int main(){ //dette er test main
    head.order.type=HARDWARE_ORDER_INSIDE;
    head.order.floor=-1;
    head.prev = NULL;
    head.next = NULL;
    last_floor =1;
    ordercount = 0;
    struct Order o1 ={.type=HARDWARE_ORDER_UP, .floor=2};
    struct Order o2 ={.type=HARDWARE_ORDER_DOWN, .floor=2};
    struct Order o3 ={.type=HARDWARE_ORDER_UP, .floor=4};
    struct Order o4 ={.type=HARDWARE_ORDER_UP, .floor=1};
    struct Order o5 ={.type=HARDWARE_ORDER_INSIDE, .floor=2};
    struct Order o6 ={.type=HARDWARE_ORDER_INSIDE, .floor=2};
    struct Order o7 ={.type=HARDWARE_ORDER_INSIDE, .floor=5};

    printf("Hello elevator\n");

    printf("o1: \t");
    add_node(o1);
    printf("o2: \t");
    add_node(o2);
    printf("o3: \t");
    add_node(o3);
    printf("o4: \t");
    add_node(o4);
    printf("o5: \t");
    add_node(o5);
    printf("o6: \t");
    add_node(o6);
    printf("o7: \t");
    add_node(o7);

    print_queue();

    del_node(2);

    print_queue();
    
    del_node(2);

    print_queue();

    del_node(4);
    del_node(1);

    print_queue();
    return 0;
}
*/

int main(){
    head.order.type=HARDWARE_ORDER_INSIDE;
    head.order.floor=-1;
    head.prev = NULL;
    head.next = NULL;
    last_floor =1;
    ordercount = 0;
    struct Order o1 ={.type=HARDWARE_ORDER_UP, .floor=2};
    struct Order o2 ={.type=HARDWARE_ORDER_DOWN, .floor=2};
    struct Order o3 ={.type=HARDWARE_ORDER_UP, .floor=4};
    struct Order o4 ={.type=HARDWARE_ORDER_UP, .floor=1};
    struct Order o5 ={.type=HARDWARE_ORDER_INSIDE, .floor=2};
    struct Order o6 ={.type=HARDWARE_ORDER_INSIDE, .floor=2};
    struct Order o7 ={.type=HARDWARE_ORDER_INSIDE, .floor=3};

    printf("Hello elevator\n");

  /*  printf("o1: \t");
    add_node(o1);
    printf("o2: \t");
    add_node(o2);
    printf("o3: \t");
    add_node(o3);
    printf("o4: \t");
    add_node(o4);
    printf("o5: \t");
    add_node(o5);
    printf("o6: \t");
    add_node(o6);*/
    printf("o7: \t");
    add_node(o7);

    print_queue();

 
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    while(1){
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        //Code block that makes the elevator go up when it reach the botton
        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }

        // Code block that makes the elevator go down when it reach the top floor
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }

        update_last_floor();
        if(ordercount){
            printf("ordercount = %d \n",ordercount);
            drive_lift();
        }
        print_queue();
        // Code to clear all lights given the obstruction signal 
        if(hardware_read_obstruction_signal()){
            hardware_command_stop_light(1);
            clear_all_order_lights();
        }
        else{
            hardware_command_stop_light(0);
        }
    }

    return 0;
}


/*
int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    while(1){
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        //Code block that makes the elevator go up when it reach the botton
        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }

        // Code block that makes the elevator go down when it reach the top floor
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }

        //All buttons must be polled, like this: 
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                update_last_floor(f);
                hardware_command_floor_indicator_on(f);
            }
        }
        for (int i =0; i < HARDWARE_NUMBER_OF_FLOORS;i++){
            if (hardware_read_floor_sensor(i)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                sleep(3);
                printf("En god natts søvn");
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
        }
         //Lights are set and cleared like this: 
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            // Internal orders 
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
            }

            // Orders going up 
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            }

            // Orders going down 
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
            }
        }

        // Code to clear all lights given the obstruction signal 
        if(hardware_read_obstruction_signal()){
            hardware_command_stop_light(1);
            clear_all_order_lights();
        }
        else{
            hardware_command_stop_light(0);
        }
    }

    return 0;
}
*/