#include "list.h"

struct node
{
    int second_element;
    struct node *next;
};

struct node *new_node(int second_element)
{
    struct node *new = malloc(sizeof(struct node));

    new -> second_element = second_element;
    new -> next = NULL;

    return new;
}

void destroy_node(struct node *this_node)
{
    free(this_node);

    return;
}

struct list
{
    short size;
    int first_element;
    struct node *head;
};

struct list *new_list(int first_element)
{
    struct list *new = malloc(sizeof(struct list));

    new -> size = EMPTY_LIST;
    new -> first_element = first_element;
    new -> head = NULL;

    return new;
}

short get_size_list(struct list *this_list)
{
    return this_list -> size;
}

_Bool element_in_list(struct list *this_list, int second_element)
{
    if (get_size_list(this_list) == EMPTY_LIST)
    {
        return 0;
    }
    
    struct node *current = this_list -> head;

    while (current != NULL)
    {
        if (current -> second_element == second_element)
        {
            return 1;
        }

        current = current -> next;
    }

    return 0;
}

void insert_node_in_list(struct list *this_list, int second_element)
{
    if (this_list -> size == MAX_LIST_SIZE || element_in_list(this_list, second_element))
    {
        return;
    }
    
    struct node *to_insert = new_node(second_element);
    
    struct node *current = this_list -> head;

    if (current == NULL)
    {
        this_list -> head = to_insert;
        this_list -> size++;
        
        return;
    }

    if (current -> next == NULL)
    {
        current -> next = to_insert;
        this_list -> size++;

        return;
    }
    
    while (current -> next != NULL)
    {
        current = current -> next;
    }
        
    current -> next = to_insert;
    this_list -> size++;
    
    return;
}

void destroy_node_in_list(struct list *this_list, int second_element)
{
    if (this_list -> size == EMPTY_LIST || !element_in_list(this_list, second_element))
    {
        return;
    }
    
    struct node *current = this_list -> head;

    if (current -> next == NULL)
    {
        destroy_node(current);
        this_list -> size--;
        return;
    }
    
    struct node *temporary = current -> next;

    if (current -> second_element == second_element)
    {
        destroy_node(current);
        this_list -> size--;
        this_list -> head = temporary;
    }

    temporary = temporary -> next;

    while(current -> next -> second_element != second_element)
    {
        current = current -> next;
        temporary = temporary -> next;
    }

    destroy_node(current -> next);
    this_list -> size--;
    current -> next = temporary;

    return;
}

void print_list(struct list *this_list)
{
    struct node *current = this_list -> head;

    while (current -> next != NULL)
    {
        printf("%d ", current -> second_element);
        current = current -> next;
    }

    printf("%d", current -> second_element);
    
    return;
}

void destroy_list(struct list *this_list)
{
    if (this_list -> size == EMPTY_LIST)
    {
        free(this_list);
        return;
    }

    struct node *current = this_list -> head;

    if (current -> next == NULL)
    {
        destroy_node(current);
        free(this_list);
        return;
    }

    struct node *temporary = current -> next;

    while (current != NULL)
    {
        destroy_node(current);
        current = temporary;
        temporary = temporary -> next;
    }
    
    free(this_list);
    return;
}

int main()
{
    struct list *test = new_list(1);

    insert_node_in_list(test, 0);

    insert_node_in_list(test, 1);

    destroy_list(test);
    
    return 0;
}