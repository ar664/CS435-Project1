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
    void        (*Insert)(Node* root, Node* node, int value);
    Node*       (*Delete)(BST* bst, Node* node, int value);
    Node*       (*FindNext)(BST* bst, Node* node);
    Node*       (*FindPrev)(BST* bst, Node* node);
    Node*       (*FindMin)(Node* node);
    Node*       (*FindMax)(Node* node);
};

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

BST* BSTAllocateRec();
BST* BSTAllocateIter();


#endif