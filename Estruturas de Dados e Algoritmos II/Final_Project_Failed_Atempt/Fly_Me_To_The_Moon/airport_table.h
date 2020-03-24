#ifndef TESTFINAL_AIRPORT_TABLE_H
#define TESTFINAL_AIRPORT_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "flight_link_list.h"
#define TURNTOINT 64
#define MAXSIZE 500009
#define MAXAIRPORTCHAR 5

struct airport{
    char airport_code[MAXAIRPORTCHAR];
    int flights_occupied, heap_position, change_in_disk;
    struct flight_link_list *flights;
};

struct airport_table{
    struct airport *table[MAXSIZE];
};

struct airport *airport_new(char airport_code[MAXAIRPORTCHAR]);
struct airport_table *airport_table_new();

int airport_hash(char airport_code[MAXAIRPORTCHAR], int i);
bool airport_table_insert_new_airport(struct airport_table *airports, struct airport *new);
bool airport_table_insert_new_flight(struct airport_table *airports, struct flight *to_list, int hash_key);
bool airport_table_remove_flight(struct airport_table *airports, int departure_time, char arrival_airport[MAXAIRPORTCHAR], int hash_key);
int airport_table_search_airport(struct airport_table *airports, char airport_code[MAXAIRPORTCHAR]);
struct flight *airport_table_search_flight(struct airport_table *airports, int departure_time, char arrival_airport[MAXAIRPORTCHAR], int hash_key);

void airport_table_write(FILE *airport_database, struct airport *to_write, int i);
struct airport *airport_table_read(FILE *airport_database, int i);

void airport_table_clear_heap(struct airport_table *airports);
void airport_table_destroy(struct airport_table *airports);
#endif

