#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#define LOAD_FACTOR 0.5
#define HASH_MULTIPLIER 31


/*Hash Code function based on
  previous classes hash code function */
int hashCode(char* word)
{
    int hash = 1;
    int c;
    while((c = *word++))
    {
        hash = hash * HASH_MULTIPLIER + c;
    }
    return abs(hash);
}

/* Creates a hashTable of specified size
   initializes all attributes of hashTable*/

Hash createHashTable(int size)
{
    Hash newTable;
    newTable.curSize = 0;
    newTable.maxSize = size;
    newTable.hash = (wordNode*)calloc(newTable.maxSize, sizeof(wordNode));
    return newTable;
}

/*Adds a string and a count to the hash table
  uses quadratic probing to handle collisions*/

void add(Hash* curHash, char* string, int countNum)
{
     int i;
     int index;
     if((((double)curHash -> curSize) / curHash -> maxSize) >= LOAD_FACTOR)
     {
        rehash(curHash);
     }

     index = (hashCode(string)) % (curHash -> maxSize);


     if(curHash -> hash[index].word == NULL)
     {
        curHash -> hash[index].word =
        (char*)malloc((strlen(string)+1) * sizeof(char));

        strcpy(curHash -> hash[index].word, string);
        curHash -> hash[index].count = countNum;
        curHash -> curSize += 1;
     }
     else if(strcmp(curHash -> hash[index].word, string) == 0)
     {
        curHash -> hash[index].count++;
     }

     /*COLLISION HANDLING*/
     else
     {
        i = 1;
        while(1)
        {
            index = (index + (i * i)) % (curHash -> maxSize);
            if(curHash -> hash[index].word == NULL)
            {
                curHash -> hash[index].word =
                (char*)malloc((strlen(string) + 1));

                strcpy(curHash -> hash[index].word, string);
                curHash -> hash[index].count = countNum;
                curHash -> curSize += 1;
                break;
            }
            else if(strcmp(curHash -> hash[index].word, string) == 0)
            {
                curHash -> hash[index].count += countNum;
                break;
            }
            i++;
        }
     }

}

/*Rehashing function for when the hash table reaches its LOAD_FACTOR
  creates a new array of wordNodes, double the size, and then adds all
  items that are not NULL from the old hash table into the new one*/
void rehash(Hash* curHash)
{
    int i;
    int oldSize = curHash -> maxSize;
    int newSize = curHash -> maxSize*2;
    wordNode* oldHash = curHash -> hash;
    curHash -> maxSize = newSize;
    curHash -> curSize = 0;
    curHash -> hash = (wordNode*)calloc(curHash -> maxSize, sizeof(wordNode));

   for(i = 0;i<oldSize;i++)
   {
       if(oldHash[i].word != NULL)
       {
           add(curHash, oldHash[i].word, oldHash[i].count);
           free(oldHash[i].word);
           oldHash[i].word = NULL;
       }
   }
   free(oldHash);
   oldHash = NULL;
}



/*This function returns all of the values from the hash table
  that are not NULL with a wordNode pointer to the first
  one. This is useful when sorting, because rather than sorting
  the entire hash table, I sort only the values that are
  not NULL */
wordNode* getImportantValues(Hash *curHash)
{

     int size = curHash -> curSize;
     wordNode* importantValues =
     (wordNode*)malloc(size * sizeof(wordNode));

     int i;
     int j = 0;
     for(i = 0; i < curHash -> maxSize; i++)
     {
        if(curHash -> hash[i].word != NULL)
        {
            importantValues[j].word = curHash -> hash[i].word;
            importantValues[j].count = curHash -> hash[i].count;
            j++;
        }
     }
    return importantValues;

}


/*This function is used to free everything related to the hash table
  and the wordNode array created when using getImportantValues. */
void freeEverything(Hash* curHash, wordNode* iValues)
{
    int i;
    for(i = 0; i < curHash -> maxSize; i++)
    {
       if(curHash -> hash[i].word != NULL)
       {
           free(curHash -> hash[i].word);
           curHash -> hash[i].word = NULL;
       }
    }

    free(iValues);
    free(curHash -> hash);
    curHash -> curSize = 0;
    curHash -> maxSize = 0;
    curHash -> hash = NULL;
}
