#ifndef AST_H
#define AST_H
#include "symbolTable.h"

void applyRule(TREENODE tn);
void traversal(TREENODE tn,SYMBOLTABLEROW* SYMBOLTABLE);
SYMBOLTABLEROW* GST;
SYMBOLTABLEROW currFunc;
#endif