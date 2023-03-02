#include<stdio.h>
#ifndef LEXERDEF_H
#define LEXERDEF_H
#define LEXEME_SIZE 32

#include "./constants.h"

typedef struct twinBuffer TwinBuffer;
typedef char* SingleBuffer;
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

    int SIZE;
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
#endif