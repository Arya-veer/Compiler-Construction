#ifndef SYMTABDEF_H
#define SYMTABDEF_H

#include "parserDef.h"

typedef struct SymTabRowNode* SYMBOLTABLEROW;
typedef struct arrRange* ARRRANGE;

struct arrRange{
    int left;
    int right;
};


struct SymTabRowNode{
    ARRRANGE range;
    LEXEME* id;
    TYPE type;
    int offset; // TODO: Assign Offsets
    short isArray;
    SYMBOLTABLEROW* SYMBOLTABLE;
    SYMBOLTABLEROW next;
    SYMBOLTABLEROW* INPUTPARAMS;
    SYMBOLTABLEROW* OUTPUTPARAMS;
}; 

#endif