#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

STACK createStack(){
    STACK st = (STACK) malloc(sizeof(struct Stack));
    st -> top = NULL;
    st -> size = 0;
    return st; 
}

void pushInStack(STACK st,LISTNODE node,TREENODE tn,short pushChild){
    if(node == NULL) return;
    STACKNODE newTop = (STACKNODE) malloc(sizeof(struct StackNode));
    TREENODE treenode;
    if(pushChild == 1){
        treenode = insertChildTree(tn,node);
    }
    else{
        treenode = insertNextTree(tn,node);
    }
    newTop -> next = NULL;
    newTop -> NODETYPE = node -> NODETYPE;
    newTop -> isTerminal = node -> isTerminal;
    pushInStack(st,node->next,treenode,0);
    newTop -> treenode = treenode;
    newTop -> next = st -> top;
    st -> top = newTop;
    ++st -> size;
}

short isStackEmpty(STACK st){
    return st->size == 0;
}

STACKNODE popFromStack(STACK st){
    if(isStackEmpty(st)){
        printf("Stack Underflow\n");
        return NULL;
    }
    STACKNODE currTop = st->top;
    st->top = currTop->next;
    currTop->next = NULL;
    st->size --;
    return currTop;
}

























































