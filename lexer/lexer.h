
#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include"../utils/tokens/tokens.h"
#include "../utils/Buffer/buffer.h"
#include "../utils/errors/errors.h"

union lexemeData{
    char *data;
    int intData;
    float floatData;
};

typedef struct lexeme LEXEME;
struct lexeme{
    TOKENS token;
    short int lineNo;
    union lexemeData *lexemedata;
};

LEXEME* tokenize(TwinBuffer *TB,short int line);
LEXEME* tokenizeEOF(TwinBuffer *TB);
LEXEME* simulateDFA(TwinBuffer *TB);

#endif