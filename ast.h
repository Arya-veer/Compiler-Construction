//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#ifndef AST_H
#define AST_H
#include "symbolTable.h"

void applyRule(TREENODE tn);
void traversal(TREENODE tn,SYMBOLTABLE SYMBOL_TABLE);
TYPE typeExtractionExpr(TREENODE expression_node,SYMBOLTABLE SYMBOL_TABLE);
void traversalForDeclaredFuncs(TREENODE node,SYMBOLTABLE SYMBOL_TABLE);
void printASTNODE(TREENODE node);
void printAST(TREENODE root);
SYMBOLTABLE GST;
SYMBOLTABLEROW currFunc;
#endif