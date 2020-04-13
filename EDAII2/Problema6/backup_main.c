#include <stdio.h>
#include <string.h>
#include "trie.h"

void copy_word(char c_a_a[], char word[])
{
	int index = 2;

	while (c_a_a[index] != '\0')
	{
		word[index - 2] = c_a_a[index];
		index++;
	}

	return;
}

int main(void)
{
	char c_a_a[MAX_WORD_SIZE + 3], word[MAX_WORD_SIZE];
	struct trie *dict = trie_new();

	for (int i = 0; i < MAX_WORD_SIZE; ++i)
	{
		word[i] = '\0';
	}

	while (scanf(" %s", c_a_a) != EOF)
	{
		switch (c_a_a[0])
		{
			case 'i':
				copy_word(c_a_a, word);
				trie_insert(dict, word);
				
				break;

			case 'r':
				copy_word(c_a_a, word);
				trie_delete(dict, word);

				break;

			case 'e':
				copy_word(c_a_a, word);
				
				if (trie_find(dict, word)) { printf("\"%s\" conhecida\n", word);}

				else{printf("\"%s\" desconhecida\n", word);}

				break;

			case 'q':
				printf("palavras conhecidas: %d\n", trie_count(dict));
				
				break;

			case 'c':
				copy_word(c_a_a, word);
				printf("palavras com prefixo \"%s\":\n", word);

				trie_print_completions(dict, word);
				break;

			default:
				break;
		}

		scanf(" %s", c_a_a);
	}

	return 0;
}