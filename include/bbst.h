#ifndef __BBST_H
#define __BBST_H

#include "node.h"

typedef struct _BBST BBST;

/**
 * @brief Balanced BST struct which is used to reference the Balanced BST and call it's functions.
 * 
 */
struct _BBST
{
    Node*       root;
    void        (*Insert)(Node* root, Node* node, int value);
    Node*       (*Delete)(BBST* bst, Node* node, int value);
    Node*       (*FindNext)(BBST* bst, Node* node);
    Node*       (*FindPrev)(BBST* bst, Node* node);
    Node*       (*FindMin)(Node* node);
    Node*       (*FindMax)(Node* node);
};

/**
 * @brief Allocates a Balanced BST using Recursive functions.
 * 
 * @return BST* 
 */
BBST* BBSTAllocateRec();

/**
 * @brief Allocates a Balanced BST using Iterative functions.
 * 
 * @return BST* 
 */
BBST* BBSTAllocateIter();


#endif