#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "avl.h"

//Rotating based on node
void RotateLeft(AVL *avl, Node* node);
void RotateRight(AVL* avl, Node* node);

//Get the height of the node
int GetHeight(Node* leftChild, Node* rightChild);

//Traverse up the parents and recalculate the heights for the nodes
void UpdateHeights(Node* node);

//Balance the trees with rotations
void BalanceTree(AVL *avl);

//Calculate the balance left - right
int CalcBalance(Node* node);

void AVLInsertRec(AVL* avl, Node* parent, Node* node, int value);
Node* AVLDeleteRec(AVL* avl, Node* node, int value);
Node* AVLFindNextRec(AVL* avl, Node* node);
Node* AVLFindPrevRec(AVL* avl, Node* node);
Node* AVLFindMinRec(Node* node);
Node* AVLFindMaxRec(Node* node);

void AVLInsertIter(AVL* avl, Node* root, Node* node, int value);
Node* AVLDeleteIter(AVL* avl, Node* node, int value);
Node* AVLFindNextIter(AVL* avl, Node* node);
Node* AVLFindPrevIter(AVL* avl, Node* node);
Node* AVLFindMinIter(Node* node);
Node* AVLFindMaxIter(Node* node);

AVL* AVLAllocateRec()
{
    AVL* avl = (AVL*) malloc(sizeof(AVL));
    avl->root = (Node*) calloc(1, sizeof(Node));
    avl->Insert = AVLInsertRec;
    avl->Delete = AVLDeleteRec;
    avl->FindNext = AVLFindNextRec;
    avl->FindPrev = AVLFindPrevRec;
    avl->FindMin = AVLFindMinRec;
    avl->FindMax = AVLFindMaxRec;
    return avl;
}

AVL* AVLAllocateIter()
{
    AVL* avl = (AVL*) malloc(sizeof(AVL));
    avl->root = (Node*) calloc(1, sizeof(Node));
    avl->Insert = AVLInsertIter;
    avl->Delete = AVLDeleteIter;
    avl->FindNext = AVLFindNextIter;
    avl->FindPrev = AVLFindPrevIter;
    avl->FindMin = AVLFindMinIter;
    avl->FindMax = AVLFindMaxIter;
    return avl;
}

int GetHeight(Node* leftChild, Node* rightChild)
{
    if(leftChild == NULL && rightChild == NULL)
    {
        return 0;
    }

    if(leftChild == NULL)
    {
        return 1 + rightChild->height;
    }
    else if(rightChild == NULL)
    {
        return 1 + leftChild->height;
    }
    else
    {
        return 1 + (int) fmax(leftChild->height, rightChild->height);
    }   
}

void UpdateHeights(Node* node)
{
    Node* temp;

    if(node == NULL)
    {
        return;
    }

    temp = node;

    while(temp != NULL)
    {
        temp->height = GetHeight(temp->leftChild, temp->rightChild);
        temp = temp->parent;
    }
}

void RotateLeft(AVL* avl, Node* node)
{
    Node* rightTree, *rightLeftTree;

    if(avl == NULL || node == NULL)
    {
        printf("RotateLeft: Either null avl or null node given.\n");
        return;
    }

    if(node->rightChild == NULL)
    {
        printf("RotateLeft: Invalid rotation, no rightChild.\n");
        return;
    }

    rightTree = node->rightChild;
    rightLeftTree = rightTree->leftChild;

    if(node == avl->root)
    {
        avl->root = rightTree;
        rightTree->parent = NULL;
    }
    else
    {
        rightTree->parent = node->parent;
        if(rightTree->parent->rightChild == node)
        {
            rightTree->parent->rightChild = rightTree;
        }
        else
        {        
            rightTree->parent->leftChild = rightTree;
        } 
    }

    //Update Node
    node->parent = rightTree;
    node->rightChild = rightLeftTree;

    //Update Right Tree
    rightTree->leftChild = node;

    //Update RightLeft Tree
    if(rightLeftTree != NULL)
    {
        rightLeftTree->parent = node;
    }

    UpdateHeights(node);
}

void RotateRight(AVL *avl, Node* node)
{
    Node* leftTree, *leftRightTree;

    if(avl == NULL || node == NULL)
    {
        printf("RotateRight: Either null avl or null node given.\n");
        return;
    }

    if(node->leftChild == NULL)
    {
        printf("RotateRight: Invalid rotation, no leftChild.\n");
        return;
    }

    leftTree = node->leftChild;
    leftRightTree = leftTree->rightChild;

    if(node == avl->root)
    {
        avl->root = leftTree;
        leftTree->parent = NULL;
    }
    else
    {
        leftTree->parent = node->parent;
        if(leftTree->parent->rightChild == node)
        {
            leftTree->parent->rightChild = leftTree;
        }
        else
        {        
            leftTree->parent->leftChild = leftTree;
        } 
    }
    
    //Update Node
    node->parent = leftTree;
    node->leftChild = leftRightTree;

    //Update Left Tree
    leftTree->rightChild = node;

    //Update LeftRight Tree
    if(leftRightTree != NULL)
    {
        leftRightTree->parent = node;
    }

    UpdateHeights(node);
}

