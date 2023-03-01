
#include<stdio.h>
#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#define SIZE 128
#define LEXEME_SIZE 32
#include "../constants/constants.h"

typedef struct twinBuffer TwinBuffer;
typedef char SingleBuffer[SIZE];
char ReturnLexeme[LEXEME_SIZE];
struct twinBuffer{
    
    /* Buffers
    */
    SingleBuffer buffer[2];
    /* Begin Pointer
    */
    short lexemeBegin;
    /* Begin Pointer
    */
    short forward;
    /* Current Buffer
    */
    short currentLexemeBegin;

    short currentForward;
    /* Filename
    */
    FILE* fp;
};


union lexemeData{
    char *data;
    int intData;
    double floatData;
};

typedef struct lexeme LEXEME;
struct lexeme{
    TOKENS token;
    short int lineNo;
    union lexemeData *lexemedata;
};

TwinBuffer* initializeTwinBuffer(char* fname);
LEXEME* simulateDFA(TwinBuffer *TB,short toPrint);

#endif