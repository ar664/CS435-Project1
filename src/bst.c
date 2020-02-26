#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

BST* BSTAllocateRec()
{
    BST* bst = (BST*) malloc(sizeof(BST));
    bst->root = (Node*) calloc(1, sizeof(Node));
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
    bst->root = (Node*) calloc(1, sizeof(Node));
    bst->Insert = InsertIter;
    bst->Delete = DeleteIter;
    bst->FindNext = FindNextIter;
    bst->FindPrev = FindPrevIter;
    bst->FindMin = FindMinIter;
    bst->FindMax = FindMaxIter;
    return bst;
}

void InsertRec(Node* parent, Node* node, int value)
{
    if(node == NULL)
    {
        node = (Node*) calloc(1, sizeof(Node));
        node->value = value;
    }

    if(parent->value == 0)
    {
        parent->value = value;
        printf("InsertRec: Root is %d\n", value);
        free(node);
        node = NULL;
    }
    else if(node->value > parent->value)
    {
        if(parent->rightChild)
        {
            InsertRec(parent->rightChild, node, value);
        }
        else
        {
            parent->rightChild = node;
            node->parent = parent;
        }
    }
    else if(node->value < parent->value)
    {
        if(parent->leftChild)
        {
            InsertRec(parent->leftChild, node, value);
        }
        else
        {
            parent->leftChild = node;
            node->parent = parent;
        }
    }
}

Node* DeleteRec(BST* bst, Node* node, int value)
{
    Node* temp;

    if(node == NULL || node->value == 0)
    {
        printf("Value not found during delete: %d\n", value);
    } 
    else if(node->value == value)
    {
        if(node->leftChild == NULL)
        {
            temp = node->rightChild;
            if(node == bst->root)
            {
                bst->root = temp;
            }
            free(node);
            node=NULL;
            return temp;
        }
        else if(node->rightChild == NULL)
        {
            temp = node->leftChild;
            if(node == bst->root)
            {
                bst->root = temp;
            }
            free(node);
            node=NULL;
            return temp;
        }
        temp = FindMinRec(node->leftChild);
        node->value = temp->value;
        node->rightChild = DeleteRec(bst, node->rightChild, node->value);
    } 
    else if(node->value > value)
    {
        node->leftChild = DeleteRec(bst, node->leftChild, value);
    }
    else
    {
        node->rightChild = DeleteRec(bst, node->rightChild, value);
    }
    return node;
}

Node* TraverseUpNext(Node* node)
{
    if(node->parent == NULL)
    {
        return node;
    }
    else
    {
        if(node->parent->value > node->value)
        {
            return node->parent;
        }
        else
        {
            return TraverseUpNext(node->parent);
        }
    }
    
}

Node* FindNextRec(BST* bst, Node* node)
{
    Node* parentNode;
    if(node == NULL || bst == NULL)
    {
        printf("FindNextRec: bst or node given is null\n");
        return NULL;
    }
    if(FindMaxRec(bst->root) == node)
    {
        printf("FindNextRec: Already at rightest node\n");
        return NULL;
    }
    if(node->rightChild)
    {
        return FindMinRec(node->rightChild);
    }
    else if(node->parent)
    {
        return TraverseUpNext(node);
    }
    else
    {
        return node;
    }
    
}

Node* TraverseUpPrev(Node* node)
{
    if(node->parent == NULL)
    {
        return node;
    }
    else
    {
        if(node->parent->value < node->value)
        {
            return node->parent;
        }
        else
        {
            return TraverseUpPrev(node->parent);
        }
    }
    
}

Node* FindPrevRec(BST* bst, Node* node)
{
    if(FindMinRec(bst->root) == node)
    {
        printf("FindPrev: Already at leftest node\n");
        return NULL;
    }
    if(node->leftChild)
    {
        return FindMaxRec(node->leftChild);
    }
    else if(node->parent)
    {
        if(node->parent->value < node->value)
        {
            return FindPrevRec(bst, node->parent);
        }
        return node->parent;
    }
    else
    {
        return node;
    }
    
}

