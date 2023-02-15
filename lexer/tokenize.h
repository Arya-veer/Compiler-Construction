#ifndef LEXER_TOKENIZER_H
#define LEXER_TOKENIZER_H

#include"../utils/tokens/tokens.h"
#include"../utils/Buffer/buffer.h"

    char* tokens[] = {
        "integer",
        "real",
        "boolean",
        "of",
        "array",
        "start",
        "end",
        "declare",
        "module",
        "driver",
        "program",
        "get_value",
        "print",
        "use",
        "with",
        "parameters",
        "takes",
        "input",
        "returns",
        "for",
        "in",
        "switch",
        "case",
        "break",
        "default",
        "while",
        "AND",
        "OR",
        "true",
        "false",
        "+",
        "-",
        "*",
        "/",
        "<",
        "<=",
        ">=",
        ">",
        "==",
        "!=",
        "<<",
        ">>",
        "<<<",
        ">>>",
        ":",
        "..",
        ";",
        ",",
        ":=",
        "[",
        "]",
        "(",
        ")",
        "**"
    };

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