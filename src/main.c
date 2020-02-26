#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "bst.h"

#define K 100000
int randomMap[K] = {0};

int* sort(int* input, int n)
{
    int* sorted = malloc(n*sizeof(int));
    int i;
    BST* bst = BSTAllocateIter();
    Node* current;
    for(i = 0; i < n; i++)
    {
        bst->Insert(bst->root, NULL, input[i]);
    }
    current = bst->FindMin(bst->root);
    i = 0;
    while(current != NULL)
    {
        sorted[i] = current->value;
        i++;
        current = bst->FindNext(current);
    }
    return sorted;
}

int* getRandomArray(int n)
{
    int* randArray = malloc(n*sizeof(int));
    int i, randValue;
    for(i = 0; i < n; i++)
    {
        randValue = rand() % K;
        while(randomMap[randValue])
        {
            randValue = rand() % K;
        }
        randomMap[randValue] = 1;
        randArray[i] = randValue;
    }
    return randArray;
}

int* getSortedArray(int n)
{
    int* sortArray = malloc(n*sizeof(int));
    int i;
    for(i = 0; i < n; i++)
    {
        sortArray[i] = n - i;
    }
    return sortArray;
}

void printArray(int* arr, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    int* randomArray, *sortedArray;
    int n = 100, i;
    srand(time(0));

    randomArray = getRandomArray(n);
    sortedArray = getSortedArray(n);

    printArray(randomArray, n);
    printArray(sortedArray, n);

	return 0;
}