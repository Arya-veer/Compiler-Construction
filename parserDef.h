#include<stdio.h>
#ifndef PARSERDEF_H
#define PARSERDEF_H
#define LEXEME_SIZE 32

#include "lexerDef.h"

/* LINKED LIST STRUCTURES*/
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


/*TREENODE STRUCTURE*/
typedef struct TreeNode* TREENODE;

union TreeNodeData{
    LEXEME* terminal;
    NONTERMINALS nonterminal;
};

struct TreeNode{
    TREENODE child;
    TREENODE next;
    TREENODE parent;
    union TreeNodeData* TREENODEDATA;
    short isTerminal;
};

/*STACK STRUCTURE*/
typedef struct StackNode* STACKNODE;
struct StackNode {
    STACKNODE next;
    union NodeType* NODETYPE;
    short isTerminal;
    TREENODE treenode;
};



typedef struct Stack* STACK;

struct Stack {
    STACKNODE top;
    short size;
};



#endif