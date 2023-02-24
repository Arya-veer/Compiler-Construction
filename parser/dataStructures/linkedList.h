#ifndef PARSER_DATASTRUCTURES_LINKEDLIST_H
#define PARSER_DATASTRUCTURES_LINKEDLIST_H

#include "stack.h"

typedef struct LinkedList* LINKEDLIST;

struct LinkedList{
    int size;
    LISTNODE head;
};

#endif
