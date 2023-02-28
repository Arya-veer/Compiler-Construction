
#include<stdio.h>
#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#define SIZE 128
#define LEXEME_SIZE 32

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
// #include"../utils/tokens/tokens.h"
// #include "../utils/Buffer/buffer.h"
// #include "../utils/errors/errors.h"

typedef enum  {
        INTEGER_TYPE,
        REAL_TYPE,
        BOOLEAN_TYPE,
        OF_KEYWORD,
        ARRAY_KEYWORD,
        START_KEYWORD,
        END_KEYWORD,
        DECLARE_KEYWORD,
        MODULE_KEYWORD,
        DRIVER_KEYWORD,
        PROGRAM_KEYWORD,
        GET_VALUE_KEYWORD,
        PRINT_FUNCTION,
        USE_KEYWORD,
        WITH_KEYWORD,
        PARAMETERS_KEYWORD,
        TAKES_KEYWORD,
        INPUT_KEYWORD,
        RETURNS_KEYWORD,
        FOR_KEYWORD,
        IN_KEYWORD,
        SWITCH_KEYWORD,
        CASE_KEYWORD,
        BREAK_KEYWORD,
        DEFAULT_KEYWORD,
        WHILE_KEYWORD,
        AND_OPERATOR,
        OR_OPERATOR,
        TRUE_BOOL,
        FALSE_BOOL,
        PLUS_OPERATOR,
        MINUS_OPERATOR,
        MUL_OPERATOR,
        DIV_OPERATOR,
        LT_OPERATOR,
        LE_OPERATOR,
        GE_OPERATOR,
        GT_OPERATOR,
        EQ_OPERATOR,
        NE_OPERATOR,
        DEF_OPERATOR,
        ENDDEF_OPERATOR,
        DRIVERDEF_OPERATOR,
        DRIVERENDDEF_OPERATOR,
        COLON_OPERATOR,
        RANGEOP_OPERATOR,
        SEMICOL_OPERATOR,
        COMMA_OPERATOR,
        ASSIGNOP_OPERATOR,
        SQBO_TOKEN,
        SQBC_TOKEN,
        BO_TOKEN,
        BC_TOKEN,
        EOF_TOKEN,
        IDENTIFIER_TOKEN,
        NUM_TOKEN,
        RNUM_TOKEN
    } TOKENS;

     char* TOKENS_STRING[54];


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

// void populateTwinBuffer(TwinBuffer *TB);

// LEXEME* tokenize(TwinBuffer *TB,short int line);
// LEXEME* tokenizeEOF(TwinBuffer *TB);
TwinBuffer* initializeTwinBuffer(char* fname);
LEXEME* simulateDFA(TwinBuffer *TB);

#endif