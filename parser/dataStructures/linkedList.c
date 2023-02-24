#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

LINKEDLIST createLinkedList(){
    LINKEDLIST ll = (LINKEDLIST) malloc(sizeof(struct LinkedList));
    ll->head = NULL;
    ll->size = 0;
    return ll;
}


void insertionInLinkedList(LINKEDLIST ll, int isTerminal, int ndtype, int ruleNum ){
    LISTNODE lstNode = (LISTNODE) malloc(sizeof(struct ListNode));
    ll->size++;
    lstNode -> next = NULL;
    LISTNODE curr = ll->head;
    if(curr == NULL){
        ll -> head = lstNode;
    }
    else{
        while(curr -> next!=NULL){
            curr = curr->next;
        }
        curr->next = lstNode;
    }
    lstNode->ruleNum = ruleNum;
    lstNode->isTerminal = isTerminal;
    if(isTerminal == 1){
        lstNode -> NODETYPE -> terminal = (TOKENS)ndtype;
    }
    else{
        lstNode -> NODETYPE -> nonterminal = (NONTERMINALS)ndtype;
    }
}