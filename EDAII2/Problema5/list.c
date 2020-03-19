#include "list.h"

struct node
{
    int second_element;
    struct node *next;
};

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

struct node *get_head_list(struct list *this_list)
{
	return this_list -> head;
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
    
	struct node *current = this_list -> head; 

    if (this_list -> size == EMPTY_LIST)
	{
		this_list -> head = malloc(sizeof(struct node));
		this_list -> head -> second_element = second_element;
		this_list -> head -> next = NULL;
		this_list -> size++;

		return;
	}

	struct node *to_insert = malloc(sizeof(struct node));
	this_list -> head = to_insert;
	to_insert -> second_element = second_element;
	to_insert -> next = current;
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
        free(current);
        this_list -> size--;
        return;
    }
    
    struct node *temporary = current -> next;

    if (current -> second_element == second_element)
    {
        free(current);
        this_list -> size--;
        this_list -> head = temporary;

		return;
    }

    temporary = temporary -> next;

    while(current -> next -> second_element != second_element)
    {
        current = current -> next;
        temporary = temporary -> next;
    }

    free(current -> next);
    this_list -> size--;
    current -> next = temporary;

    return;
}

void print_list(struct node *current)
{
	if (current -> next != NULL)
	{
		print_list(current -> next);
	}

	printf(" %d", current -> second_element);

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
        free(current);
        free(this_list);
        return;
    }

    struct node *temporary = current -> next;

    while (temporary != NULL)
    {
        free(current);
        current = temporary;
        temporary = temporary -> next;
    }

	free(current);
    free(this_list);
    return;
}