Node* FindMinRec(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    } 
    if(node->leftChild == NULL)
    {
        return node;
    } 
    else
    {
        return FindMinRec(node->leftChild);
    }
}

Node* FindMaxRec(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    } 
    else if (node->rightChild == NULL)
    {
        return node;
    } 
    else
    {
        return FindMaxRec(node->rightChild);
    }
    
}

void InsertIter(Node* root, Node* node, int value)
{
    Node* parent;
    int done = 0;

    parent = root;
    if(parent == NULL)
    {
        printf("Error for InsertIter you must give root as first variable\n");
        return;
    }

    if(parent->value == 0)
    {
        parent->value = value;
        printf("InsertIter: Root is %d\n", value);
    }
    else
    {
        node = calloc(1, sizeof(Node));
        node->value = value;

        parent = root;
        while(!done)
        {
            if(parent->value > value)
            {
                if(parent->leftChild)
                {
                    parent = parent->leftChild;
                }
                else
                {
                    parent->leftChild = node;
                    node->parent = parent;
                    done = 1;
                }
            } else if(parent->value < value)
            {
                if(parent->rightChild)
                {
                    parent = parent->rightChild;
                }
                else
                {
                    parent->rightChild = node;
                    node->parent = parent;
                    done = 1;
                }
            } else
            {
                printf("Duplicate value given, did not insert value: %d\n", value);
                done = 1;
            }
            
        }
    }
    
}

Node* DeleteIter(BST* bst, Node* node, int value)
{
    Node* looseRight, *looseLeft, *prev, *next;
    while(node != NULL)
    {
        if(node->value == value)
        {
            if(node->rightChild)
            {
                looseRight = node->rightChild;
                if(looseRight->leftChild)
                {
                    prev = FindPrevIter(bst, node);
                    prev->rightChild = looseRight;
                } 
                looseRight->leftChild = node->leftChild;
                //Check Root
            }
            else if(node->leftChild)
            {
                looseLeft = node->leftChild;
                if(looseLeft->rightChild)
                {
                    next = FindNextIter(bst, node);
                    next->leftChild = looseLeft;
                }
                looseLeft->rightChild = node->rightChild;
                //Check Root
            }
        } 
        else if(node->value < value)
        {
            node = node->rightChild;
        }
        else if(node->value > value)
        {
            node = node->leftChild;
        }
    }
    printf("Value not found during delete: %d\n", value);
    return NULL;
}

Node* FindNextIter(BST* bst, Node* node)
{
    Node* next;
    next = node;
    if(bst == NULL || node == NULL)
    {
        printf("FindNextIter: bst or node given is null\n");
        return NULL;
    }
    if(FindMaxIter(bst->root) == node)
    {
        printf("FindNextIter: Already at rightest node\n");
        return NULL;
    }
    if(next->rightChild)
    {
        return FindMinIter(next->rightChild);
    }
    while(next->parent->value < next->value)
    {
        next = next->parent;
    }
    return next->parent;
}

Node* FindPrevIter(BST* bst, Node* node)
{
    Node* prev;
    prev = node;
    if(FindMinIter(bst->root) == node)
    {
        printf("FindPrev: Already at leftest node\n");
        return NULL;
    }
    if(prev->leftChild)
    {
        return FindMaxIter(prev->leftChild);
    }
    while(prev->parent->value > prev->value)
    {
        prev = prev->parent;
    }
    return prev;
}

Node* FindMinIter(Node* node)
{
    Node* min;
    min = node;
    while(min->leftChild)
    {
        min = min->leftChild;
    }
    return min;
}

Node* FindMaxIter(Node* node)
{
    Node* max;
    max = node;
    while(max->rightChild)
    {
        max = max->rightChild;
    }
    return max;
}

