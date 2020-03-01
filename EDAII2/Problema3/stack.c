#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack
{
	int array[SIZE];
	short top;
};

struct stack *new_stack()
{
	struct stack *new = malloc(sizeof(struct stack));

	if (new == NULL)
	{
		free(new);
		return NULL;
	}

	new -> top = -1;

	return new;
}

int peek_stack(struct stack *stack)
{
	return stack -> array[stack -> top];
}

_Bool push_stack(struct stack *stack, int value)
{
	if (stack -> top == SIZE)
	{
		return 0;
	}

	stack -> top++;
	stack -> array[stack -> top] = value;

	return 1;
}

int pop_stack(struct stack *stack)
{
	stack -> top--;

	return stack -> array[stack -> top + 1];
}

_Bool set_empty_stack(struct stack *stack)
{
	stack -> top = -1;

	return 1;
}

_Bool free_stack(struct stack *stack)
{
	free(stack);

	if (stack == NULL)
	{
		return 1;
	}

	return 0;
}