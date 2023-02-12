#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include"../utils/tokens/tokens.h"
#include"../utils/readFile/readFile.h"

typedef struct lexeme LEXEME;
struct lexeme{
    TOKENS token;
    int lineNo;
    union lexemeData{
        char data[20];
        int intData;
        float floatData;
    };
};

#endif