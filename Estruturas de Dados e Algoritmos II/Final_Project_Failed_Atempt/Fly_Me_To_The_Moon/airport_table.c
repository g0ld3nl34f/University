#include "airport_table.h"

struct airport *airport_new(char airport_code[MAXAIRPORTCHAR]){
    struct airport *new = malloc(sizeof(struct airport));

    if (new == NULL)
    {
        free(new);
        return NULL;
    }

    else{
        strcpy(new -> airport_code, airport_code);
        new -> flights_occupied = 0;
        new -> change_in_disk = 1;
        new -> heap_position = -1;
        new -> flights = NULL;

        return new;
    }
}

struct airport_table *airport_table_new(){
    struct airport_table *new = malloc(sizeof(struct airport_table));

    for (int i = 0; i < MAXSIZE; ++i) {
        new -> table[i] = NULL;
    }

    return new;
}


int airport_hash(char airport_code[MAXAIRPORTCHAR], int i)
{
    long int hashKey = 0;
    int first = (int) airport_code[0] - TURNTOINT, second = (int) airport_code[1] - TURNTOINT, third = (int) airport_code[2] - TURNTOINT, fourth;

    if ((int) airport_code[3] == 0)
    {
        fourth = 0;
    }

    else{
        fourth = (int) airport_code[3] - TURNTOINT;
    }

    hashKey = ((26*26*26)*first) + ((26*26)*second) + (26*third) + fourth + (i * i);
    hashKey %= MAXSIZE;
    return hashKey;
}

bool airport_table_insert_new_airport(struct airport_table *airports, struct airport *new)
{
    int i = 0;

    while(i != MAXSIZE)
    {
        int hashKey = airport_hash(new -> airport_code, i);

        if (airports -> table[hashKey] == NULL)
        {
            airports -> table[hashKey] = new;
            airports -> table[hashKey] -> change_in_disk = 1;
            return true;
        }

        else{
            i++;
        }
    }

    return false;

}

bool airport_table_insert_new_flight(struct airport_table *airports, struct flight *to_list, int hash_key){
    if (airports -> table[hash_key] -> flights == NULL)
    {
        struct flight_link_list *new = flight_link_list_new();

        airports -> table[hash_key] -> flights = new;
        flight_link_list_insert(new, to_list);
        airports -> table[hash_key] -> flights_occupied++;

        return true;
    }

    if (airports -> table[hash_key] -> flights_occupied == MAXFLIGHTS - 1)
    {
        return false;
    }

    flight_link_list_insert(airports -> table[hash_key] -> flights , to_list);
    airports -> table[hash_key] -> flights_occupied++;

    return true;

}

bool airport_table_remove_flight(struct airport_table *airports, int departure_time, char arrival_airport[MAXAIRPORTCHAR], int hash_key)
{
    if (airports -> table[hash_key] -> flights == NULL)
    {
        return false;
    }

    bool removed = flight_link_list_remove(airports -> table[hash_key] -> flights, departure_time, arrival_airport);

    if (!removed)
    {
        return false;
    }

    airports -> table[hash_key] -> flights_occupied--;
    return true;
}

int airport_table_search_airport(struct airport_table *airports, char airport_code[MAXAIRPORTCHAR])
{
    int i = 0;

    while(i != MAXSIZE) {
        bool found = true;
        int hashKey = airport_hash(airport_code, i);

        if (airports -> table[hashKey] != NULL) {

            if (strcmp(airports-> table[hashKey]-> airport_code, airport_code) != 0) {
                found = false;
            }

            if (found == true) {
                return hashKey;
            }

            else {
                i++;
            }
        }

        else{
            return -1;
        }
    }

    return -1;
}

struct flight *airport_table_search_flight(struct airport_table *airports, int departure_time, char arrival_airport[MAXAIRPORTCHAR], int hash_key){
    struct flight *temp = flight_link_list_search(airports -> table[hash_key] -> flights, departure_time, arrival_airport);

    return temp;
}

void airport_table_write(FILE *airport_database, struct airport *to_write, int i){
    fseek(airport_database, i * sizeof(struct airport), SEEK_SET);

    fwrite(to_write, sizeof(struct airport), 1, airport_database);
}

struct airport *airport_table_read(FILE *airport_database, int i){
    fseek(airport_database, i * sizeof(struct airport), SEEK_SET);

    struct airport *temp = malloc(sizeof(struct airport));

    fread(temp, sizeof(struct airport), 1, airport_database);

    return temp;
}

void airport_table_clear_heap(struct airport_table *airports){
    for (int i = 0; i < MAXSIZE; ++i) {
        if (airports -> table[i] != NULL)
        {
            if (airports -> table[i] -> heap_position != -1)
            {
                airports -> table[i] -> heap_position = -1;
            }
        }
    }
}

void airport_table_destroy(struct airport_table *airports)
{
    for (int i = 0; i < MAXSIZE; ++i) {
        if(airports -> table[i] != NULL)
        {
            if (airports -> table[i] -> flights != NULL)
            {
                flight_link_list_destroy(airports -> table[i] -> flights);
            }

            free(airports->table[i]);
        }
    }

    free(airports);
}