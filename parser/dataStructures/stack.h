
#ifndef PARSER_DATASTRUCTURES_STACK_H
#define PARSER_DATASTRUCTURES_STACK_H


#include "parseTree.h"
#include "linkedList.h"


typedef struct StackNode* STACKNODE;
struct StackNode {
    STACKNODE next;
    union NodeType* NODETYPE;
    int isTerminal;
    TREENODE treenode;
};



typedef struct Stack* STACK;

struct Stack {
    STACKNODE top;
    int size;
};

STACK createStack();
void pushInStack(STACK st,LISTNODE node);
int isStackEmpty(STACK st);
STACKNODE popFromStack(STACK st);

#endif


