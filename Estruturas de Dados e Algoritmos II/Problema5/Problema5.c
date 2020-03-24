#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 600011

struct list_node{
    int a, b, c, interface;
    struct list_node *next;
};

struct list{
    struct list_node *head;
};

struct list_node *list_node_new(int a, int b, int c, int interface){
    struct list_node *new = malloc(sizeof(struct list_node));
    new -> a = a;
    new -> b = b;
    new -> c = c;
    new -> interface = interface;
    new -> next = NULL;

    return new;
}

struct list *list_new(){
    struct list *list = malloc(sizeof(struct list));
    return list;
}


_Bool list_empty(struct list *list){
    struct list_node *current = list->head;

    if (current->next == NULL){
        free(current);
        return 1;
    }
    else{
        free(current);
        return 0;
    }
}

void list_insert(struct list *list, int a, int b, int c, int interface){
    struct list_node *temp = list_node_new(a, b, c, interface);

    if (list -> head == NULL)
    {
        list -> head = temp;
        return;
    }

    temp -> next = list -> head;
    list -> head = temp;

}

struct list_node *list_search(struct list *list, int a, int b, int c){
    struct list_node *temp = list->head;

    while (temp -> next != NULL)
    {
        if (temp -> a == a && temp -> b == b && temp -> c == c)
        {
            return temp;
        }

        temp = temp -> next;
    }

    return temp;
}

void list_destroy(struct list *list){
    struct list_node *current = list -> head;
    struct list_node *temp = list -> head;

    while (current->next != NULL)
    {
        temp = current -> next;
        free(current);
        current = temp;
    }

    free(current);
    free(list);
}

struct hash_table_node{
    struct list *list;
};

struct hash_table{
    struct hash_table_node *table[MAXSIZE];
};

struct hash_table_node *node_new(int a, int b, int c, int interface){
    struct hash_table_node *new = malloc(sizeof(struct hash_table_node));

    new -> list = list_new();

    new -> list -> head = list_node_new(a, b, c, interface);

    return new;

}

struct hash_table *hash_table_new(){
    struct hash_table *hash_table = malloc(sizeof(struct hash_table));

    for (int i = 0; i < MAXSIZE; ++i) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
};


long int hash(int a, int b, int c)
{
    long int key = ((a * 1000) + (b * 100) + c) % MAXSIZE;
    return key;
}

void hash_table_insert(struct hash_table *hash_table, int a, int b, int c, int interface)
{
    long int key = hash(a, b, c);

    if (hash_table -> table[key] == NULL)
    {
        hash_table -> table[key] = node_new(a, b, c, interface);
        return;
    }

    else
    {
        list_insert(hash_table -> table[key] -> list, a, b, c, interface);
        return;
    }
}

struct list_node *hash_table_search(struct hash_table *hash_table, int a, int b, int c)
{
    long int key = hash(a, b, c);

    if (hash_table -> table[key] == NULL)
    {
        return NULL;
    }

    else
    {
        return list_search(hash_table -> table[key] -> list, a, b, c);
    }
}

int hash_table_route(struct hash_table *hash_table, int a, int b, int c)
{
    struct list_node *new = hash_table_search(hash_table, a, b, c);

    if (new == NULL)
    {
        return -1;
    }

    while(new -> next != NULL)
    {
        if (new -> a == a && new -> b == b && new -> c == c)
        {
            return new -> interface;
        }

        new = new -> next;
    }

    if (new -> a == a && new -> b == b && new -> c == c)
    {
        return new -> interface;
    }


    return -1;
}

void hash_table_destroy(struct hash_table *hash_table)
{
    for (int i = 0; i < MAXSIZE; ++i) {
        if (hash_table -> table[i] != NULL)
        {
            list_destroy(hash_table -> table[i] -> list);
        }
        free(hash_table->table[i]);
    }

    free(hash_table);
}

int main()
{
    struct hash_table *hashTable = hash_table_new();
    int R = 0, a = 0, b = 0, c = 0, d = 0, interface = 0, default_route = -1;

    scanf("%d", &R);

    for (int i = 0; i < R; ++i) {
        scanf("%d.%d.%d.%d %d", &a, &b, &c, &d, &interface);
        if (a == 0 && b == 0 && c == 0)
        {
            default_route = interface;
        }
        else{
            hash_table_insert(hashTable, a, b, c, interface);
        }
    }

    for (int j = 0; j < 6; ++j) {
        scanf("%d.%d.%d.%d", &a, &b, &c, &d);
        int route = hash_table_route(hashTable, a, b, c);
        if (route == -1)
        {
            if (default_route != -1)
            {
                printf("%d\n", default_route);
            }
            else{
                printf("no route\n");
            }
        }
        else{
            printf("%d\n", route);
        }

    }

    hash_table_destroy(hashTable);
}