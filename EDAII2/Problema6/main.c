#include <stdio.h>
#include "trie.h"

int main(void)
{
	char command = '\0', word[MAX_WORD_SIZE + 1];
	struct trie *dict = trie_new();

	for (int i = 0; i < MAX_WORD_SIZE; ++i)
	{
		word[i] = '\0';
	}

	while (scanf(" %c", &command) != EOF)
	{
		switch (command)
		{
			case 'i':
				scanf("%s", word);
				trie_insert(dict, word);
				
				break;

			case 'r':
				scanf("%s", word);
				trie_delete(dict, word);

				break;

			case 'e':
				scanf("%s", word);
				
				if (trie_find(dict, word)) { printf("\"%s\" conhecida\n", word);}

				else{printf("\"%s\" desconhecida\n", word);}

				break;

			case 'q':
				printf("palavras conhecidas: %d\n", trie_count(dict));
				
				break;

			case 'c':
				scanf("%s", word);
				printf("palavras com prefixo \"%s\":\n", word);

				trie_print_completions(dict, word);
				break;

			default:
				break;
		}
	}

	return 0;
}