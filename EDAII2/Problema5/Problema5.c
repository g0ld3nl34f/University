#include <stdio.h>
#include "list.h"

#define MAX_INT_VALUE 1000000

int main()
{
    char command = '\0';
    int first_element, second_element;
    struct list *pairs[MAX_INT_VALUE];

    for (size_t i = 0; i < MAX_INT_VALUE; i++)
    {
        pairs[i] = new_list(i);
    }

    while (scanf(" %c", &command) != EOF)
    {
        switch (command)
        {
        case 'p':
            scanf(" %d %d", &first_element, &second_element);
            insert_node_in_list(pairs[first_element], second_element);
            break;
        
        case 'x':
            scanf(" %d %d", &first_element, &second_element);
            destroy_node_in_list(pairs[first_element], second_element);
            break;
        
        case 'q':
            scanf(" %d", &first_element);
            second_element = get_size_list(pairs[first_element]);
            printf("%d %d", first_element, second_element);
            
            if (second_element == 0)
            {
                printf("\n");
                break;
            }

            print_list(get_head_list(pairs[first_element]));
            printf("\n");
            break;
        
        default:
            break;
        }
    }
    
    for (int j = 0; j < MAX_INT_VALUE; j++)
    {
        destroy_list(pairs[j]);
    }
    
    return 0;
}