// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

/*  Notes
    Could perform modulo math many fewer times, per https://stackoverflow.com/a/71316468/14093090
    strcasecmp is very slow and should be avoided
    malloc is slow when run many times and should be avoided
    Hash is a prime number larger than the number of words
        a prime is used to avoid collisions
        described here: https://medium.com/swlh/why-should-the-length-of-your-hash-table-be-a-prime-number-760ec65a75d1
    a large table number uses more RAM, but is typically faster
    reminder that LENGTH is 45. Definied in dictionary.h
    hash prototype is called by including dictionary.h
*/


// Represents a node in a hash table
// Uncomment third part to slightly modify vanilla file to include a hash value. Can speed up some implementations.
typedef struct node
{
    char word[LENGTH + 1 + 1];
    struct node *next;
    // unsigned int hash;
} node;

// Constant numbers to use in functions. See notes at top of file
const unsigned int N = 187751;
int counter = 0;

// Hash table full of 'buckets'
node *table[N];

// Hashes word to a number and copies lowercase chars to output buffer
unsigned int hash2(char *dest, const char *word)
{
    unsigned int hsh = 0;

    // Some fancy syntax that uses pointer arithmetic
    // chr ~ "character" as ascii int
    for (int chr = *word++;  chr != 0;  chr = *word++)
    {
        chr = tolower((unsigned char) chr);
        hsh = (31 * hsh) + chr;
        *dest++ = chr;
    }

    *dest = 0;

    return hash;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char tmp[LENGTH];
    unsigned int hash_num = hash2(tmp, word);
    unsigned int idx = hash_num % N;

    // iterator through buckets
    for (node *cursor = table[idx]; cursor != NULL; cursor = cursor->next)
    {
        // could optimize
        if (strcmp(cursor->word, tmp) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// Must return integer between 0 and N-1
unsigned int hash(const char *word)
{
    // Allocate space for the hash variable
    int hash = 0;

    for (int chr = *word++;  chr != 0;  chr = *word++)
    {
        hash = (31 * hash + chr) % N;
    }

    return hash;
}

/* Loads dictionary into memory, returning true if successful, else false
     must load a dictionary file
     must read strings from the file one line at a time
     must create a node for each string/word
     hash the word to get a hash value
     insert node into hash table at that location */
bool load(const char *dictionary)
{
    // Opens the input dictionary file
    FILE *d = fopen(dictionary, "r");

    if (d == NULL)
    {
        return false;
    }

    // Temporarily allocates memory to a string plus the nul character
    char d_word[LENGTH + 1];

    // While loop until end of file
    while(fscanf(d, "%s", d_word) != EOF)
    {
        // Allocates memory for a new node
        node *foo = malloc(sizeof(node));

        // Checks that the word is not fully NULL. Could happen if out of memory.
        if (foo == NULL)
        {
            return false;
        }

        // Populates the node
        strcpy(foo->word, d_word);
        foo->next = NULL;
        // foo->hash = 0;

        // Get a hash value
        int idx = hash(d_word);

        if (table[idx] == NULL)
        {
            // Add new node "bucket" if needed
            table[idx] = foo;
        }

        else
        {
            // Insert command that does not orphan data in memory
            foo->next = table[idx];
            table[idx] = foo;
        }

        // Increment the counter
        counter++;
    }
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return a counter from the load function
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
// use recursive unloading function. must make a temporary function to do this
bool unload(void)
{
    // return true if memory successfully freed
    for (int i = 0; i < N; i++)
    {
        node *foo = table[i];

        while (foo != NULL)
        {
            node *tmp = foo;
            foo = foo->next;
            free(tmp);
        }

        if (foo == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}