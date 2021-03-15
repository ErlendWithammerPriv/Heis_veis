#include "queuesys.h"


void update_last_floor(int floor){
    last_floor = floor;
}
int add_node(Order order){
    Node* current_node = &head;
    while(current_node->next){
        if(current_node->next->order.floor== order.floor){
            add_flag(order);
            return 0;
        }
        current_node = current_node->next;
    }
    Node* new_node = (struct Node*)malloc(sizeof(struct Node));
 
    new_node->order=order;
    new_node->next= NULL;
    new_node->prev=current_node;
    current_node->next=new_node;
    add_flag(order);
    ordercount++;

    return 0;
}
int print_queue(){ //tregns ikke men fin å ha
    Node* current = &head;
    printf("Printqueue:\n\n");
    while(current!= NULL){
        printf("\nDette er etasjen: %d \n", current->order.floor);
        current = current->next;
    }
    return 0;
}

int add_flag(Order order)
{
    order_flags[order.type][order.floor]=1;
    hardware_command_order_light(order.floor, order.type, 1);
    return 0;
}


int clear_flag(int floor)
{
    for (int i=0;i<3;i++){
        order_flags[i][floor]=0;
        hardware_command_order_light(floor,i, 0);
    }
    return 0; 
}
int del_node(int floor){
    Node* current_node = head.next;
    while (current_node){
        if(current_node->order.floor == floor){
            current_node->prev->next = current_node->next;
            if(current_node->next){
                current_node->next->prev = current_node->prev;
            }
            free(current_node);
            clear_flag(floor);
            ordercount--;
            return 0;
        }
        current_node = current_node->next;
    }
    return 0;
}
int del_all_nodes(){
    for(int i =0;i<HARDWARE_NUMBER_OF_FLOORS;i++){
        del_node(i);
    }
    return 0;
}
int swap_nodes(Node* X, Node* Y){ //The nodes does not need to swap only the orders
    Order o = X->order;
    X->order=Y->order;
    Y->order=o;
    return 0;
}