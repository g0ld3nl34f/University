#include <stdio.h>
#include <string.h>
#include "airport_table.h"
#include "heap.h"

#define AIRPORTSDATABASE "airport_database"
#define COMMANDMAXCHAR 3
#define MINUTESINADAY 1440
#define MINCONNECTIONTIME 30


FILE *open_airports()
{
    FILE *new = fopen(AIRPORTSDATABASE, "r+");

    if (new == NULL)
    {
        new = fopen(AIRPORTSDATABASE, "w+");

        fseek(new, 0, SEEK_SET);

        struct airport *temp = airport_new("\0\0\0\0\0");

        fwrite(temp, sizeof(struct airport), 1, new);

        free(temp);

        return new;
    }


    return new;
}


void read_file(FILE *airports_database, struct airport_table *airports){
    struct flight *flight_to_table = NULL;
    struct airport *airport_to_table = NULL;

    fseek(airports_database, 0, SEEK_SET);

    for (int i = 0; i < MAXSIZE; ++i)
    {
        airport_to_table = malloc(sizeof(struct airport));

        fread(airport_to_table, sizeof(struct airport), 1, airports_database);

        if (strcmp(airport_to_table -> airport_code, "\0\0\0\0\0") == 0)
        {
            free(airport_to_table);
            return;
        }

        airport_to_table -> flights = NULL;
        airport_table_insert_new_airport(airports, airport_to_table);

        flight_to_table = malloc(sizeof(struct flight));

        fread(flight_to_table, sizeof(struct flight), 1, airports_database);

        while (strcmp(flight_to_table -> arrival_airport, "\0\0\0\0\0") != 0)
        {
            airport_table_insert_new_flight(airports, flight_to_table, airport_table_search_airport(airports, airport_to_table -> airport_code));

            flight_to_table = malloc(sizeof(struct flight));

            fread(flight_to_table, sizeof(struct flight), 1, airports_database);
        }

        free(flight_to_table);
    }

}

void write_file(FILE *airports_database, struct airport_table *airports){
    struct airport* to_write, *airports_end = malloc(sizeof(struct flight));
    struct flight *to_write_after, *flights_end = malloc(sizeof(struct flight));

    fseek(airports_database, 0, SEEK_SET);

    for (int i = 0; i < MAXSIZE; ++i)
    {
        to_write = airports -> table[i];

        if(to_write != NULL)
        {
            fwrite(to_write, sizeof(struct airport), 1, airports_database);

            if (to_write -> flights != NULL)
            {
                to_write_after = to_write -> flights -> head;

                while (to_write_after != NULL)
                {
                    fwrite(to_write_after, sizeof(struct flight), 1, airports_database);
                    to_write_after = to_write_after -> next;
                }
            }

            fwrite(flights_end, sizeof(struct flight), 1, airports_database);
        }
    }

    fwrite(airports_end, sizeof(struct airport), 1, airports_database);

    free(airports_end);
    free(flights_end);
}

struct heap *make_graph(struct airport_table *airports, char departure_airport[MAXAIRPORTCHAR])
{
    int position;
    struct heap *priority_queue = heap_new();

    for (int i = 0; i < MAXSIZE; ++i) {
        if (airports -> table[i] != NULL)
        {
            if (airports -> table[i] -> heap_position == -1)
            {
                if (strcmp(airports -> table[i] -> airport_code, departure_airport) == 0)
                {
                    position = heap_insert(priority_queue, vertice_new(0, departure_airport), airports);
                    airports -> table[i] -> heap_position = position;
                }

                else{
                    position = heap_insert(priority_queue, vertice_new(INFINITY,airports -> table[i] -> airport_code), airports);
                    airports -> table[i] -> heap_position = position;
                }
            }
        }
    }

    return priority_queue;
}

struct vertice *find_shortest_paths(struct airport_table *airports, char departure_airport[MAXAIRPORTCHAR], char arrival_airport[MAXAIRPORTCHAR], int time_of_departure, struct heap *s) {
    int arrival_time = 0, curr_distance = 0;
    struct heap *priority_queue = make_graph(airports, departure_airport);
    struct vertice *visiting = NULL, *flight_to_here = NULL;
    struct flight_link_list *search_flights = NULL;
    struct flight *calculate_distance = NULL;

