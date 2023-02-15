#ifndef LEXER_TOKENIZER_H
#define LEXER_TOKENIZER_H

#include"../utils/tokens/tokens.h"
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

#endif