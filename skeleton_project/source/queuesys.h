/**
 * @file
 * @brief Queue system for the orders
 *
 */
#ifndef QUEUESYS_H
#define QUEUESYS_H
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include "general.h"
/**
 * @brief Order type used in @c add_node
 */
typedef struct Order
{
    HardwareOrder type;
    int floor;

}Order;
/**
 * @brief Node used in doubly linked list queue.
 */
typedef struct Node{
    struct Order order;
    struct Node* prev;
    struct Node* next;
} Node;
/**
 * @brief The anchour of the queue.
 */
Node head;
/**
 * @brief Number of orders in queue.
 */
int ordercount;
/**
 * @brief Prints the queue. Head is printed as -1
 */
int print_queue();
/**
 * @brief Adds a new order to the queue. 
 * @param order the order to be added to the queue.
 */
int add_node(Order order);
/**
 * @brief Swaps the order of two nodes in the queue. Before: queue: X-Y, After: queue: Y-X
 * @param Node X 
 * @param Node Y
 */
int swap_nodes(Node* X, Node* Y);
/**
 * @brief Removes the orders on the specific floor floor from the queue.
 * @param floor the floor to be removed
 */
int del_node(int floor);
/**
 * @brief Deletes the entire queue.
 */
int del_all_nodes();
/**
 * @brief Last floor the elevator was at.
 */
int last_floor;
/**
 * @brief Updates the last floor variable to floor floor.
 * @param floor the value given to last floor
 */
void update_last_floor(int floor);
/**
 * @brief The array of order flags.
 * [3] = {UP, INSIDE, DOWN} - Order type
 * [4] = {0, 1, 2, 3} - Floor
 */
int order_flags[3][4]; // 3 nedover (up,inside,down) 4 bortover (etasje 1,2,3,4)
/**
 * @brief Sets flag in @c order_flags at oderflags[order.type][order.floor]
 * @param order The order to be flagged
 */
int add_flag(Order order);//legg til et flag på en bestilling
/**
 * @brief Clear all flags at the floor floor
 * @param floor The floor to which all flags will be clared
 */
int clear_flag(int floor);//clear en hel etasje av flags når den stopper der
Order last_order;


#endif