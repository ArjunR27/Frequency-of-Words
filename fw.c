#include "hash.h"
#include "qSort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
/*This function is used to readFromFiles and
  add values to the hashTable. This method
  was modified from the read_long_line from
  lab02. It rather reads each word, delimited
  by alphabetic characters, and the adds
  it to the hash table. */
void readFromFile(FILE* file, Hash* curHash)
{
    int chr;
    int lineSize = 128;
    int lineIndex = 0;
    char* word;
    if(!(word = (char *)malloc(lineSize + sizeof(*word))))
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while((chr = getc(file)) != EOF)
    {
        if(lineIndex == lineSize)
        {
            lineSize *= 2;
            if(!(word = (char *)realloc(word, lineSize + sizeof(*word))))
            {
                 perror("realloc");
                 exit(EXIT_FAILURE);
            }
        }
        if(isalpha(chr))
        {
           chr = tolower(chr);
           word[lineIndex] = chr;
           lineIndex++;
        }

        else if (lineIndex > 0)
        {

            word[lineIndex] = '\0';
            add(curHash, word, 1);

            lineIndex = 0;
            free(word);
            if(!(word = (char *)malloc(lineSize + sizeof(*word))))
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
        }
    }

    if(lineIndex < 0)
    {
        free(word);
    }
    free(word);
}

/*This main function is utilized
  to read arguments from the command line
  as well as stdin, and display the specified
  output*/

int main(int argc, char* argv[]) {
    wordNode* iValues;
    int num = 10;
    Hash h = createHashTable(5000);
    int fileCount = 0;
    FILE* file = NULL;
    int i;
    int opt;

    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch(opt)
        {
            case 'n':
                if(!(num = atoi(optarg)) || num < 0)
                {
                    fprintf(stderr,
                    "Usage: %s [-n num] [file1 [file2 [...]]] \n", argv[0]);
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr,
                "Usage: %s [-n num] [file1 [file2 [...]]] \n", argv[0]);
                exit(EXIT_FAILURE);
        }

    }

    for(i = optind; i < argc; i++) {
        if((file = fopen(argv[i], "r")) != NULL)
        {
            readFromFile(file, &h);
            fclose(file);
            fileCount++;
        }
        else
        {
            fprintf(stderr, "usage: fw [-n num] [file1 [file2 ...]]\n");
        }
    }

    if(optind == argc)
    {
         if(isatty(0))
         {
             fprintf(stderr, "Error reading from stdin\n");
             exit(EXIT_FAILURE);
         }
         readFromFile(stdin, &h);
    }

    iValues = getImportantValues(&h);
    qSort(iValues, 0, h.curSize-1);
    printf("The top %d words (out of %d) are:\n", num, h.curSize);
    if(h.curSize < num)
    {
         num = h.curSize;
    }

    for(i = 0; i < num; i++)
    {
        printf("%9d %s\n", iValues[i].count, iValues[i].word);
    }
    freeEverything(&h, iValues);
    return 0;
}
