#include <stdio.h>
#include "stack.h"
#define TURN_TO_INT 48

void reverse_polish_notation_calculator(char to_calculate[], struct stack *rpn)
{
	short num1, num2;
	_Bool flag = 0;

	for (int i = 0; to_calculate[i] != '\0'; ++i)
	{
		if (to_calculate[i] >= '0' && to_calculate[i] <= '9')
		{
			push_stack(rpn, ((int) to_calculate[i]) - TURN_TO_INT);
		}

		else
		{
			switch (to_calculate[i])
			{
				case '+':
					num2 = pop_stack(rpn);
					num1 = pop_stack(rpn);

					push_stack(rpn, num1 + num2);
					break;

				case '-':
					num2 = pop_stack(rpn);
					num1 = pop_stack(rpn);

					push_stack(rpn, num1 - num2);
					break;

				case '*':
					num2 = pop_stack(rpn);
					num1 = pop_stack(rpn);

					push_stack(rpn, num1 * num2);
					break;

				case '/':
					num2 = pop_stack(rpn);
					num1 = pop_stack(rpn);

					if (num2 == 0)
					{
						printf("divisao por 0\n");
						flag = 1;
						break;
					}

					push_stack(rpn, num1 / num2);
					break;

				case '~':
					num1 = -(pop_stack(rpn));

					push_stack(rpn, num1);
					break;
			}
		}

		if (flag == 1)
		{
			set_empty_stack(rpn);
			break;
		}
	}

	return;
}

int main()
{
	char to_calculate[3] = {'2', '1', '+'};
	struct stack *rpn = new_stack();

	reverse_polish_notation_calculator(to_calculate, rpn);

	/*while (scanf("%s", &to_calculate) != EOF)
	{
		reverse_polish_notation_calculator(to_calculate, rpn);

		if (rpn -> top != -1)
		{
			printf("%d\n", rpn -> array[rpn -> top]);
			rpn -> top = -1;
		}

	}*/

	free_stack(rpn);

	return 0;
}