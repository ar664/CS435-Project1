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
        current = bst->FindNext(bst, current);
    }
    return sorted;
}

int* getRandomArray(int n)
{
    int* randArray;
    int i, randValue;
    if(n > K)
    {
        printf("Max n can be is: %d\n", K);
        return NULL;
    }
    randArray = malloc(n*sizeof(int));

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
    int* randomArray, *sortedArray, *bstSorted;
    int n = 100, i;
    BST* bstIter, *bstRec;
    Node* travIter, *travRec;
    srand(time(0));

    randomArray = getRandomArray(n);
    sortedArray = getSortedArray(n);

    printArray(randomArray, n);
    printArray(sortedArray, n);

    bstIter = BSTAllocateIter();
    bstRec = BSTAllocateRec();
    printf("bstIter root is %d\n", bstIter->root->value);

    for(i = 0; i < n; i++)
    {
        bstIter->Insert(bstIter->root, NULL, randomArray[i]);
        bstRec->Insert(bstRec->root, NULL, randomArray[i]);
    }
    travIter = bstIter->FindMin(bstIter->root);
    travRec = bstRec->FindMin(bstRec->root);

    for(i = 0; i < n-1; i++)
    {
        travIter = bstIter->FindNext(bstIter, travIter);
        travRec = bstRec->FindNext(bstRec, travRec);
    }

    printf("Right Most Node: %d or %d\n", travIter->value, travRec->value);
    
    for(i = 0; i < n-1; i++)
    {
        travIter = bstIter->FindPrev(bstIter, travIter);
        travRec = bstRec->FindPrev(bstRec, travRec);
    }

    printf("Left Most Node: %d or %d\n", travIter->value, travRec->value);

    bstSorted = sort(randomArray, n);

    printf("BST sort: ");
    for(i = 0; i < n; i++)
    {
        printf("%d ", bstSorted[i]);
    }
    printf("\n");

	return 0;
}