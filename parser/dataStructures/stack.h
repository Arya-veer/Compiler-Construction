
#ifndef PARSER_DATASTRUCTURES_STACK_H
#define PARSER_DATASTRUCTURES_STACK_H


#include "parseTree.h"
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


