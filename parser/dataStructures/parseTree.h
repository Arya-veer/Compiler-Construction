#ifndef PARSER_DATASTRUCTURES_PARSETREE_H
#define PARSER_DATASTRUCTURES_PARSETREE_H
#include "../../lexer/lexer.h"
#include "stack.h"

typedef struct TreeNode* TREENODE;
struct TreeNode{
    TREENODE child;
    TREENODE next;
    LEXEME terminal;
    int isTerminal;
};




#endif