int CalcBalance(Node* node)
{
    if(node == NULL)
    {
        printf("CalcBalance: Null node given.\n");
        return 0;
    }

    if(node->leftChild == NULL && node->rightChild == 0)
    {
        return 0;
    }

    if(node->leftChild == NULL)
    {
        return -(node->rightChild->height+1);
    }
    else if(node->rightChild == NULL)
    {
        return node->leftChild->height+1;
    }
    else
    {
        return node->leftChild->height - node->rightChild->height;
    }
}

void BalanceTree(AVL* avl)
{
    Node* temp;
    int done = 0;
    int balance;

    if(avl == NULL)
    {
        printf("BalanceTree: Null tree given.\n");
        return;
    }

    temp = avl->root;

    while( abs(CalcBalance(avl->root)) > 1)
    {
        balance = CalcBalance(temp);
        if(balance > 1)
        {
            if( abs(CalcBalance(temp->leftChild)) > 1)
            {
                temp = temp->leftChild;
                continue;
            }
            else if(CalcBalance(temp->leftChild) == -1)
            {
                RotateLeft(avl, temp->leftChild);
            }
            
            //Rotate and Reset Position
            RotateRight(avl, temp);
            temp = avl->root;
        }
        else
        {
            if( abs(CalcBalance(temp->rightChild)) > 1)
            {
                temp = temp->rightChild;
                continue;
            }
            else if(CalcBalance(temp->rightChild) == 1)
            {
                RotateRight(avl, temp->rightChild);
            }

            //Rotate and Reset Position
            RotateLeft(avl, temp);
            temp = avl->root;
        }
    }
}

void AVLInsertRec(AVL* avl, Node* parent, Node* node, int value)
{
    //Error Checking
    if(parent == NULL || value == 0)
    {
        printf("AVLInsertRec: Either NULL parent or 0 value given.\n");
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
        printf("AVLInsertRec: Root is %d\n", value);
        free(node);
        node = NULL;
    }
    else if(node->value > parent->value)
    {
        if(parent->rightChild)
        {
            AVLInsertRec(avl, parent->rightChild, node, value);
        }
        else
        {
            parent->rightChild = node;
            node->parent = parent;
            UpdateHeights(node);
            BalanceTree(avl);
        }
    }
    else if(node->value < parent->value)
    {
        if(parent->leftChild)
        {
            AVLInsertRec(avl, parent->leftChild, node, value);
        }
        else
        {
            parent->leftChild = node;
            node->parent = parent;
            UpdateHeights(node);
            BalanceTree(avl);
        }
    }
}

Node* AVLDeleteRec(AVL* avl, Node* node, int value)
{
    Node* temp;

    if(node == NULL || node->value == 0)
    {
        printf("AVLDeleteRec: Value not found: %d\n", value);
        return NULL;
    }
    
    if(node->value == value)
    {
        if(node->leftChild == NULL)
        {
            temp = node->rightChild;
            if(node == avl->root)
            {
                avl->root = temp;
            }
            free(node);
            node=NULL;
            return temp;
        }
        else if(node->rightChild == NULL)
        {
            temp = node->leftChild;
            if(node == avl->root)
            {
                avl->root = temp;
            }
            free(node);
            node=NULL;
            return temp;
        }
        temp = AVLFindMinRec(node->leftChild);
        node->value = temp->value;
        node->rightChild = AVLDeleteRec(avl, node->rightChild, node->value);
    } 
    else if(node->value > value)
    {
        node->leftChild = AVLDeleteRec(avl, node->leftChild, value);
    }
    else
    {
        node->rightChild = AVLDeleteRec(avl, node->rightChild, value);
    }
    return node;
}

/**
 * @brief Helper function for finding the next node by going up the AVL.
 * 
 * @param node  The node needing to be traversed.
 * @return Node* 
 */
Node* AVLTraverseUpNext(Node* node)
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
        return AVLTraverseUpNext(node->parent);
    }
    
}

Node* AVLFindNextRec(AVL* avl, Node* node)
{
    Node* parentNode;

    //Error Checking
    if(node == NULL || avl == NULL)
    {
        printf("AVLFindNextRec: avl or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further right.
    if(AVLFindMaxRec(avl->root) == node)
    {
        printf("AVLFindNextRec: Already at rightest node\n");
        return NULL;
    }
    
    //The next node is always the minimum value of the right subtree
    //or a right traversal up.
    if(node->rightChild)
    {
        return AVLFindMinRec(node->rightChild);
    }
    else if(node->parent)
    {
        return AVLTraverseUpNext(node);
    }
    else
    {
        return node;
    }
    
}

/**
 * @brief Helper function for finding the previous node by going up the AVL.
 * 
 * @param node The node needing to be traversed.
 * @return Node* 
 */
Node* AVLTraverseUpPrev(Node* node)
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
        return AVLTraverseUpPrev(node->parent);
    }
    
}

