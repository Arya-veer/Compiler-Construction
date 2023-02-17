#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#include"../utils/tokens/tokens.c"
#include"../utils/Buffer/buffer.h"

union lexemeData{
        char *data;
        int intData;
        float floatData;
    };

    typedef struct lexeme LEXEME;
    struct lexeme{
        TOKENS token;
        int lineNo;
        union lexemeData *lexemedata;
    };

void tokenize(TwinBuffer *TB,int line);
void simulateDFA(TwinBuffer *TB);

#endif