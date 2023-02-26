#ifndef PARSER_DATASTRUCTURES_LINKEDLIST_H
#define PARSER_DATASTRUCTURES_LINKEDLIST_H


#include "../../utils/tokens/tokens.h"
#include "../../utils/nonTerminals/nonTerminals.h"

union NodeType {
    TOKENS terminal;
    NONTERMINALS nonterminal;
};


typedef struct ListNode* LISTNODE;
struct ListNode {
    int ruleNum;
    LISTNODE next;
    union NodeType* NODETYPE;
    int isTerminal;
};

typedef struct LinkedList* LINKEDLIST;

struct LinkedList{
    int size;
    LISTNODE head;
};

LINKEDLIST createLinkedList();
void insertionInLinkedList(LINKEDLIST ll, int isTerminal, int ndtype, int ruleNum);

#endif
