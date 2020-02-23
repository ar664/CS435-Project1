#ifndef __BST_H
#define __BST_H

#include "node.h"

typedef struct _BST BST;

struct _BST
{
    Node*       root;
    Node*       currentNode;
    void        (*Insert)(Node* node, int value);
    void        (*Delete)(Node* node, int value);
    void        (*FindNext)(Node* node);
    void        (*FindPrev)(Node* node);
    void        (*FindMin)(Node* node);
    void        (*FindMax)(Node* node);
};

#define BST_MAX_NODES 1000
static Node nodeList[BST_MAX_NODES] = {0};

void InsertRec(Node* node, int value);
void DeleteRec(Node* node, int value);
void FindNextRec(Node* node);
void FindPrevRec(Node* node);
void FindMinRec(Node* node);
void FindMaxRec(Node* node);

void InsertIter(Node* node, int value);
void DeleteIter(Node* node, int value);
void FindNextIter(Node* node);
void FindPrevIter(Node* node);
void FindMinIter(Node* node);
void FindMaxIter(Node* node);

BST* BSTAllocateRec();
BST* BSTAllocateIter();




#endif