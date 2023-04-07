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
    ARRRANGE range; // TODO: Dynamic or Static
    LEXEME* id;
    TYPE type;
    int offset; // TODO: Assign Offsets
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