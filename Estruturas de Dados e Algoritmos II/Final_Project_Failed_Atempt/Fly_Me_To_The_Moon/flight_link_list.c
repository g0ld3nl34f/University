#include "flight_link_list.h"

//a new node is allocated in memory;
struct flight *flight_new(int departure_time, int duration, char arrival_airport[MAXAIRPORTCHAR])
{
    struct flight *new = malloc(sizeof(struct flight));

    if (new == NULL)
    {
        free(new);
        return NULL;
    }

    new -> departure_time = departure_time;
    new -> duration = duration;
    strcpy(new -> arrival_airport, arrival_airport);
    new -> next = NULL;

    return new;
}

//a new list is allocated in memory;
struct flight_link_list *flight_link_list_new()
{
    struct flight_link_list *new = malloc(sizeof(struct flight_link_list));

    new -> head = NULL;

    new -> change_in_disk = 1;

    return new;
}

//a new node is allocated in memory and inserted into a list;
void flight_link_list_insert(struct flight_link_list *flights, struct flight *to_insert)
{
    if (flights -> head == NULL)
    {
        flights -> head = to_insert;
        flights -> change_in_disk = 1;
        return;
    }

    to_insert -> next = flights -> head;
    flights -> head = to_insert;
    flights -> change_in_disk = 1;
}

bool flight_link_list_remove(struct flight_link_list *flights, int departure_time, char arrival_airport[MAXAIRPORTCHAR]){
    struct flight *temp = flights -> head;

    if (temp -> next == NULL)
    {
        if (strcmp(temp -> arrival_airport, arrival_airport) == 0 && temp -> departure_time == departure_time)
        {
            flights -> head = NULL;
            free(temp);
            flights -> change_in_disk = 1;
            return true;
        }
    }

    struct flight *aux = temp;
    temp = temp -> next;

    if (strcmp(aux -> arrival_airport, arrival_airport) == 0 && aux -> departure_time == departure_time)
    {
        flights -> head = temp;
        free(aux);
        flights -> change_in_disk = 1;
        return true;
    }

    while (temp != NULL)
    {
        if (strcmp(temp -> arrival_airport, arrival_airport) == 0 && temp -> departure_time == departure_time)
        {
            aux -> next = temp -> next;
            free(temp);
            flights -> change_in_disk = 1;
            return true;
        }

        aux = aux -> next;
        temp = temp -> next;
    }

    return false;
}

//a node is searched in a given list;
struct flight *flight_link_list_search(struct flight_link_list *flights, int departure_time, char arrival_airport[MAXAIRPORTCHAR])
{
    struct flight *temp = flights -> head;

    while (temp != NULL)
    {
        if (strcmp(temp -> arrival_airport, arrival_airport) == 0 && temp -> departure_time == departure_time)
        {
            return temp;
        }

        temp = temp -> next;
    }

    return NULL;
}

void flight_link_list_write(FILE *flights_database, struct flight_link_list *to_write, int i)
{
    struct flight *temp;

    fseek(flights_database, i * sizeof(struct flight) * MAXFLIGHTS, SEEK_SET);

    if (to_write == NULL)
    {
        temp = flight_new(0, 0, "\0\0\0\0\0");
        fwrite(temp, sizeof(struct flight), 1, flights_database);

        free(temp);
        return;
    }

    temp = to_write -> head;

    while (temp != NULL)
    {
        fwrite(temp, sizeof(struct flight), 1, flights_database);

        temp = temp -> next;
    }

    temp = flight_new(0, 0, "\0\0\0\0\0");
    fwrite(temp, sizeof(struct flight), 1, flights_database);

    free(temp);
}

struct flight_link_list *flight_link_list_read(FILE *flights_database, int i){
    fseek(flights_database, i * sizeof(struct flight) * MAXFLIGHTS, SEEK_SET);

    struct flight *temp = malloc(sizeof(struct flight));
    struct flight_link_list *from_disk = flight_link_list_new();

    fread(temp, sizeof(struct flight), 1, flights_database);

    if (temp == NULL)
    {
        return NULL;
    }

    temp -> next = NULL;
    flight_link_list_insert(from_disk, temp);

    temp = malloc(sizeof(struct flight));
    fread(temp, sizeof(struct flight), 1, flights_database);

    while (strcmp(temp -> arrival_airport, "\0\0\0\0\0") != 0)
    {
        temp -> next = NULL;
        flight_link_list_insert(from_disk, temp);

        temp = malloc(sizeof(struct flight));
        fread(temp, sizeof(struct flight), 1, flights_database);
    }

    return from_disk;
}

//the given list is freed from memory
void flight_link_list_destroy(struct flight_link_list *flights)
{
    struct flight *current = flights -> head, *temp;

    while (current != NULL)
    {
        temp = current -> next;
        free(current);
        current = temp;
    }

    free(current);
    free(flights);
}