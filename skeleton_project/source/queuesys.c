#include "queuesys.h"


void update_last_floor(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                last_floor=f+1;
                hardware_command_floor_indicator_on(f);
            }
        }
    }


int order_equal(struct Order o1, struct Order o2){
    if ((o1.floor==o2.floor)&&(o1.type==o2.type)){
        return 1;
    }
    return 0;
}
int add_node(struct Order order){

    struct Node* current_node = &head;
    struct Order default_order={.type=HARDWARE_ORDER_INSIDE, .floor=-3};
    struct Order nestes_order = default_order;
    struct Order neste_nestes_order = default_order;

    while (1){

        if(ordercount>=1){
            if(current_node->next!=NULL){
                nestes_order = current_node->next->order;
            }
            else {
                nestes_order = default_order;
            }
        }
       
        /*if(ordercount>=2){
            if(current_node->next->next!=NULL){
                neste_nestes_order = current_node->next->next->order;
            }
            else{
                neste_nestes_order = default_order;
            }
        }*/
        


        if(order_equal(current_node->order,order)||order_equal(nestes_order,order)||order_equal(neste_nestes_order,order)){
            printf("helt lik\n");
            return 0; //2 betyr order equal
        }
        else if(current_node->order.floor==order.floor){
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            new_node->order=order;
            new_node->prev=current_node;
            new_node->next=current_node->next;
            printf("SAMME FLOOR\n");
            if((current_node->next!=NULL)){
                current_node->next->prev = new_node; 
            }
            current_node->next=new_node;
            ordercount++;
            hardware_command_order_light(order.floor-1, order.type, 1);

            return 0;
        }
        else if(current_node->next==NULL){
            printf("lagt bakerst \n");
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            new_node->order=order;
            current_node->next = new_node;
            new_node->prev=current_node;
            new_node->next= NULL;
            ordercount++;
            hardware_command_order_light(order.floor-1, order.type, 1);
            return 0; //3 betyr bakerst;
        }
        current_node = (current_node->next);
    }
    return 1; //1 betyr feil
}

int print_queue(){
    struct Node* current = &head;
    printf("Printqueue:\n\n");
    while(current!= NULL){
        printf("\nDette er etasjen: %d \n", current->order.floor);
        current = current->next;
    }
    return 0;
}

int del_node(int floor){
    if(head.next==NULL){
        printf("Trying to remove order from empty queue\n");
        return 1;
    }
    while(head.next->order.floor==floor){ //maks tre bestillinger til samme etasje denne sjeker om noden etter head har samme etasje som floor
        struct Node* first = head.next; // her er koden plasseffetkiv over tidseffetkiv forklar hvorfor

        head.next = first->next;
        if(first->next!=NULL){
            first->next->prev= &head;
        }
        hardware_command_order_light(first->order.floor-1,first->order.type, 0);
        free(first);
        ordercount--;
        
        if(head.next==NULL){
            break;
        }
    }
    return 0; //bytt dette til 0 når du vet det funker
}