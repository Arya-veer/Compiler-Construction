//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#ifndef SYMTABDEF_H
#define SYMTABDEF_H

#include "parserDef.h"

typedef struct SymbolTable* SYMBOLTABLE;
typedef struct SymTabRowNode* SYMBOLTABLEROW;
typedef struct arrRange* ARRRANGE;

struct arrRange{
    TREENODE left;
    TREENODE right;
    char* leftSign;
    char* rightSign;
    int leftVal;
    int rightVal;
};


struct SymTabRowNode{
    ARRRANGE range;
    short isDynamic;
    LEXEME* id;
    TYPE type;
    int offset;
    SYMBOLTABLE SYMBOLTABLE;
    SYMBOLTABLEROW next;
    SYMBOLTABLEROW INPUTPARAMSHEAD;
    SYMBOLTABLEROW OUTPUTPARAMSHEAD;
}; 



struct SymbolTable{
    SYMBOLTABLEROW* TABLE;
    int currOffset;
    char* name;
    SYMBOLTABLE next;
    SYMBOLTABLE parent;
    int first;
    int last;
};

#endif