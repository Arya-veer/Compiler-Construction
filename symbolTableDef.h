#ifndef SYMTABDEF_H
#define SYMTABDEF_H

#include "parserDef.h"

typedef struct SymbolTable* SYMBOLTABLE;
typedef struct SymTabRowNode* SYMBOLTABLEROW;
typedef struct arrRange* ARRRANGE;

struct arrRange{
    int left;
    int right;
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
};

#endif