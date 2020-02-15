#include <stdio.h>
#define INITIAL 2

int factorial(int fact)
{
	if (fact == 0)
	{
		return 1;
	}

	else
	{
		return fact * factorial(fact - 1);
	}
}

int get_next_prime(int factor)
{

	if(((factorial(factor) + 1) % (factor + 1)) == 0)
	{
		return factor + 1;
	}

	return get_next_prime(factor + 1);
}

int decompose_primes(int number)
{
	if (number == 1)
	{
		return 1;
	}

	int count = 0, factor = INITIAL;

	while(number > 0)
	{
		if (number % factor == 0)
		{
			number /= factor;
			count++;
		}

		if (number == factor)
		{
			number = 0;
			count++;
		}

		else
		{
			factor = get_next_prime(factor);
		}
	}

	return count;
}

int main()
{
	printf("%d\n", decompose_primes(12));
	/*int amount, current, factors;

	scanf("%d", &amount);

	for (int i = 0; i < amount; ++i)
	{
		scanf("%d", &current);
		factors = decompose_primes(current);
		printf("%d: %d\n", current, factors);
	}*/

	return 0;
}