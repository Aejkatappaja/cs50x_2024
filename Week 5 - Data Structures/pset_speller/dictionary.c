// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

unsigned int word_count;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word) {

  int hash_value = hash(word);

  node *n = table[hash_value];

  while (n != NULL) {
    if (strcasecmp(word, n->word) == 0) {
      return true;
    }
    n = n->next;
  }
  // TODO
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {

  long sum = 0;

  for (int i = 0; i < strlen(word); i++)
    sum += tolower(word[i]);
  // TODO: Improve this hash function

  return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {

  // TODO
  FILE *source = fopen(dictionary, "r");
  if (source == NULL)
    return false;

  char word[LENGTH + 1];

  while (fscanf(source, "%s", word) != EOF) {
    node *n = malloc(sizeof(node));
    if (n == NULL)
      return false;
    strcpy(n->word, word);
    int hash_value = hash(word);
    n->next = table[hash_value];
    table[hash_value] = n;
    word_count++;
  }

  fclose(source);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {

  return word_count;
  // TODO
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) {

  for (int i = 0; i < N; i++) {
    node *n = table[i];

    while (n != NULL) {
      node *tmp = n;

      n = n->next;

      free(tmp);
    }
    if (n == NULL && i == N - 1) {
      return true;
    }
  }
  return false;
}
