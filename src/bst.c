#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

Node* DeleteNode(BST* bst, Node* node);

void InsertRec(Node* parent, Node* node, int value);
Node* DeleteRec(BST* bst, Node* node, int value);
Node* FindNextRec(BST* bst, Node* node);
Node* FindPrevRec(BST* bst, Node* node);
Node* FindMinRec(Node* node);
Node* FindMaxRec(Node* node);

void InsertIter(Node* root, Node* node, int value);
Node* DeleteIter(BST* bst, Node* node, int value);
Node* FindNextIter(BST* bst, Node* node);
Node* FindPrevIter(BST* bst, Node* node);
Node* FindMinIter(Node* node);
Node* FindMaxIter(Node* node);

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

void CreateRelation(Node* parent, Node* child, int opt)
{
    int i;
    i = 0;
}

Node* DeleteNode(BST* bst, Node* node)
{
    Node* prev, *next, *left, *right, *parent, *current;
    int i;

    prev = FindPrevIter(bst, node);
    next = FindNextIter(bst, node);
    left = node->leftChild;
    right = node->rightChild;
    parent = node->parent;

    if(left == NULL && right == NULL)
    {
        if(node == bst->root)
        {
            node->value = 0;
            return node;
        }

        if(parent->value > node->value)
        {
            parent->leftChild = NULL;
        }
        else
        {
            parent->rightChild = NULL;
        }

        current = parent;
    }
    else if(left && right)
    {
        if(node == bst->root)
        {
            bst->root = prev;
        }

        if(prev->leftChild)
        {
            if(prev->parent->value > prev->value)
            {
                prev->parent->leftChild = prev->leftChild;
            }
            else
            {
                prev->parent->rightChild = prev->leftChild;
            }
            prev->leftChild->parent = prev->parent;
        }

        if(prev->parent != node)
        {
            if(prev->parent->value > prev->value)
            {
                prev->parent->leftChild = NULL;
            }
            else
            {
                prev->parent->rightChild = NULL;
            }
        }

        prev->rightChild = right;
        right->parent = prev;
        prev->parent = parent;
        current = prev;
    }
    else if(right == NULL)
    {
        if(node == bst->root)
        {
            bst->root = left;
        }

        if(parent->value > node->value)
        {
            parent->leftChild = left;
        }
        else
        {
            parent->rightChild = left;
        }
        
        left->parent = parent;
        current = left;
    }
    else
    {
        if(node == bst->root)
        {
            bst->root = right;
        }

        if(parent->value > node->value)
        {
            parent->leftChild = right;
        }
        else
        {
            parent->rightChild = right;
        }
        
        right->parent = parent;
        current = right;
    }
    
    free(node);
    node = NULL;
    return current; 
}

void InsertRec(Node* parent, Node* node, int value)
{
    //Error Checking
    if(parent == NULL || value == 0)
    {
        printf("InsertRec: Either NULL parent or 0 value given.\n");
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
        printf("DeleteRec: Value not found: %d\n", value);
        return NULL;
    }
    
    if(node->value == value)
    {
        return DeleteNode(bst, node);
    } 
    else if(node->value > value)
    {
        return DeleteRec(bst, node->leftChild, value);
    }
    else
    {
        return DeleteRec(bst, node->rightChild, value);
    }
}

/**
 * @brief Helper function for finding the next node by going up the BST.
 * 
 * @param node  The node needing to be traversed.
 * @return Node* 
 */
Node* TraverseUpNext(Node* node)
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
        return TraverseUpNext(node->parent);
    }
    
}

Node* FindNextRec(BST* bst, Node* node)
{
    Node* parentNode;

    //Error Checking
    if(node == NULL || bst == NULL)
    {
        printf("FindNextRec: bst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further right.
    if(FindMaxRec(bst->root) == node)
    {
        printf("FindNextRec: Already at rightest node\n");
        return NULL;
    }
    
    //The next node is always the minimum value of the right subtree
    //or a right traversal up.
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

/**
 * @brief Helper function for finding the previous node by going up the BST.
 * 
 * @param node The node needing to be traversed.
 * @return Node* 
 */
Node* TraverseUpPrev(Node* node)
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
        return TraverseUpPrev(node->parent);
    }
    
}

Node* FindPrevRec(BST* bst, Node* node)
{
    //Error Checking
    if(bst == NULL || node == NULL)
    {
        printf("FindPrevRec: bst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further left.
    if(FindMinRec(bst->root) == node)
    {
        printf("FindPrevRec: Already at leftest node\n");
        return NULL;
    }
    
    //The previous node is always the max of the left subtree
    //or a left traversal up.
    if(node->leftChild)
    {
        return FindMaxRec(node->leftChild);
    }
    else if(node->parent)
    {
        return TraverseUpPrev(node);
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

    //Call this function until node has no more left children, then return.
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
    
    //Call this function until node has no more right children, then return.
    if (node->rightChild == NULL)
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

    //Error Checking
    if(parent == NULL || value == 0)
    {
        printf("InsertIter: Either NULL parent or 0 value given.\n");
        return;
    }

    //Assign root value
    if(parent->value == 0)
    {
        parent->value = value;
        printf("InsertIter: Root is %d\n", value);
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
                printf("InsertIter: Duplicate value given, did not insert value: %d\n", value);
                done = 1;
            }
            
        }
    }
    
}

Node* DeleteIter(BST* bst, Node* node, int value)
{
    Node* temp;
    temp = bst->root;
    while(temp != NULL)
    {
        if(temp->value == value)
        {
            return DeleteNode(bst, temp);
        }
        else if(temp->value > value )
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }
    printf("DeleteIter: Value not found: %d\n", value);
    return NULL;
}

Node* FindNextIter(BST* bst, Node* node)
{
    Node* next;
    next = node;

    //Error Checking
    if(bst == NULL || node == NULL)
    {
        printf("FindNextIter: bst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further right.
    if(FindMaxIter(bst->root) == node)
    {
        printf("FindNextIter: Already at rightest node\n");
        return NULL;
    }

    //The next node is always the min of the right subtree.
    if(next->rightChild)
    {
        return FindMinIter(next->rightChild);
    }

    //or a right traversal up.
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

    //Error Checking
    if(bst == NULL || node == NULL)
    {
        printf("FindNextIter: bst or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further left.
    if(FindMinIter(bst->root) == node)
    {
        printf("FindPrev: Already at leftest node\n");
        return NULL;
    }

    //The previous node is always the max of the left subtree.
    if(prev->leftChild)
    {
        return FindMaxIter(prev->leftChild);
    }

    //or a left traversal up.
    while(prev->parent->value > prev->value)
    {
        prev = prev->parent;
    }
    return prev->parent;
}

Node* FindMinIter(Node* node)
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

Node* FindMaxIter(Node* node)
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

