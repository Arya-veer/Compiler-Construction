#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

LINKEDLIST createLinkedList(){
    LINKEDLIST ll = (LINKEDLIST) malloc(sizeof(struct LinkedList));
    ll->head = NULL;
    ll->size = 0;
    return ll;
}


void insertionInLinkedList(LINKEDLIST ll, short isTerminal, short ndtype, short ruleNum ){
    // printf("Inserting in Linked List\n");
    if(isTerminal == -1) return;
    if(ndtype == -1) isTerminal = -1;
    LISTNODE lstNode = (LISTNODE) malloc(sizeof(struct ListNode));
    lstNode -> NODETYPE = (union NodeType*) malloc(sizeof(union NodeType)); 
    ll->size++;
    lstNode -> next = NULL;
    LISTNODE curr = ll->head;
    if(curr == NULL){
        ll -> head = lstNode;
    }
    else{
        while(curr -> next != NULL){
            curr = curr->next;
        }
        curr->next = lstNode;
    }
    lstNode->ruleNum = ruleNum;
    lstNode->isTerminal = isTerminal;
    // printf("Now assigning value to NODETYPE\n");
    if(isTerminal == 1){
        lstNode -> NODETYPE -> terminal = (TOKENS)ndtype;
    }
    else{
        lstNode -> NODETYPE -> nonterminal = (NONTERMINALS)ndtype;
    }
}