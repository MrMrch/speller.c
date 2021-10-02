// Implements a dictionary's functionality
#include <stdio.h> //ADDED BY ME
#include <string.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // return false;
    // testning
    int index = hash(word);
    node *cursor = table[index];

    while(cursor->next != NULL)
    {
        if(cursor->word == word)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
        return false;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int n = (word[0]*31)*(word[1]*37)*(word[2]*41);

    while(n > N-1)
    {
        n = n%N;
    }
    return n;
}

//initiates size_load variable
int size_counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];
    
    if(file == NULL)
    {
        return false;
    }
    
    //while(!feof(file))
    while(fscanf(file, "%s", word) != EOF)
    {
        //fscanf(file, "%s", word);
        
        node *n = malloc(sizeof(node));
        
        if(n == NULL)
        {
            return false;
        }
        
        else
        {
            strcpy(n->word, word);
            n->next = NULL;
            int index = hash(n->word);
            
            size_counter +=1;
        // n->next = table[index+1];    
        // table[index]->next = n;
    
            if(table[index]==NULL)
            {
                table[index] = n;
            }
            
            else
            {
                n->next = table[index+1];    
                table[index]->next = n;
            }
            return true;
        }
    }// exit the while loop when you get to end of the file

    return false;   
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i<N; i++)
    {
    node *cursor = table[i];

        while(cursor!=NULL)
        {
            cursor = table[i];
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}