Node* AVLFindPrevRec(AVL* avl, Node* node)
{
    //Error Checking
    if(avl == NULL || node == NULL)
    {
        printf("AVLFindPrevRec: avl or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further left.
    if(AVLFindMinRec(avl->root) == node)
    {
        printf("AVLFindPrevRec: Already at leftest node\n");
        return NULL;
    }
    
    //The previous node is always the max of the left subtree
    //or a left traversal up.
    if(node->leftChild)
    {
        return AVLFindMaxRec(node->leftChild);
    }
    else if(node->parent)
    {
        return AVLTraverseUpPrev(node);
    }
    else
    {
        return node;
    }
    
}

Node* AVLFindMinRec(Node* node)
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
        return AVLFindMinRec(node->leftChild);
    }
}

Node* AVLFindMaxRec(Node* node)
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
        return AVLFindMaxRec(node->rightChild);
    }
    
}

void AVLInsertIter(AVL* avl, Node* root, Node* node, int value)
{
    Node* parent;
    int done = 0;
    parent = root;

    //Error Checking
    if(parent == NULL || value == 0)
    {
        printf("AVLInsertIter: Either NULL parent or 0 value given.\n");
        return;
    }

    //Assign root value
    if(parent->value == 0)
    {
        parent->value = value;
        printf("AVLInsertIter: Root is %d\n", value);
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
                    UpdateHeights(node);
                    BalanceTree(avl);
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
                    UpdateHeights(node);
                    BalanceTree(avl);
                    done = 1;
                }
            } else
            {
                printf("AVLInsertIter: Duplicate value given, did not insert value: %d\n", value);
                done = 1;
            }
            
        }
    }
    
}

Node* AVLDeleteIter(AVL* avl, Node* node, int value)
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
                    prev = AVLFindPrevIter(avl, node);
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
                    next = AVLFindNextIter(avl, node);
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
    printf("AVLDeleteIter: Value not found: %d\n", value);
    return NULL;
}

Node* AVLFindNextIter(AVL* avl, Node* node)
{
    Node* next;
    next = node;

    //Error Checking
    if(avl == NULL || node == NULL)
    {
        printf("AVLFindNextIter: avl or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further right.
    if(AVLFindMaxIter(avl->root) == node)
    {
        printf("AVLFindNextIter: Already at rightest node\n");
        return NULL;
    }

    //The next node is always the min of the right subtree.
    if(next->rightChild)
    {
        return AVLFindMinIter(next->rightChild);
    }

    //or a right traversal up.
    while(next->parent->value < next->value)
    {
        next = next->parent;
    }
    return next->parent;
}

Node* AVLFindPrevIter(AVL* avl, Node* node)
{
    Node* prev;
    prev = node;

    //Error Checking
    if(avl == NULL || node == NULL)
    {
        printf("AVLFindNextIter: avl or node given is null\n");
        return NULL;
    }

    //Check if we cannot go any further left.
    if(AVLFindMinIter(avl->root) == node)
    {
        printf("FindPrev: Already at leftest node\n");
        return NULL;
    }

    //The previous node is always the max of the left subtree.
    if(prev->leftChild)
    {
        return AVLFindMaxIter(prev->leftChild);
    }

    //or a left traversal up.
    while(prev->parent->value > prev->value)
    {
        prev = prev->parent;
    }
    return prev->parent;
}

Node* AVLFindMinIter(Node* node)
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

Node* AVLFindMaxIter(Node* node)
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

int bCumSum(int level)
{
    int i, sum;
    for(i = 0; i < level+1; i++)
    {
        sum += pow(2, i);
    }
    return sum;
}

char *AllocateSpace(int num)
{
    char* spaces;
    int i;

    spaces = malloc((num+1)*sizeof(char));

    memset(spaces, ' ', num*sizeof(char));
    spaces[num] = '\0';

    return spaces;
}

void AVLPrint(AVL* avl)
{
    Node* temp;
    Node* queue[AVL_MAX_SIZE] = {0};
    char *spaces;
    int i, size, spaceNum, nextEnter = 1;

    temp = avl->root;
    size = pow(2, avl->root->height+1);

    for(i = 1; i < size; i++)
    {
        spaceNum = (size-i)/2;
        spaces = AllocateSpace(spaceNum+1);

        if(temp == NULL)
        {
            printf("%s-%s", spaces, spaces);
            if(i == nextEnter)
            {
                printf("\n");
                nextEnter = pow(2, log2(i+1)+1)-1;
            }
            temp = queue[i+1];
            free(spaces);
            continue;
        }

        printf("%s%d%s", spaces, temp->value, spaces);

        if(temp->leftChild)
        {
            queue[i*2] = temp->leftChild;
            if(temp->rightChild)
            {
                queue[i*2+1] = temp->rightChild;
            }
        }
        else if(temp->rightChild)
        {
            queue[i*2+1] = temp->rightChild;
        }

        if(i == nextEnter)
        {
            printf("\n");
            nextEnter = pow(2, log2(i+1)+1)-1;
        }
        temp = queue[i+1];
        free(spaces);
    }
}