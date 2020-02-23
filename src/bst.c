#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BST* BSTAllocateRec()
{
    BST* bst = (BST*) malloc(sizeof(BST));
    bst->root = nodeList;
    bst->currentNode = bst->root;
    bst->Insert = InsertRec;
    bst->Delete = DeleteRec;
    bst->FindNext = FindNextRec;
    bst->FindPrev = FindPrevRec;
    bst->FindMin = FindMinRec;
    bst->FindMax = FindMaxRec;
    return bst;
}

BST* BSTAllocateIter()
{
    BST* bst = (BST*) malloc(sizeof(BST));
    bst->root = nodeList;
    bst->currentNode = bst->root;
    bst->Insert = InsertIter;
    bst->Delete = DeleteIter;
    bst->FindNext = FindNextIter;
    bst->FindPrev = FindPrevIter;
    bst->FindMin = FindMinIter;
    bst->FindMax = FindMaxIter;
    return bst;
}

void InsertRec(Node* node, int value)
{
    if(node->value == 0)
    {
        node->value = value;
    } else if(node->value < value)
    {
        InsertRec(node->rightChild, value);
    } else if(node->value > value)
    {
        InsertRec(node->leftChild, value);
    } else
    {
        printf("Duplicate value given, did not insert value: %d\n", value);
    }
}

void DeleteRec(Node* node, int value)
{
    if(node->value == 0)
    {
        printf("Value not found during delete: %d\n", value);
    } else if(node->value == value)
    {
        node->value = 0;
    }
}

void FindNextRec(Node* node)
{

}

void FindPrevRec(Node* node)
{

}

void FindMinRec(Node* node)
{

}

void FindMaxRec(Node* node)
{

}

void InsertIter(Node* node, int value)
{

}

void DeleteIter(Node* node, int value)
{

}

void FindNextIter(Node* node)
{

}

void FindPrevIter(Node* node)
{

}

void FindMinIter(Node* node)
{

}

void FindMaxIter(Node* node)
{

}

