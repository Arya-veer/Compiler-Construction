#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
// #include "../../utils/tokens/tokens.c"
// #include "../../utils/terminals/terminals.c"
// #include "../../utils/nonTerminals/nonTerminals.c"

STACK createStack(){
    // printf("fjsdoilaf\n");
    STACK st = (STACK) malloc(sizeof(struct Stack));
    // printf("fksdhjlf\n");
    st -> top = NULL;
    st -> size = 0;
    return st; 
}

void pushInStack(STACK st,LISTNODE node){
    if(node == NULL) return;
    // printf("%d\n")
    STACKNODE newTop = (STACKNODE) malloc(sizeof(struct StackNode));
    newTop -> next = NULL;
    newTop -> NODETYPE = node -> NODETYPE;
    newTop -> isTerminal = node -> isTerminal;
    pushInStack(st,node->next);
    newTop -> next = st -> top;
    st -> top = newTop;
    ++st -> size;
    // if(newTop->isTerminal == 0) printf("PUSHED IN STACK %d , isTerminal %d\n",newTop->NODETYPE->nonterminal,newTop->isTerminal);
    // if(newTop->isTerminal == 1) printf("PUSHED IN STACK %d , isTerminal %d\n",newTop->NODETYPE->terminal,newTop->isTerminal);
    // if(newTop->isTerminal == -1) printf("PUSHED IN STACK EPISLON\n");

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
    // if(st->top->isTerminal == 0) printf("POPPPED FROM STACK %d, isTerminal %d\n",st->top->NODETYPE->nonterminal)
    return currTop;
}

























































