
#ifndef STACK_H
#define STACK_H


#include "./parserDef.h"
#include "linkedList.h"


typedef struct StackNode* STACKNODE;
struct StackNode {
    STACKNODE next;
    union NodeType* NODETYPE;
    short isTerminal;
    TREENODE treenode;
};



typedef struct Stack* STACK;

struct Stack {
    STACKNODE top;
    short size;
};

STACK createStack();
void pushInStack(STACK st,LISTNODE node,TREENODE tn,short pushChild);
short isStackEmpty(STACK st);
STACKNODE popFromStack(STACK st);

#endif

