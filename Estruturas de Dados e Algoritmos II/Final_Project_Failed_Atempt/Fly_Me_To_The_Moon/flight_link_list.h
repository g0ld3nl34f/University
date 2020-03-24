#ifndef TESTFINAL_FLIGHT_LINK_LIST_H
#define TESTFINAL_FLIGHT_LINK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXFLIGHTS 151
#define MAXAIRPORTCHAR 5

//declaration of a node from a list;
struct flight
{
    int duration, departure_time;
    char arrival_airport[MAXAIRPORTCHAR];
    struct flight *next;
};

//declaration of a list;
struct flight_link_list
{
    int change_in_disk;
    struct flight *head;
};

struct flight *flight_new(int departure_time, int duration, char arrival_airport[MAXAIRPORTCHAR]);
struct flight_link_list *flight_link_list_new();

void flight_link_list_insert(struct flight_link_list *flights, struct flight *to_insert);
bool flight_link_list_remove(struct flight_link_list *flights, int departure_time, char arrival_airport[MAXAIRPORTCHAR]);
struct flight *flight_link_list_search(struct flight_link_list *flights, int departure_time, char arrival_airport[MAXAIRPORTCHAR]);
struct flight_link_list *flight_link_list_read(FILE *flights_database, int i);
void flight_link_list_write(FILE *flights_database, struct flight_link_list *to_write, int i);

void flight_link_list_destroy(struct flight_link_list *flights);
#endif