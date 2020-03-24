#include "heap.h"

struct vertice *vertice_new(int duration, char airport_code[MAXAIRPORTCHAR]){
    struct vertice *new = malloc(sizeof(struct vertice));

    new -> duration = duration;
    memset(new -> airport_code, '\0', MAXAIRPORTCHAR);
    strcpy(new -> airport_code, airport_code);
    new -> flight_from = NULL;
    memset(new -> predecessor, '\0', MAXAIRPORTCHAR);

    return new;
}

struct heap *heap_new(){
    struct heap *new = malloc(sizeof(struct heap));

    for (int i = 0; i < MAXSIZE; ++i) {
        new -> heap_array [i] = NULL;
    }

    new -> size = 0;
    return new;
}

void change(struct vertice *x, struct vertice *y)
{
    struct vertice temp = *x;
    *x = *y;
    *y = temp;
}

int parent(int i)
{
    return (i-1)/2;
}

int left_child(int i)
{
    return 2 * i + 1;
}

int right_child(int i)
{
    return 2 * i + 2;
}

int heap_insert(struct heap *priority_queue, struct vertice *to_insert, struct airport_table *airports)
{
    if (priority_queue -> size == MAXSIZE)
    {
        return -1;
    }

    priority_queue -> size++;
    int i = priority_queue -> size - 1;
    priority_queue -> heap_array[i] = to_insert;
    airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[i] -> airport_code)] -> heap_position = i;

    while (i != 0 && priority_queue -> heap_array[parent(i)] -> duration > priority_queue -> heap_array[i] -> duration)
    {
        change(priority_queue -> heap_array[i], priority_queue -> heap_array[parent(i)]);
        airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[i] -> airport_code)] -> heap_position = i;
        airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[parent(i)] -> airport_code)] -> heap_position = parent(i);

        i = parent(i);
    }

    return i;
}

void heap_decrease_key(struct heap *priority_queue, struct airport_table *airports, int i){
    priority_queue -> heap_array[i] -> duration = INFINITY;

    while(i != 0 && priority_queue -> heap_array[parent(i)] -> duration < priority_queue -> heap_array[i] -> duration)
    {
        change(priority_queue -> heap_array[i], priority_queue -> heap_array[parent(i)]);
        airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[i] -> airport_code)] -> heap_position = i;
        airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[parent(i)] -> airport_code)] -> heap_position = parent(i);

        i = parent(i);
    }
}

void heap_heapify(struct heap *priority_queue, struct airport_table *airports, int i)
{
    int left = left_child(i);
    int right = right_child(i);
    int min = i;

    if (priority_queue -> heap_array[left] != NULL)
    {
        if (left <= priority_queue -> size && priority_queue -> heap_array[left] -> duration < priority_queue -> heap_array[i] -> duration)
        {
            min = left;
        }
    }

    if (priority_queue -> heap_array[right] != NULL)
    {
        if (right <= priority_queue -> size && priority_queue -> heap_array[right] -> duration < priority_queue -> heap_array[min] -> duration)
        {
            min = right;
        }
    }

    if (min != i)
    {
        change(priority_queue -> heap_array[i], priority_queue -> heap_array[min]);
        airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[i] -> airport_code)] -> heap_position = i;
        airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[min] -> airport_code)] -> heap_position = min;

        heap_heapify(priority_queue, airports, min);
    }
}

struct vertice *heap_extract_min(struct heap *priority_queue, struct airport_table *airports)
{
    if (priority_queue -> size <= 0)
    {
        return NULL;
    }

    if (priority_queue -> size == 1)
    {
        priority_queue -> size--;
        return priority_queue -> heap_array[0];
    }

    struct vertice *min = priority_queue -> heap_array[0];
    priority_queue -> heap_array[0] = priority_queue -> heap_array[priority_queue -> size - 1];
    airports -> table[airport_table_search_airport(airports, priority_queue -> heap_array[0] -> airport_code)] -> heap_position = 0;
    priority_queue -> heap_array[priority_queue -> size - 1] = NULL;
    priority_queue -> size--;
    heap_heapify(priority_queue, airports, 0);

    return min;
}

void heap_delete_key(struct heap *priority_queue, struct airport_table *airports, int i)
{
    heap_decrease_key(priority_queue, airports, i);
    heap_extract_min(priority_queue, airports);
}

void heap_destroy(struct heap *priority_queue, struct airport_table *airports)
{
    struct vertice *visiting = priority_queue -> heap_array[0];

    for (int i = 0; i < MAXSIZE; ++i) {
        if (visiting == NULL)
        {
            break;
        }

        if (i == 0)
        {
            priority_queue -> heap_array[i] = NULL;
        }

        else{
            free(visiting);
            priority_queue -> heap_array[i] = NULL;
        }

        visiting = priority_queue -> heap_array[i];
    }

    free(priority_queue);
}