#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

struct stack;

struct stack *new_stack();

int get_top_stack(struct stack *stack);
int peek_stack(struct stack *stack);
_Bool push_stack(struct stack *stack, int value);
int pop_stack(struct stack *stack);
_Bool set_empty_stack(struct stack *stack);

_Bool free_stack(struct stack *stack);

#endif //STACK