#ifndef __NODE_H
#define __NODE_H

typedef struct _Node Node;

/**
 * @brief Node structure for a BST/AVL
 * 
 */
struct _Node
{
    Node*       parent;
    Node*       leftChild;
    Node*       rightChild;
    int         value;
    int         height; 
};

#endif