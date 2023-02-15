#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"


void simulateDFA(TwinBuffer *TB){
    char* error;
    int state = 0;
    char c;
    int lineCount = 0;
    char* currBuff;
    while(1){
        switch(state){
            case -1:
                printf("Lexical Error Occured\n");

                return;
            case 0:
                printf("START STATE\n");
                // TB.lexemeBegin = TB.forward;
                c = getCharacterAtForward(TB);
                printf("current char = %d\n",c);
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
                else if (c == '\n') state = 39, lineCount++;
                else if (c == EOF || c == '\0') state = 40;
                else state = -1;
                break;
            
            case 1:
                printf("STATE 1\n");
                incrementForward(TB);
                printf("TOKENIZE TK_PLUS\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 2:
                printf("STATE 2\n");
                incrementForward(TB);
                printf("TOKENIZE TK_MINUS\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 3:
                printf("STATE 3\n");
                incrementForward(TB);
                printf("TOKENIZE TK_DIV\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 4:
                printf("STATE 4\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SEMICOL\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 5:
                printf("STATE 5\n");
                incrementForward(TB);
                printf("TOKENIZE TK_COMMA\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 6:
                printf("STATE 6\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SQBO\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 7:
                printf("STATE 7\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SQBC\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 8:
                printf("STATE 8\n");
                incrementForward(TB);
                printf("TOKENIZE TK_BO\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 9:
                printf("STATE 9\n");
                incrementForward(TB);
                printf("TOKENIZE TK_BC\n");
                tokenize(TB,lineCount);
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
                tokenize(TB,lineCount);
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
                tokenize(TB,lineCount);
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
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 16:
                printf("STATE 16\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 17;
                else{
                    printf("TOKENIZE TK_MUL\n");
                    tokenize(TB,lineCount);
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
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 20:
                printf("STATE 20\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 21;
                else{
                    printf("TOKENIZE TK_COLON\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 21:
                printf("STATE 21\n");
                incrementForward(TB);
                printf("TOKENIZE TK_ASSIGNOP\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 22:
                printf("STATE 22\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                printf("Inside case 22, c = %d\n",c);
                if(c == '.') state = 23;
                else if(c >= '0' && c <= '9') state = 22;
                else{
                    printf("TOKENIZE TK_NUM\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 23:
                printf("STATE 23\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if(c == '.'){
                    decrementForward(TB);
                    printf("TOKENIZE TK_NUM\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                else state = -1;
                break;
            case 24:
                printf("STATE 24\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if (c == 'e' || c == 'E') state = 25;
                else{
                    printf("TOKENIZE TK_RNUM\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 25:
                printf("STATE 25\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '+' || c == '-') state = 26;
                else if(c >= '0' && c <= '9') state = 27;
                else state = -1;
                break;
            case 26:
                printf("STATE 26\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 27;
                else state = -1;
                break;
            case 27:
                printf("STATE 27\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 27;
                else{
                    printf("TOKENIZE TK_RNUM\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 28:
                printf("STATE 28\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_')) state = 28;
                else {
                    printf("TOKENIZE TK_ID OR TK_KW\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 29:
                printf("STATE 29\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 30;
                else if(c == '>') state = 31;
                else{
                    printf("TOKENIZE TK_GT\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 30:
                printf("STATE 30\n");
                incrementForward(TB);
                printf("TOKENIZE TK_GE\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 31:
                printf("STATE 31\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '>') state = 32;
                else{
                    printf("TOKENIZE TK_ENDDEF\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 32:
                printf("STATE 32\n");
                incrementForward(TB);
                printf("TOKENIZE TK_DRIVERENDDEF\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 33:
                printf("STATE 33\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 34;
                else if(c == '<') state = 35;
                else{
                    printf("TOKENIZE TK_LT\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 34:
                printf("STATE 34\n");
                incrementForward(TB);
                printf("TOKENIZE TK_LE\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 35:
                printf("STATE 35\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '<') state = 36;
                else{
                    printf("TOKENIZE TK_DEF\n");
                    tokenize(TB,lineCount);
                    state = 0;
                }
                break;
            case 36:
                printf("STATE 36\n");
                incrementForward(TB);
                printf("TOKENIZE TK_DRIVERDEF\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 37:
                printf("STATE 37\n");
                incrementForward(TB);
                printf("TOKENIZE TK_SPACE\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 38:
                printf("STATE 38\n");
                incrementForward(TB);
                printf("TOKENIZE TK_TAB\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 39:
                printf("STATE 39\n");
                incrementForward(TB);
                printf("TOKENIZE TK_NEWLINE\n");
                tokenize(TB,lineCount);
                state = 0;
                break;
            case 40:
                printf("STATE 40\n");
                incrementForward(TB);
                printf("TOKENIZE TK_EOF\n");
                tokenize(TB,lineCount);
                state = 0;
                printf("ENDING DFA PARSING\n");
                return;
        }
    }
}