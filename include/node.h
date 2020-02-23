#ifndef __NODE_H
#define __NODE_H

typedef struct _Node Node;

struct _Node
{
    Node*       parent;
    Node*       leftChild;
    Node*       rightChild;
    int         value;
};

#endif