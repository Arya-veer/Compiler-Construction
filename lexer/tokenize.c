#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"

int isFloat(char* number){
    int n = strlen(number);
    for(int i=0;i<n;i++){
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
void tokenize(TwinBuffer *TB,int line){
    char* input = extractLexeme(TB);
    // printf("tokenize got the input as %s\n",input);
    if(input[0] == ' ' || input[0] == '\n' || input[0] == '\t' || input[0] == EOF) return; // If a white space is there do not tokenize it
    LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    lex->lexemedata = (union lexemeData*) malloc(sizeof(union lexemeData));
    lex->lineNo = line;
    /* Checking For Int or Float */
    if(input[0] >= '0' && input[0] <= '9'){
        if(isFloat(input)){
            lex->lexemedata->floatData = atof(input);
            // printf("Printing as float => %f\n",lex->lexemedata->floatData);
        }
        else{
            lex->lexemedata->intData = atoi(input);
            // printf("Printing as integer => %d\n",lex->lexemedata->intData);
        }
        return;
    }
    lex->lexemedata->data = input;
    int found = 0;
    /* Checking For Keywords */
    for(int i=0;i <= 53;i++){
        // printf("Are they equal %d\n",strcmp(input,TOKENS_STRING[i]));
        if(strcmp(input,TOKENS_STRING[i]) == 0){
            lex->token = (TOKENS) i;
            found = 1;
            break;
        }
    } 

    if(found == 0) lex->token = IDENTIFIER_TOKEN;
    printf("Tokenized %d , sending it for parsing\n",(int) lex->token);
    return;
}

