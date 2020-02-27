#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bbst.h"

//Rotating based on node & node->parent
void RotateLeft(Node* node);
void RotateRight(Node* node);

void BalInsertRec(Node* parent, Node* node, int value);
Node* BalDeleteRec(BBST* bbst, Node* node, int value);
Node* BalFindNextRec(BBST* bbst, Node* node);
Node* BalFindPrevRec(BBST* bbst, Node* node);
Node* BalFindMinRec(Node* node);
Node* BalFindMaxRec(Node* node);

void BalInsertIter(Node* root, Node* node, int value);
Node* BalDeleteIter(BBST* bbst, Node* node, int value);
Node* BalFindNextIter(BBST* bbst, Node* node);
Node* BalFindPrevIter(BBST* bbst, Node* node);
Node* BalFindMinIter(Node* node);
Node* BalFindMaxIter(Node* node);

BBST* BBSTAllocateRec()
{
    BBST* bbst = (BBST*) malloc(sizeof(BBST));
    bbst->root = (Node*) calloc(1, sizeof(Node));
    bbst->Insert = BalInsertRec;
    bbst->Delete = BalDeleteRec;
    bbst->FindNext = BalFindNextRec;
    bbst->FindPrev = BalFindPrevRec;
    bbst->FindMin = BalFindMinRec;
    bbst->FindMax = BalFindMaxRec;
    return bbst;
}

BBST* BBSTAllocateIter()
{
    BBST* bbst = (BBST*) malloc(sizeof(BBST));
    bbst->root = (Node*) calloc(1, sizeof(Node));
    bbst->Insert = BalInsertIter;
    bbst->Delete = BalDeleteIter;
    bbst->FindNext = BalFindNextIter;
    bbst->FindPrev = BalFindPrevIter;
    bbst->FindMin = BalFindMinIter;
    bbst->FindMax = BalFindMaxIter;
    return bbst;
}

void BalInsertRec(Node* parent, Node* node, int value)
{
    //Error Checking
    if(parent == NULL || value == 0)
    {
        printf("BalInsertRec: Either NULL parent or 0 value given.\n");
        return;
    }

    //Allocate a node for inserting.
    if(node == NULL)
    {
        node = (Node*) calloc(1, sizeof(Node));
        node->value = value;
    }

    //Insert a root if there is no value for it.
    //Otherwise insert into left & right respectively
    if(parent->value == 0)
    {
        parent->value = value;
        printf("BalInsertRec: Root is %d\n", value);
        free(node);
        node = NULL;
    }
    else if(node->value > parent->value)
    {
        if(parent->rightChild)
        {
            BalInsertRec(parent->rightChild, node, value);
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
            BalInsertRec(parent->leftChild, node, value);
        }
        else
        {
            parent->leftChild = node;
            node->parent = parent;
        }
    }
}

Node* BalDeleteRec(BBST* bbst, Node* node, int value)
{
    Node* temp;

    if(node == NULL || node->value == 0)
    {
        printf("BalDeleteRec: Value not found: %d\n", value);
        return NULL;
    }
    
    if(node->value == value)
    {
        if(node->leftChild == NULL)
        {
            temp = node->rightChild;
            if(node == bbst->root)
            {
                bbst->root = temp;
            }
            free(node);
            node=NULL;
            return temp;
        }
        else if(node->rightChild == NULL)
        {
            temp = node->leftChild;
            if(node == bbst->root)
            {
                bbst->root = temp;
            }
            free(node);
            node=NULL;
            return temp;
        }
        temp = BalFindMinRec(node->leftChild);
        node->value = temp->value;
        node->rightChild = BalDeleteRec(bbst, node->rightChild, node->value);
    } 
    else if(node->value > value)
    {
        node->leftChild = BalDeleteRec(bbst, node->leftChild, value);
    }
    else
    {
        node->rightChild = BalDeleteRec(bbst, node->rightChild, value);
    }
    return node;
}

/**
 * @brief Helper function for finding the next node by going up the BBST.
 * 
 * @param node  The node needing to be traversed.
 * @return Node* 
 */
Node* BalTraverseUpNext(Node* node)
{
    if(node->parent == NULL)
    {
        return node;
    }

    //If node is leftChild, return it's parent.
    if(node->parent->value > node->value)
    {
        return node->parent;
    }
    else
    {
        return BalTraverseUpNext(node->parent);
    }
    
}

