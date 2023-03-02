
#ifndef PARSETREE_H
#define PARSETREE_H

#include "./lexer.h"
#include "linkedList.h"

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
TREENODE insertChildTree(TREENODE tn, LISTNODE ln);
TREENODE insertNextTree(TREENODE tn, LISTNODE ln);
TREENODE createRootNode(LISTNODE ln);
void inorderTraversal(TREENODE tn,short goNext, FILE* outputFile);

#endif
