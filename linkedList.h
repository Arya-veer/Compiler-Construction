#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "./lexer.h"



union NodeType {
    TOKENS terminal;
    NONTERMINALS nonterminal;
};


typedef struct ListNode* LISTNODE;
struct ListNode {
    short ruleNum;
    LISTNODE next;
    union NodeType* NODETYPE;
    short isTerminal;
};

typedef struct LinkedList* LINKEDLIST;

struct LinkedList{
    short size;
    LISTNODE head;
};

LINKEDLIST createLinkedList();
void insertionInLinkedList(LINKEDLIST ll, short isTerminal, short ndtype, short ruleNum);

#endif