#ifndef PARSER_DATASTRUCTURES_STACK_H
#define PARSER_DATASTRUCTURES_STACK_H
#include "../../utils/tokens/tokens.h"
#include "../../utils/nonTerminals/nonTerminals.h"


union NodeType {
    TOKENS terminal;
    NONTERMINALS nonterminal;
};

typedef struct StackNode* STACKNODE;
struct StackNode {
    STACKNODE next;
    union NodeType* NODETYPE;
    int isTerminal;
};


typedef struct ListNode* LISTNODE;
struct ListNode {
    int ruleNum;
    LISTNODE next;
    union NodeType* NODETYPE;
    int isTerminal;
};


typedef struct Stack* STACK;

struct Stack {
    STACKNODE top;
    int size;
};

#endif


