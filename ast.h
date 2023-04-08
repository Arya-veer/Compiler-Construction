#ifndef AST_H
#define AST_H
#include "symbolTable.h"

void applyRule(TREENODE tn);
void traversal(TREENODE tn,SYMBOLTABLE SYMBOL_TABLE);
TYPE typeExtractionExpr(TREENODE expression_node,SYMBOLTABLE SYMBOL_TABLE);
SYMBOLTABLE GST;
SYMBOLTABLEROW currFunc;
#endif