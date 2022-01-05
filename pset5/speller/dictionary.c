// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

#define TOLOWER(c) 'A' <= c && c <= 'Z' ? c + ('a' - 'A') : c

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 50;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int i, j, wordLen;
    node *n;

    for(i = 0; i < N; i++)
    {
        for(n = table[i]; n != NULL; n = n->next)
        {
            if(strcasecmp(n->word, word) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    unsigned short c = TOLOWER(*word);

    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = TOLOWER(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH+1];
    unsigned int index;
    node *n;

    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }

    while(fscanf(file, "%s", word) != EOF)
    {
        n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        index = hash(n->word);
        n->next = table[index];
        table[index] = n;
    }

    if(fclose(file) != 0)
    {
        return false;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int i, wordsCount = 0;
    node *n;

    for(i = 0; i < N; i++)
    {
        for(n = table[i]; n != NULL; n = n->next)
        {
            wordsCount++;
        }
    }

    return wordsCount;
}

// Unloads a linked list from the memory recursively
void freeList(node *list)
{
    if(list == NULL)
    {
        return;
    }

    freeList(list->next);
    free(list);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    unsigned int i;
    node *n, last;

    for(i = 0; i < N; i++)
    {
        freeList(table[i]);
    }

    return true;
}