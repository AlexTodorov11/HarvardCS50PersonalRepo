// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 10000; // Choosing a large number of buckets for better distribution

// Hash table
node *table[N];

// Number of words in the dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain the correct index
    unsigned int index = hash(word);

    // Access the linked list at that index
    node *cursor = table[index];

    // Traverse the linked list to look for the word (case-insensitive)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    // If the word is not found, return false
    return false;
}

// Hashes word to a number using a better hash function
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); // hash * 33 + c
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer to store words
    char word[LENGTH + 1];

    // Read words from the file one at a time
    while (fscanf(file, "%45s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, word);

        // Hash the word to obtain a hash index
        unsigned int index = hash(word);

        // Insert the node into the hash table at that index
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the word count
        word_count++;
    }

    // Close the dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Free the linked list at each bucket
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
