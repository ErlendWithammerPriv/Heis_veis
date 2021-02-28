#ifndef QUEUESYS_H
#define QUEUESYS_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#define ORDER_QUEUE_SIZE 2*HARDWARE_NUMBER_OF_FLOORS
struct Order
{
    HardwareOrder type;
    int floor;

};

struct Node{
    struct Order order;
    struct Node* prev;
    struct Node* next;
};
struct Node head;
int ordercount;
int print_queue();

int order_equal(struct Order,struct Order);
int add_node(struct Order order);
int del_node(int floor);

int last_floor;
void update_last_floor();
//int get_floor(); //get the current floor kanskje helt unødvendig

#endif