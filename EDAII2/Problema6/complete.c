#include <stdio.h>

#include "trie.h"

char *words[] = {
  "acabais",
  "acocora",
  "amuareis",
  "ar",
  "aramada",
  "arpoavam",
  "azoto",
  "barceiro",
  "barco",
  "cabulais",
  "coragem",
  "corasse",
  "cuja",
  "embarace",
  "ensaquem",
  "enxuguem",
  "festeiro",
  "laringes",
  "mar",
  "propugno",
  "remem",
  "salteada",
  "repudiei",
  "reactive",
  "festa",
  "leque",
  "festarola",
  "achar",
  "enteados",
  "marujar",
  "vinte",
  NULL
};

/*
   Fazer um programa que:

   1. insere todas as palavras em words[] numa trie

   2. confirma que trie_find() as encontra todas

   3. diz quantas palavras existem na trie

   4. mostra as palavras na trie com prefixos "a" "ac" "mar" "por" "vinte"

   5. remove 5 palavras da trie

   6. mostra todas as palavras na trie, antes e depois de remover palavras
*/

int main(void)
{
  struct trie *dict = trie_new();
  int index = 0;

  while (words[index] != NULL)
  {
    trie_insert(dict, words[index]);
    index++;
  }

  index = 0;

  while(words[index] != NULL)
  {

    if (trie_find(dict, words[index]))
    {
      printf("found: %s\n", words[index]);
    }

    else
    {
      printf("not found: %s\n", words[index]);
    }

    index++;
  }

  printf("words in trie: %d\n", trie_count(dict));

  trie_print_completions(dict, "vo");

  trie_destroy(dict);
  return 0;
}
