#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

STACK createStack(){
    STACK st = (STACK) malloc(sizeof(struct Stack));
    st -> top = NULL;
    st -> size = 0;
    return st; 
}

void pushInStack(STACK st,LISTNODE node){
    if(node == NULL) return;
    STACKNODE newTop = (STACKNODE) malloc(sizeof(struct StackNode));
    newTop -> next = NULL;
    newTop -> NODETYPE = node -> NODETYPE;
    newTop -> isTerminal = node -> isTerminal;
    pushInStack(st,node->next);
    newTop -> next = st -> top;
    st -> top = newTop;
    ++st -> size;
}

int isStackEmpty(STACK st){
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

























































