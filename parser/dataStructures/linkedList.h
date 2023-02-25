#ifndef PARSER_DATASTRUCTURES_LINKEDLIST_H
#define PARSER_DATASTRUCTURES_LINKEDLIST_H

#include "stack.h"

typedef struct LinkedList* LINKEDLIST;

struct LinkedList{
    int size;
    LISTNODE head;
};

LINKEDLIST createLinkedList();
void insertionInLinkedList(LINKEDLIST ll, int isTerminal, int ndtype, int ruleNum);

#endif