    while (priority_queue->size > 0) {

        visiting = heap_extract_min(priority_queue, airports);

        if (visiting->duration != 0) {
            if (strcmp(visiting->predecessor, "\0\0\0\0\0") == 0) {
                heap_insert(s, visiting, airports);
                continue;
            }
        }

        if (visiting -> duration == 0)
        {
            arrival_time = time_of_departure;
        }

        else{
            if (visiting -> flight_from != NULL)
            {
                arrival_time = time_of_departure + visiting -> duration;
            }
        }

        if (arrival_time > MINUTESINADAY)
        {
            arrival_time %= MINUTESINADAY;
        }

        search_flights = airports->table[airport_table_search_airport(airports, visiting->airport_code)]->flights;

        if (search_flights != NULL) {
            calculate_distance = search_flights->head;

            while (calculate_distance != NULL) {
                if (strcmp(calculate_distance->arrival_airport, departure_airport) != 0)
                {
                    if (s -> heap_array[airports -> table[airport_table_search_airport(airports, calculate_distance -> arrival_airport)] -> heap_position] != NULL)
                    {
                        if (strcmp(s -> heap_array[airports -> table[airport_table_search_airport(airports, calculate_distance -> arrival_airport)] -> heap_position] -> airport_code, calculate_distance -> arrival_airport) == 0)
                        {
                            calculate_distance = calculate_distance -> next;
                            continue;
                        }
                    }

                    flight_to_here = priority_queue -> heap_array[airports -> table[airport_table_search_airport(airports, calculate_distance -> arrival_airport)] -> heap_position];

                    if (visiting -> duration == 0)
                    {
                        curr_distance = 0;
                    }

                    else{
                        curr_distance = MINCONNECTIONTIME;
                    }

                    if (arrival_time + curr_distance <= calculate_distance -> departure_time)
                    {
                        curr_distance = calculate_distance -> departure_time - arrival_time;
                    }

                    else{
                        curr_distance = MINUTESINADAY - arrival_time;
                        curr_distance += calculate_distance -> departure_time;
                    }

                    curr_distance += calculate_distance -> duration;

                    if (flight_to_here -> duration > visiting -> duration + curr_distance)
                    {
                        flight_to_here -> duration = visiting -> duration + curr_distance;
                        flight_to_here -> flight_from = calculate_distance;
                        strcpy(flight_to_here -> predecessor, visiting -> airport_code);
                    }

                    calculate_distance = calculate_distance->next;
                }

                else{
                    calculate_distance = calculate_distance->next;
                }

            }

            /*if (flight_to_here != NULL)
            {
                heap_heapify(priority_queue, airports, parent(airports -> table[airport_table_search_airport(airports, flight_to_here -> airport_code)] -> heap_position));

            }

            flight_to_here = NULL;*/

        }

        if (strcmp(visiting -> airport_code, arrival_airport) == 0)
        {
            heap_insert(s, visiting, airports);

            /*for (int i = 0; i < MAXSIZE; ++i) {
                if (priority_queue -> heap_array[i] != NULL)
                {
                    visiting = priority_queue -> heap_array[i];

                    if (s -> heap_array[airports -> table[airport_table_search_airport(airports, visiting -> airport_code)] -> heap_position] != NULL)
                    {
                        if (strcmp(s -> heap_array[airports -> table[airport_table_search_airport(airports, visiting -> airport_code)] -> heap_position] -> airport_code, visiting -> airport_code) != 0)
                        {
                            priority_queue -> heap_array[i] = NULL;
                        }

                        else{
                            free(visiting);
                        }
                    }

                    else{
                        free(visiting);
                    }
                }
            }*/
            return visiting;
        }

        else{
            heap_insert(s, visiting, airports);
            heap_heapify(priority_queue, airports, 0);
        }

    }

    heap_destroy(priority_queue, airports);

    return NULL;
}

