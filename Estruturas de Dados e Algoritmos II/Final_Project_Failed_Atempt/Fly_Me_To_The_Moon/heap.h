#ifndef TEST_HEAP_H
#define TEST_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "airport_table.h"
#define INFINITY 100000000
#define MAXSIZE 500009
#define MAXAIRPORTCHAR 5

struct vertice{
    int duration;
    char airport_code[MAXAIRPORTCHAR], predecessor[MAXAIRPORTCHAR];
    struct flight* flight_from;
};

struct heap{
    struct vertice *heap_array[MAXSIZE];
    int size;
};

struct heap *heap_new();
struct vertice *vertice_new(int duration, char airport_code[MAXAIRPORTCHAR]);

void change(struct vertice *x, struct vertice *y);
int parent(int i);
int left_child(int i);
int right_child(int i);

int heap_insert(struct heap *priority_queue, struct vertice *to_insert, struct airport_table *airports);
void heap_decrease_key(struct heap *priority_queue, struct airport_table * airports, int i);
void heap_heapify(struct heap *priority_queue, struct airport_table *airports, int i);
struct vertice *heap_extract_min(struct heap *priority_queue, struct airport_table *airports);
void heap_delete_key(struct heap *priority_queue, struct airport_table *airports, int i);
void heap_destroy(struct heap *priority_queue, struct airport_table *airports);

#endif