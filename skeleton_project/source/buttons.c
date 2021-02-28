#include "buttons.h"

int read_buttons(){
    for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
        for(int j=0; j<3;j++){
            if(hardware_read_order(i,j)){
                struct Order new_order = {.type=j, .floor=i+1};
                printf("Etasje %d, type %d og read %d \n",i+1,j,hardware_read_order(i,j));
                add_node(new_order); //om orderen faktsk skal inn i queue-en sjekkes i add_node
                //dermed er det naturlig at lyset kun settes der
            }
        }
    }
    return 0;
}