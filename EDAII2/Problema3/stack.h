#ifndef STACK_H
#define STACK_H
#define SIZE 1000

#include <stdio.h>
#include <stdlib.h>

struct stack;

struct stack *new_stack();

int peek_stack(struct stack *stack);
_Bool push_stack(struct stack *stack, int value);
int pop_stack(struct stack *stack);
_Bool set_empty_stack(struct stack *stack);

_Bool free_stack(struct stack *stack);

#endif