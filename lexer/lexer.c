#include<stdio.h>
#include<stdlib.h>
// #include<stdbool.h>
#include "lexer.h"


void tokenizer(TwinBuffer TB,LEXEME lex,int type){
    // char* input = incrementLexemeBegin(TB);
}


void simulateDFA(TwinBuffer TB){
    char* error;
    int state = 0;
    char c;
    int lineCount = 0;
    char* currBuff;
    while(1){
        // currBuff = TB.currentBuffer?TB.buffFirst:TB.buffSecond;
        switch(state){
            case -1:
                error = "Lexical Error Occured";
                break;
            case 0:
                printf("START STATE\n");
                // TB.lexemeBegin = TB.forward;
                c = getCharacterAtForward(TB);
                if(c == '+')       state = 1;
                else if (c == '-') state = 2;
                else if (c == '/') state = 3;
                else if (c == ';') state = 4;
                else if (c == ',') state = 5;
                else if (c == '[') state = 6;
                else if (c == ']') state = 7;
                else if (c == '(') state = 8;
                else if (c == ')') state = 9;
                else if (c == '!') state = 10;
                else if (c == '=') state = 12;
                else if (c == '.') state = 14;
                else if (c == '*') state = 16;
                else if (c == ':') state = 20;
                else if (c >= '0' && c <= '9') state = 22;
                else if ((c >= 'a' && c >= 'z') || (c >='A' && c >= 'Z') || (c == '_')) state = 28;
                else if (c == '>') state = 29;
                else if (c == '<') state = 33;
                else if (c == ' ') state = 37;
                else if (c == '\t') state = 38;
                else if (c == '\n') state = 39;
                else if (c == EOF) state = 40;
                else state = -1;
                break;
            
            case 1:
                printf("STATE 1\n");
                incrementForward(TB);
                printf("TOKENIZE TK_PLUS\n");
                state = 0;
                break;
            case 2:
                printf("STATE 2\n");
                incrementForward(TB);
                printf("TOKENIZE TK_MINUS\n");
                state = 0;
                break;
            case 3:
                printf("STATE 3\n");
                incrementForward(TB);
                printf("TOKENIZE TK_DIV\n");
                state = 0;
                break;
            case 4:
                printf("STATE 4\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SEMICOL\n");
                state = 0;
                break;
            case 5:
                printf("STATE 5\n");
                incrementForward(TB);
                printf("TOKENIZE TK_COMMA\n");
                state = 0;
                break;
            case 6:
                printf("STATE 6\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SQBO\n");
                state = 0;
                break;
            case 7:
                printf("STATE 7\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SQBC\n");
                state = 0;
                break;
            case 8:
                printf("STATE 8\n");
                incrementForward(TB);
                printf("TOKENIZE TK_BO\n");
                state = 0;
                break;
            case 9:
                printf("STATE 9\n");
                incrementForward(TB);
                printf("TOKENIZE TK_BC\n");
                state = 0;
                break;
            case 10:
                printf("STATE 10\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 11;
                else state = -1;
                break;
            case 11:
                printf("STATE 11\n");
                incrementForward(TB);
                printf("TOKENIZE TK_NE\n");
                state = 0;
                break;
            case 12:
                printf("STATE 12\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 13;
                else state = -1;
                break;
            case 13:
                printf("STATE 13\n");
                incrementForward(TB);
                printf("TOKENIZE TK_EQ\n");
                state = 0;
                break;
            case 14:
                printf("STATE 14\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '.') state = 15;
                else state = -1;
                break;
            case 15:
                printf("STATE 15\n");
                incrementForward(TB);
                printf("TOKENIZE TK_RANGEOP\n");
                state = 0;
                break;
            case 16:
                printf("STATE 16\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 17;
                else{
                    printf("TOKENIZE TK_MUL\n");
                    state = 0;
                }
                break;
            case 17:
                printf("STATE 17\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 18;
                else state = 17;
                break;
            case 18:
                printf("STATE 18\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 19;
                else state = 17;
                break;
            case 19:
                printf("STATE 19\n");
                incrementForward(TB);
                printf("TOKENIZE TK_COMMENTMARK\n");
                state = 0;
                break;
            case 20:
                printf("STATE 20\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 21;
                else{
                    printf("TOKENIZE TK_COLON\n");
                    state = 0;
                }
                break;
            case 21:
                printf("STATE 21\n");
                incrementForward(TB);
                printf("TOKENIZE TK_ASSIGNOP\n");
                state = 0;
                break;
            case 22:
                printf("STATE 22\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '.') state = 23;
                else if(c >= '0' && c <= '9') state = 22;
                else{
                    printf("TOKENIZE TK_NUM\n");
                    state = 0;
                    break;
                }
            case 23:
                printf("STATE 23\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if(c == '.'){
                    //decreament forward
                }
        }
    }
}