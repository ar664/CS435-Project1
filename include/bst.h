#ifndef __BST_H
#define __BST_H

#include "node.h"

typedef struct _BST BST;

/**
 * @brief BST struct which is used to reference the BST and call it's functions.
 * 
 */
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

/**
 * @brief Allocates a BST using Recursive functions.
 * 
 * @return BST* 
 */
BST* BSTAllocateRec();

/**
 * @brief Allocates a BST using Iterative functions.
 * 
 * @return BST* 
 */
BST* BSTAllocateIter();


#endif