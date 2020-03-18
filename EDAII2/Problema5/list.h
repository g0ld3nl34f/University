#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#define EMPTY_LIST 0
#define MAX_LIST_SIZE 20

struct node;

struct node *new_node(int second_element);
void destroy_node(struct node *this_node);

struct list;

struct list *new_list(int first_element);
_Bool element_in_list(struct list *this_list, int second_element); 
void insert_node_in_list(struct list *this_list, int second_element); 
void destroy_node_in_list(struct list *this_list, int second_element);
void print_list(struct list *this_list);
short get_size_list(struct list *this_list);
void destroy_list(struct list *this_list);

#endif