Node* BalFindNextRec(BBST* bbst, Node* node)
{
    Node* parentNode;

    //Error Checking
    if(node == NULL || bbst == NULL)
    {
        printf("BalFindNextRec: bbst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further right.
    if(BalFindMaxRec(bbst->root) == node)
    {
        printf("BalFindNextRec: Already at rightest node\n");
        return NULL;
    }
    
    //The next node is always the minimum value of the right subtree
    //or a right traversal up.
    if(node->rightChild)
    {
        return BalFindMinRec(node->rightChild);
    }
    else if(node->parent)
    {
        return BalTraverseUpNext(node);
    }
    else
    {
        return node;
    }
    
}

/**
 * @brief Helper function for finding the previous node by going up the BBST.
 * 
 * @param node The node needing to be traversed.
 * @return Node* 
 */
Node* BalTraverseUpPrev(Node* node)
{
    if(node->parent == NULL)
    {
        return node;
    }

    //If node is rightChild, return it's parent.
    if(node->parent->value < node->value)
    {
        return node->parent;
    }
    else
    {
        return BalTraverseUpPrev(node->parent);
    }
    
}

Node* BalFindPrevRec(BBST* bbst, Node* node)
{
    //Error Checking
    if(bbst == NULL || node == NULL)
    {
        printf("BalFindPrevRec: bbst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further left.
    if(BalFindMinRec(bbst->root) == node)
    {
        printf("BalFindPrevRec: Already at leftest node\n");
        return NULL;
    }
    
    //The previous node is always the max of the left subtree
    //or a left traversal up.
    if(node->leftChild)
    {
        return BalFindMaxRec(node->leftChild);
    }
    else if(node->parent)
    {
        return BalTraverseUpPrev(node);
    }
    else
    {
        return node;
    }
    
}

Node* BalFindMinRec(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    //Call this function until node has no more left children, then return.
    if(node->leftChild == NULL)
    {
        return node;
    } 
    else
    {
        return BalFindMinRec(node->leftChild);
    }
}

Node* BalFindMaxRec(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    } 
    
    //Call this function until node has no more right children, then return.
    if (node->rightChild == NULL)
    {
        return node;
    } 
    else
    {
        return BalFindMaxRec(node->rightChild);
    }
    
}

void BalInsertIter(Node* root, Node* node, int value)
{
    Node* parent;
    int done = 0;
    parent = root;

    //Error Checking
    if(parent == NULL || value == 0)
    {
        printf("BalInsertIter: Either NULL parent or 0 value given.\n");
        return;
    }

    //Assign root value
    if(parent->value == 0)
    {
        parent->value = value;
        printf("BalInsertIter: Root is %d\n", value);
    }
    else
    {
        node = calloc(1, sizeof(Node));
        node->value = value;

        //Check parent if > or <.
        //Go into right/left children as necessary.
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
                printf("BalInsertIter: Duplicate value given, did not insert value: %d\n", value);
                done = 1;
            }
            
        }
    }
    
}

Node* BalDeleteIter(BBST* bbst, Node* node, int value)
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
                    prev = BalFindPrevIter(bbst, node);
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
                    next = BalFindNextIter(bbst, node);
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
    printf("BalDeleteIter: Value not found: %d\n", value);
    return NULL;
}

Node* BalFindNextIter(BBST* bbst, Node* node)
{
    Node* next;
    next = node;

    //Error Checking
    if(bbst == NULL || node == NULL)
    {
        printf("BalFindNextIter: bbst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further right.
    if(BalFindMaxIter(bbst->root) == node)
    {
        printf("BalFindNextIter: Already at rightest node\n");
        return NULL;
    }

    //The next node is always the min of the right subtree.
    if(next->rightChild)
    {
        return BalFindMinIter(next->rightChild);
    }

    //or a right traversal up.
    while(next->parent->value < next->value)
    {
        next = next->parent;
    }
    return next->parent;
}

Node* BalFindPrevIter(BBST* bbst, Node* node)
{
    Node* prev;
    prev = node;

    //Error Checking
    if(bbst == NULL || node == NULL)
    {
        printf("BalFindNextIter: bbst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further left.
    if(BalFindMinIter(bbst->root) == node)
    {
        printf("FindPrev: Already at leftest node\n");
        return NULL;
    }

    //The previous node is always the max of the left subtree.
    if(prev->leftChild)
    {
        return BalFindMaxIter(prev->leftChild);
    }

    //or a left traversal up.
    while(prev->parent->value > prev->value)
    {
        prev = prev->parent;
    }
    return prev->parent;
}

Node* BalFindMinIter(Node* node)
{
    Node* minNode;
    minNode = node;

    //Keep setting minNode to left child until it doesn't have one.
    while(minNode->leftChild)
    {
        minNode = minNode->leftChild;
    }
    return minNode;
}

Node* BalFindMaxIter(Node* node)
{
    Node* maxNode;
    maxNode = node;

    //Keep setting maxNode to right child until it doesn't have one.
    while(maxNode->rightChild)
    {
        maxNode = maxNode->rightChild;
    }
    return maxNode;
}