void output_path(struct airport_table *airports, struct heap *shortest_paths, struct vertice *last_airport, char d_airport[MAXAIRPORTCHAR], char a_airport[MAXAIRPORTCHAR], int departure_hour)
{
    int curr_time = 0;
    char curr_airport[MAXAIRPORTCHAR];
    memset(curr_airport, '\0', MAXAIRPORTCHAR);
    struct flight *flight_to = 0;
    struct flight_link_list *trip = flight_link_list_new();
    struct vertice *curr = last_airport;

    while (strcmp(curr -> predecessor, "\0\0\0\0\0") != 0)
    {
        flight_link_list_insert(trip, flight_new(curr -> flight_from -> departure_time, curr -> flight_from -> duration, curr -> flight_from -> arrival_airport));

        curr = shortest_paths -> heap_array[airports -> table[airport_table_search_airport(airports, curr -> predecessor)] -> heap_position];
    }

    strcpy(curr_airport, d_airport);

    printf("De   Para Parte Chega\n");
    printf("==== ==== ===== =====\n");

    while(trip -> head != NULL)
    {
        flight_to = trip -> head;

        printf("%-4s ", curr_airport);

        strcpy(curr_airport, flight_to -> arrival_airport);

        printf("%-4s ", curr_airport);

        curr_time = flight_to -> departure_time;

        printf("%02d:%02d ", curr_time/60, curr_time%60);

        curr_time += flight_to -> duration;

        if (curr_time > MINUTESINADAY)
        {
            curr_time %= MINUTESINADAY;
        }

        printf("%02d:%02d\n", curr_time/60, curr_time%60);

        flight_link_list_remove(trip, flight_to -> departure_time, flight_to -> arrival_airport);
    }
}

void calculate_path(struct airport_table *airports, char d_airport[MAXAIRPORTCHAR], char a_airport[MAXAIRPORTCHAR], int departure_hour, struct heap *shortest_paths){
    struct vertice *last_airport = find_shortest_paths(airports, d_airport, a_airport, departure_hour, shortest_paths);

    if (last_airport != NULL)
    {
        if (strcmp(last_airport -> airport_code, a_airport) != 0)
        {
            printf("+ sem voos de %s para %s", d_airport, a_airport);

            while (shortest_paths -> size > 0)
            {
                last_airport = heap_extract_min(shortest_paths, airports);

                free(last_airport);
            }

            return;
        }
    }

    else{
        printf("+ sem voos de %s para %s", d_airport, a_airport);

        while (shortest_paths -> size > 0)
        {
            last_airport = heap_extract_min(shortest_paths, airports);

            free(last_airport);
        }
        return;
    }

    output_path(airports, shortest_paths, last_airport, d_airport, a_airport, departure_hour);

    printf("Tempo de viagem: %d minutos", last_airport -> duration);

    while (shortest_paths -> size > 0)
    {
        last_airport = heap_extract_min(shortest_paths, airports);

        free(last_airport);
    }
}

