#ifndef __BST_H
#define __BST_H

#include "node.h"

typedef enum
{
    LEFT    =   -1,
    UP      =    0,
    RIGHT   =    1
}Dir;

typedef struct _BST BST;

struct _BST
{
    Node*       root;
    int         direction;
    void        (*Insert)(Node* root, Node* node, int value);
    Node*       (*Delete)(BST* bst, Node* node, int value);
    Node*       (*FindNext)(Node* node);
    Node*       (*FindPrev)(Node* node);
    Node*       (*FindMin)(Node* node);
    Node*       (*FindMax)(Node* node);
};

void InsertRec(Node* parent, Node* node, int value);
Node* DeleteRec(BST* bst, Node* node, int value);
Node* FindNextRec(Node* node);
Node* FindPrevRec(Node* node);
Node* FindMinRec(Node* node);
Node* FindMaxRec(Node* node);

void InsertIter(Node* root, Node* node, int value);
Node* DeleteIter(BST* bst, Node* node, int value);
Node* FindNextIter(Node* node);
Node* FindPrevIter(Node* node);
Node* FindMinIter(Node* node);
Node* FindMaxIter(Node* node);

BST* BSTAllocateRec();
BST* BSTAllocateIter();


#endif