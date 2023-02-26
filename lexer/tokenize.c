#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"
// #include "../utils/tokens/tokens.c"

short isFloat(char* number){
    short n = strlen(number);
    for(short i=0;i<n;i++){
        if(number[i] == '.'){
            return 1;
        }
    }
    return 0;
}
/* @param 
    TWINBUFFER TB;
    int line;
    TODO: Handle comments

 */

LEXEME* tokenizeEOF(TwinBuffer *TB){
    char* input = extractLexeme(TB);
    LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    lex -> token = EOF_TOKEN;
    printf("Tokenized %s , sending it for parsing\n","EOF");
    return lex;
}

LEXEME* tokenize(TwinBuffer *TB,short int line){
    char* input = extractLexeme(TB);
    // printf("tokenize got the input as %s\n",input);
    if(input[0] == ' ' || input[0] == '\n' || input[0] == '\t' || input[0] == EOF) return NULL; // If a white space is there do not tokenize it
    LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    lex->lexemedata = (union lexemeData*) malloc(sizeof(union lexemeData));
    lex->lineNo = line;
    /* Checking For Int or Float */
    if(input[0] >= '0' && input[0] <= '9'){
        if(isFloat(input)){
            lex->lexemedata->floatData = atof(input);
            lex->token = RNUM_TOKEN;

            // printf("Printing as float => %f\n",lex->lexemedata->floatData);
        }
        else{
            lex->lexemedata->intData = atoi(input);
            lex->token = NUM_TOKEN;
            // printf("Printing as integer => %d\n",lex->lexemedata->intData);
        }
        return lex;
    }
    lex->lexemedata->data = input;
    short found = 0;
    // printf("Checking for keywords\n");
    /* Checking For Keywords */
    for(short int i=0;i <= 52;i++){
        // printf("Are they equal %d\n",strcmp(input,TOKENS_STRING[i]));
        if(strcmp(input,TOKENS_STRING[i]) == 0){
            lex->token = (TOKENS) i;
            found = 1;
            break;
        }
    } 

    if(found == 0) lex->token = IDENTIFIER_TOKEN;
    // printf("Tokenized %s , sending it for parsing\n",TOKENS_STRING[(int) lex->token]);
    return lex;
}

