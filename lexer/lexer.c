#include<stdio.h>
#include<stdlib.h>
// #include<stdbool.h>
#include "lexer.h"

// int tokenizer(TwinBuffer TB,LEXEME lex){
//     char* currBuff = TB.curr?TB.buffFirst:TB.buffSecond;
//     char input[20];
//     int i = 0;
//     while(TB.lexemeBegin < TB.forward){
//         if(i == 20){
//             return 0;
//         }
//         input[i] = TB
//     }
// }

void simulateDFA(){
    char* error;
    int state = 0;
    char c;
    TwinBuffer TB;
    int lineCount = 0;
    char* currBuff;
    while(1){
        currBuff = TB.currentBuffer?TB.buffFirst:TB.buffSecond;
        switch(state){
            case -1:
                error = "Lexical Error Occured";
                break;
            case 0:
                printf("START STATE\n");
                // TB.lexemeBegin = TB.forward;
                c = currBuff[TB.forward];
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
                ++TB.forward;
                printf("TOKENIZE TK_PLUS\n");
                state = 0;
                break;
            case 2:
                printf("STATE 2\n");
                ++TB.forward;
                printf("TOKENIZE TK_MINUS\n");
                state = 0;
                break;
            case 3:
                printf("STATE 3\n");
                ++TB.forward;
                printf("TOKENIZE TK_DIV\n");
                state = 0;
                break;
            case 4:
                printf("STATE 4\n");
                ++TB.forward;
                printf("TOKENIZE TK_SEMICOL\n");
                state = 0;
                break;
            case 5:
                printf("STATE 5\n");
                ++TB.forward;
                printf("TOKENIZE TK_COMMA\n");
                state = 0;
                break;
            case 6:
                printf("STATE 6\n");
                ++TB.forward;
                printf("TOKENIZE TK_SQBO\n");
                state = 0;
                break;
            case 7:
                printf("STATE 7\n");
                ++TB.forward;
                printf("TOKENIZE TK_SQBC\n");
                state = 0;
                break;
            case 8:
                printf("STATE 8\n");
                ++TB.forward;
                printf("TOKENIZE TK_BO\n");
                state = 0;
                break;
            case 9:
                printf("STATE 9\n");
                ++TB.forward;
                printf("TOKENIZE TK_BC\n");
                state = 0;
                break;
            case 10:
                printf("STATE 10\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '=') state = 11;
                else state = -1;
                break;
            case 11:
                printf("STATE 11\n");
                ++TB.forward;
                printf("TOKENIZE TK_NE\n");
                state = 0;
                break;
            case 12:
                printf("STATE 12\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '=') state = 13;
                else state = -1;
                break;
            case 13:
                printf("STATE 13\n");
                ++TB.forward;
                printf("TOKENIZE TK_EQ\n");
                state = 0;
                break;
            case 14:
                printf("STATE 14\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '.') state = 15;
                else state = -1;
                break;
            case 15:
                printf("STATE 15\n");
                ++TB.forward;
                printf("TOKENIZE TK_RANGEOP\n");
                state = 0;
                break;
            case 16:
                printf("STATE 16\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '*') state = 17;
                else{
                    printf("TOKENIZE TK_MUL\n");
                    state = 0;
                }
                break;
            case 17:
                printf("STATE 17\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '*') state = 18;
                else state = 17;
                break;
            case 18:
                printf("STATE 18\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '*') state = 19;
                else state = 17;
                break;
            case 19:
                printf("STATE 19\n");
                ++TB.forward;
                printf("TOKENIZE TK_COMMENTMARK\n");
                state = 0;
                break;
            case 20:
                printf("STATE 20\n");
                ++TB.forward;
                c = currBuff[TB.forward];
                if(c == '=') state = 21;
                else{
                    printf("TOKENIZE TK_COLON\n");
                    state = 0;
                }
                break;
            case 21:
                printf("STATE 21\n");
                ++TB.forward;
                printf("TOKENIZE TK_ASSIGNOP\n");
                state = 0;
                break;
        }
    }
}