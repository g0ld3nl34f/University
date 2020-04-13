/* trie implementation, with arrays */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "trie.h"

#define ALPHABET_MIN 'a'
#define ALPHABET_MAX 'z'
#define ALPHABET_SIZE (ALPHABET_MAX - ALPHABET_MIN + 1)

#define POS(c)  ((c) - ALPHABET_MIN)	// character position in alphabet
#define CHAR(n) ((n) + ALPHABET_MIN)	// n-th alphabet character


/* trie node */
struct node {
  struct node *child[ALPHABET_SIZE];	// children
  bool        word;			// end-of-word mark
};

/* trie */
struct trie {
  struct node *root;
};


/*
  Allocates and returns a new trie node.
*/
static struct node *node_new(void)
{
  struct node *node = malloc(sizeof(*node));

  if (node != NULL)
    {
      node->word = false;

      for (int i = 0; i < ALPHABET_SIZE; ++i)
	      node->child[i] = NULL;
    }

  return node;
}


/* Frees a trie NODE. */
static void node_free(struct node *node)
{
  free(node);
}


/* Destroys the sub-trie with root NODE. */
static void node_destroy(struct node *node)
{
  if (node == NULL)
    return;

  for (int i = 0; i < ALPHABET_SIZE; ++i)
    node_destroy(node->child[i]);

  node_free(node);
}


/*
  Creates and returns a new, empty trie.
*/
struct trie *trie_new(void)
{
  struct trie *trie = malloc(sizeof(struct trie));

  if (trie != NULL)
    trie->root = NULL;

  return trie;
}


/* Destroys trie T, freeing the memory it occupies. */
void trie_destroy(struct trie *t)
{
  node_destroy(t->root);

  free(t);
}


/* Checks whether trie T is empty. */
bool trie_empty(struct trie *t)
{
  return t->root == NULL;
}


/*
  Inserts word P into trie T.

  Returns true if the word was successfully inserted (or was already
  in the trie), false otherwise.
*/
bool trie_insert(struct trie *t, char p[])
{
  struct node *n;
  int i = 0;

  if (t->root == NULL)
    t->root = node_new();	// new, empty root node

  if (t->root == NULL)
    return false;

  n = t->root;

  // follow the word down the trie as long as possible,
  // taking care not to go to a nonexisting node
  while (p[i] != '\0' && n->child[POS(p[i])] != NULL)
    {
      n = n->child[POS(p[i])];
      i++;
    }

  // insert the new suffix into the trie
  while (p[i] != '\0')
    {
      n->child[POS(p[i])] = node_new();

      if (n->child[POS(p[i])] == NULL)
	return false;

      n = n->child[POS(p[i])];

      i++;
    }

  n->word = true;

  return true;
}


/*
   Searches for word P in trie T.

   Returns true if it finds it, false otherwise.
*/
bool trie_find(struct trie *t, char p[])
{
  struct node *temp = t -> root;
  int index = 0;

  while (temp != NULL && p[index] != '\0')
  {
    temp = temp -> child[POS(p[index])];
    index++;
  }

  if (temp != NULL && temp -> word)
   {
     return true;
   } 

   return false;
}


/* Counts and returns the number of words in trie T. */
int trie_count_words(struct node *n)
{
  int n_words = 0;

  if (n -> word)
  {
    n_words++;
  }

  for (int i = 0; i < ALPHABET_SIZE; ++i)
  {
    if (n -> child[i] != NULL)
    {
      n_words += trie_count_words(n -> child[i]);
    }
  }

  return n_words;
}


int trie_count(struct trie *t)
{
  int n_words = 0;

  for (int i = 0; i < ALPHABET_SIZE; ++i)
  {
    if (t -> root -> child[i] != NULL)
    {
      n_words += trie_count_words(t -> root -> child[i]);
    }
  }

  return n_words;
}


/* Prints all words in trie T with prefix P. */

void trie_print_c_remaining(struct node *n, int index, char word[], char p[])
{
  if (n -> word)
  {
    printf("%s", p);

    for (int i = 0; i < index; ++i)
    {
      printf("%c", word[i]);
    }
    printf("\n");
  }

  for (int i = 0; i < ALPHABET_SIZE; ++i)
  {
    if (n -> child[i] != NULL)
    {
      word[index] = CHAR(i);

      trie_print_c_remaining(n -> child[i], index + 1, word, p);
    }
  }
}

void trie_print_completions(struct trie *t, char p[])
{
  struct node *n = t -> root;
  int index = 0;

  while (n != NULL && p[index] != '\0')
  {
    n = n -> child[POS(p[index])];
    index++;
  }

  if (n == NULL)
  {
    return;
  }

  char remaining_word[(MAX_WORD_SIZE + 1) - index];

  trie_print_c_remaining(n, 0, remaining_word, p);
}



/* Removes word P from trie T. */
void trie_delete(struct trie *t, char p[])
{
  struct node *temp = t -> root;
  int index = 0;

  while (temp != NULL && p[index] != '\0')
  {
    temp = temp -> child[POS(p[index])];
    index++;
  }

  if (temp != NULL && temp -> word)
   {
     temp -> word = false;
   }
}


/* Prints the full contents of trie T. */

void trie_print_remaining(struct node *n, int index, char word[])
{
  if (n -> word)
  {
    for (int i = 0; i < index; ++i)
    {
      printf("%c", word[i]);
    }
    printf("\n");
  }

  for (int i = 0; i < ALPHABET_SIZE; ++i)
  {
    if (n -> child[i] != NULL)
    {
      word[index] = CHAR(i);

      trie_print_remaining(n -> child[i], index + 1, word);
    }
  }
}

void trie_print(struct trie *t)
{
  char word[MAX_WORD_SIZE + 1];

  trie_print_remaining(t -> root, 0, word);
}

