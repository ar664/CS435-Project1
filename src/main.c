#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <glib.h>
#include "bst.h"
#include "avl.h"

#define K 50000
GHashTable* hashTable = NULL;

int* sort(int* input, int n)
{
    Node* current;
    int* sorted, i;
    BST* bst;
    
    //Error Checking
    if(input == NULL || n == 0)
    {
        printf("sort: Either input = NULL or n = 0\n");
        return NULL;
    }

    //Allocate memory
    sorted = malloc(n*sizeof(int));
    bst = BSTAllocateIter();

    //Insert array into BST
    for(i = 0; i < n; i++)
    {
        bst->Insert(bst->root, NULL, input[i]);
    }

    //Do a left->right traversal using FindNext
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

/**
 * @brief Get an array with distinct values of range K. 
 * 
 * @param n     The size of the array from 1 - K
 * @return int* 
 * 
 */
int* getRandomArray(int n)
{
    int* randArray;
    int i, randValue;

    //K is our range of numbers that we can choose from.
    if(n > K)
    {
        printf("getRandomArray: Max n can be is: %d\n", K);
        return NULL;
    }

    //Cannot allocate empty array.
    if(n <= 0)
    {
        printf("getRandomArray: n cannot be <= 0\n");
        return NULL;
    }

    if(hashTable == NULL)
    {
        hashTable = g_hash_table_new(g_int_hash, g_int_equal);
    }

    randArray = malloc(n*sizeof(int));

    //Get a random number each time.
    for(i = 0; i < n; i++)
    {
        randValue = rand() % K;
        randArray[i] = randValue;

        //If random number is already in the map, keep getting one until it's not.
        while(g_hash_table_contains(hashTable, &randArray[i]))
        {
            randValue = rand() % K;
            randArray[i] = randValue;
        }
        
        //Assign map & values
        g_hash_table_insert(hashTable, &randArray[i], &randArray[i]);
    }

    return randArray;
}

int* getSortedArray(int n)
{
    int* sortArray = malloc(n*sizeof(int));
    int i;

    if(n <= 0)
    {
        printf("getSortedArray: n cannot be <= 0\n");
        return NULL;
    }

    //Set each value in descending sorted order starting with n
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
    AVL* avlIter, *avlRec;
    srand(time(0));

    randomArray = getRandomArray(n);
    sortedArray = getSortedArray(n);

    printArray(randomArray, n);
    printArray(sortedArray, n);

    bstIter = BSTAllocateIter();
    bstRec = BSTAllocateRec();

    //Insert into both bst versions from randomArray
    for(i = 0; i < n; i++)
    {
        bstIter->Insert(bstIter->root, NULL, randomArray[i]);
        bstRec->Insert(bstRec->root, NULL, randomArray[i]);
    }

    travIter = bstIter->FindMin(bstIter->root);
    travRec = bstRec->FindMin(bstRec->root);

    //Traverse bsts inOrder
    for(i = 0; i < n-1; i++)
    {
        travIter = bstIter->FindNext(bstIter, travIter);
        travRec = bstRec->FindNext(bstRec, travRec);
    }

    printf("Right Most Node: %d or %d\n", travIter->value, travRec->value);
    
    //Traverse bsts backwards
    for(i = 0; i < n-1; i++)
    {
        travIter = bstIter->FindPrev(bstIter, travIter);
        travRec = bstRec->FindPrev(bstRec, travRec);
    }

    printf("Left Most Node: %d or %d\n", travIter->value, travRec->value);

    //Sort randomArray with sort function.
    bstSorted = sort(randomArray, n);

    printf("BST sort: ");
    printArray(bstSorted, n);

    avlIter = AVLAllocateIter();
    avlRec = AVLAllocateRec();

    for(i = 0; i < n; i++)
    {
        avlIter->Insert(avlIter, avlIter->root, NULL, randomArray[i]);
        avlRec->Insert(avlRec, avlRec->root, NULL, randomArray[i]);
    }

    travIter = avlIter->root;
    travRec = avlRec->root;

    for(i = 0; i < n-1; i++)
    {
        travIter = avlIter->FindNext(avlIter, travIter);
        travRec = avlRec->FindNext(avlRec, travRec);
    }

    printf("Left Most Node: %d or %d\n", travIter->value, travRec->value);

    for(i = 0; i < n-1; i++)
    {
        travIter = avlIter->FindPrev(avlIter, travIter);
        travRec = avlRec->FindPrev(avlRec, travRec);
    }

    printf("Right Most Node: %d or %d\n", travIter->value, travRec->value);

	return 0;
}