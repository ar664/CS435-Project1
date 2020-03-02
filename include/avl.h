#ifndef __AVL_H
#define __AVL_H

#include "node.h"

typedef struct _AVL AVL;

/**
 * @brief Balanced BST struct which is used to reference the Balanced BST and call it's functions.
 * 
 */
struct _AVL
{
    Node*       root;
    void        (*Insert)(AVL* avl, Node* root, Node* node, int value);
    Node*       (*Delete)(AVL* avl, Node* node, int value);
    Node*       (*FindNext)(AVL* avl, Node* node);
    Node*       (*FindPrev)(AVL* avl, Node* node);
    Node*       (*FindMin)(Node* node);
    Node*       (*FindMax)(Node* node);
};

#define AVL_MAX_SIZE 12000

/**
 * @brief Allocates a Balanced BST using Recursive functions.
 * 
 * @return BST* 
 */
AVL* AVLAllocateRec();

/**
 * @brief Allocates a Balanced BST using Iterative functions.
 * 
 * @return BST* 
 */
AVL* AVLAllocateIter();

void AVLPrint(AVL* avl);


#endif