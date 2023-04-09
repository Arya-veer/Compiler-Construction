#ifndef SYMTAB_H
#define SYMTAB_H
#include "symbolTableDef.h"

SYMBOLTABLE initializeSymbolTable(char* name,int first,int last);
SYMBOLTABLEROW StoreVarAsInputParam(SYMBOLTABLEROW IP,TREENODE var);
SYMBOLTABLEROW StoreVarAsOutputParam(SYMBOLTABLEROW OP,TREENODE var);
SYMBOLTABLEROW StoreVarIntoSymbolTable(SYMBOLTABLE SYMBOLTABLE,TREENODE var,TREENODE range);
SYMBOLTABLEROW StoreFuncIntoSymbolTable(SYMBOLTABLE SYMBOLTABLE,TREENODE func);
SYMBOLTABLEROW GetVarFromSymbolTable(SYMBOLTABLE SYMBOLTABLE,TREENODE var);
SYMBOLTABLEROW GetFuncFromSymbolTable(SYMBOLTABLE SYMBOLTABLE,TREENODE func);
void printSymbolTable(SYMBOLTABLEROW func);
void printTable(SYMBOLTABLE SYMBOL_TABLE);
SYMBOLTABLEROW StoreForIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE FOR);
SYMBOLTABLEROW StoreWhileIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE WHILE);
SYMBOLTABLEROW StoreSwitchIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE SWITCH);
SYMBOLTABLEROW StoreCaseIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE CASE);
SYMBOLTABLEROW GetForFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE FOR);
SYMBOLTABLEROW GetWhileFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE WHILE);
SYMBOLTABLEROW GetSwitchFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE SWITCH);
SYMBOLTABLEROW GetCaseFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE CASE);
SYMBOLTABLEROW copy(SYMBOLTABLEROW old_row);
void printFullTable(SYMBOLTABLE ST);

#endif