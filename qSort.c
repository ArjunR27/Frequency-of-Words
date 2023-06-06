#include "hash.h"
#include <stdio.h>
#include <string.h>

/*This function swaps two wordNodes */
void swapNodes(wordNode* a, wordNode* b)
{
    wordNode tmp = *a;
    *a = *b;
    *b = tmp;
}

/*This function partitions the array into a left
  and right half where all elements to the left
  are smaller than the pivot and all elements
  to the right are greater than the pivot*/

int partition(wordNode* arr, int left, int right)
{
    wordNode pivot = arr[right];
    int i = left - 1;
    int j;
    for(j = left; j <= right - 1; j++)
    {
        if(arr[j].count > pivot.count
           || (arr[j].count == pivot.count
           && strcmp(arr[j].word, pivot.word) > 0))
        {
            i+=1;
            swapNodes(&arr[i], &arr[j]);
        }
    }
    swapNodes(&arr[i+1], &arr[right]);
    return i+1;
}

/*This function recursively performs the quicksort
  algorithm, recursing on the left and right half.*/
void qSort(wordNode* arr, int left, int right)
{
    if(left < right)
    {
        int pi = partition(arr, left, right);
        qSort(arr, left, pi-1);
        qSort(arr, pi+1, right);
    }
}
