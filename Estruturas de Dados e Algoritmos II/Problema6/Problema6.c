#include <stdio.h>
#include <stdlib.h>

struct node{
    int element;
    struct node *next;
    struct node *prev;
};

struct dll{
    struct node *head;
    struct node *last;
};

struct node *node_new(int element){
    struct node *node = malloc(sizeof(struct node));
    node -> next = NULL;
    node -> prev = NULL;
    node -> element = element;
    return node;
}

struct dll *dll_new(){
    struct dll *dll = malloc(sizeof(struct dll));
    dll->head = NULL;
    dll->last = NULL;
    return dll;
};

_Bool dll_empty(struct dll *dll){
    if (dll->head == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

_Bool dll_insert(struct dll *dll, int element){
    struct node *node = node_new(element);
    if(node == NULL){
        return 0;
    }

    node -> next = dll -> head;
    dll -> head = node;

    if (dll_empty(dll))
    {
        dll -> last = dll -> head;
    }

    if (node -> next != NULL) {
        node->next->prev = node;
    }
    return 1;

}

int dll_find(struct dll *dll, int element){
    struct node *temp = dll->head;
    int position = 0;

    if(dll_empty(dll)){
        return -1;
    }

    while(temp->next != NULL){
        if(temp->element == element){
            return position;
        }

        temp = temp->next;
        position++;
    }

    if(temp -> element == element){
        return position;
    }

    return -1;
}

_Bool dll_remove(struct dll *dll, int element){
    struct node *current = dll->head;
    struct node *temp = current;

    if(current->element == element){
        dll -> head = dll -> head ->next;
        free(temp);
        return 1;
    }

    current = current -> next;

    while(current->next!=NULL){
        if (current->element == element){
            temp -> next = current -> next;
            temp -> next -> prev = temp;
            free(current);
            return 1;
        }
        else{
            current = current ->next;
            temp = temp ->next;
        }
    }

    if (current->element == element) {
        temp->next = current->next;
        free(current);
        return 1;
    }

    return 0;
}


void dll_destroy(struct dll *dll){
    struct node *current = dll->head;
    struct node *temp;

    if(dll_empty(dll)){
        free(dll);
        return;
    }

    while(current -> next != NULL){
        temp = current;
        current = current->next;

        free(temp);
    }
    free(current);
    free(dll);
}

int main()
{
    int S, L, sensor_from = 0, sensor_to = 0, first, last;
    char operator;
    _Bool found = 1;

    scanf("%d", &S);
    getchar();

    struct dll *sensors[S];

    for (int i = 0; i < S; ++i)
    {
        sensors[i] = NULL;
    }

    while(scanf("%c", &operator) != EOF)
    {
        switch (operator) {
            case '+':

                scanf("%d %d", &sensor_from, &sensor_to);
                getchar();

                if (sensors[sensor_from] == NULL)
                {
                    sensors[sensor_from] = dll_new();
                    dll_insert(sensors[sensor_from], sensor_to);
                }

                else {
                    dll_insert(sensors[sensor_from], sensor_to);
                }
                break;


            case '-':

                scanf("%d %d", &sensor_from, &sensor_to);
                getchar();

                dll_remove(sensors[sensor_from], sensor_to);

                break;

            case '?':

                scanf("%d", &L);
                scanf("%d", &sensor_from);
                first = sensor_from;

                for (int i = 0; i < L; ++i) {
                    scanf("%d", &sensor_to);

                    if (sensors[sensor_from] == NULL)
                    {
                        found = 0;
                    }

                    else if (dll_find(sensors[sensor_from], sensor_to) == -1)
                    {
                        found = 0;
                    }

                    sensor_from = sensor_to;
                }
                last = sensor_to;

                if (found == 1)
                {
                    printf("yes [%d..%d]\n", first, last);
                }
                else{
                    printf("no [%d..%d]\n", first, last);
                }

                found = 1;

                break;

            default:

                break;

        }
    }

    for (int l = 0; l < S; ++l)
    {
        if (sensors[l] != NULL)
        {
            dll_destroy(sensors[l]);
        }
    }

    return 0;
}