int main() {
    struct airport_table *airports = airport_table_new();
    struct heap *shortest_paths = heap_new();
    FILE *airports_database = open_airports();

    read_file(airports_database, airports);

    char command[COMMANDMAXCHAR];
    memset(command, '\0', COMMANDMAXCHAR);

    scanf("%c", &command[0]);

    while (command[0] != 'X')
    {

        scanf("%c", &command[1]);

        if (strcmp("AI", command) == 0)
        {
            char aux[MAXAIRPORTCHAR];

            scanf("%s", aux);

            if (airport_table_search_airport(airports, aux) != -1)
            {
                printf("+ aeroporto %s existe", aux);
            }

            else{
                airport_table_insert_new_airport(airports, airport_new(aux));

                printf("+ novo aeroporto %s", aux);
            }
        }

        if (strcmp("FI", command) == 0)
        {
            int departure_hour, minute, duration;
            char d_airport[MAXAIRPORTCHAR], a_airport[MAXAIRPORTCHAR];

            scanf("%s", d_airport);
            scanf("%s", a_airport);
            scanf("%d:%d", &departure_hour, &minute);
            scanf("%d", &duration);
            departure_hour = (departure_hour * 60) + minute;

            if (airport_table_search_airport(airports, d_airport) == -1) {
                printf("+ aeroporto %s desconhecido", d_airport);
            }

            else if (airport_table_search_airport(airports, a_airport) == -1) {
                printf("+ aeroporto %s desconhecido", a_airport);
            }

            else if (airports->table[airport_table_search_airport(airports, d_airport)]->flights != NULL) {
                if (airports->table[airport_table_search_airport(airports, d_airport)]->flights->head != NULL) {
                    if (airport_table_search_flight(airports, departure_hour, a_airport, airport_table_search_airport(airports, d_airport)) != NULL) {
                        printf("+ voo %s %s %02d:%02d existe", d_airport, a_airport, departure_hour / 60,
                               departure_hour % 60);
                    }

                    else{
                        airport_table_insert_new_flight(airports, flight_new(departure_hour, duration, a_airport),
                                                        airport_table_search_airport(airports, d_airport));

                        printf("+ novo voo %s %s %02d:%02d", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
                    }
                }
            }

            else {
                airport_table_insert_new_flight(airports, flight_new(departure_hour, duration, a_airport),
                                                airport_table_search_airport(airports, d_airport));

                printf("+ novo voo %s %s %02d:%02d", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
            }
        }

        if (strcmp("FD", command) == 0)
        {
            int departure_hour, minute;
            char d_airport[MAXAIRPORTCHAR], a_airport[MAXAIRPORTCHAR];

            scanf("%s", d_airport);
            scanf("%s", a_airport);
            scanf("%d:%d", &departure_hour, &minute);
            departure_hour = (departure_hour * 60) + minute;

            if (airport_table_search_airport(airports, d_airport) == -1 || airport_table_search_airport(airports, a_airport) == -1) {
                printf("+ voo %s %s %02d:%02d inexistente", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
            }

            else if (airports->table[airport_table_search_airport(airports, d_airport)]->flights == NULL)
            {
                printf("+ voo %s %s %02d:%02d inexistente", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
            }

            else if (airports->table[airport_table_search_airport(airports, d_airport)]->flights->head == NULL)
            {
                printf("+ voo %s %s %02d:%02d inexistente", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
            }

            else if (airport_table_search_flight(airports, departure_hour, a_airport, airport_table_search_airport(airports, d_airport)) == NULL)
            {
                printf("+ voo %s %s %02d:%02d inexistente", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
            }

            else {
                if (!airport_table_remove_flight(airports, departure_hour, a_airport, airport_table_search_airport(airports, d_airport)))
                {
                    printf("+ voo %s %s %02d:%02d inexistente", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
                }
                else{
                    airports->table[airport_table_search_airport(airports, d_airport)]->flights->change_in_disk = 1;
                    printf("+ voo %s %s %02d:%02d removido", d_airport, a_airport, departure_hour / 60, departure_hour % 60);
                }
            }
        }

        if (strcmp("TR", command) == 0)
        {
            int departure_hour, minute;
            char d_airport[MAXAIRPORTCHAR], a_airport[MAXAIRPORTCHAR];

            scanf("%s", d_airport);
            scanf("%s", a_airport);
            scanf("%d:%d", &departure_hour, &minute);
            departure_hour = (departure_hour * 60) + minute;

            if (airport_table_search_airport(airports, d_airport) == -1)
            {
                printf("+ aeroporto %s desconhecido", d_airport);
            }

            else if (airport_table_search_airport(airports, a_airport) == -1)
            {
                printf("+ aeroporto %s desconhecido", a_airport);
            }

            else if(airports -> table[airport_table_search_airport(airports, d_airport)] -> flights == NULL)
            {
                printf("+ sem voos de %s para %s", d_airport, a_airport);
            }

            else{
                if (airports -> table[airport_table_search_airport(airports, d_airport)] -> flights -> head == NULL)
                {
                    printf("+ sem voos de %s para %s", d_airport, a_airport);
                }

                else{
                    calculate_path(airports, d_airport, a_airport, departure_hour, shortest_paths);
                    airport_table_clear_heap(airports);
                }

            }

        }

        printf("\n");
        getchar();
        scanf("%c", &command[0]);
    }

    fclose(airports_database);

    airports_database = fopen(AIRPORTSDATABASE, "w+");

    write_file(airports_database, airports);

    heap_destroy(shortest_paths, airports);
    airport_table_destroy(airports);
    return 0;
}