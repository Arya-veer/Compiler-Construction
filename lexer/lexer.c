#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"

void populateTwinBuffer(TwinBuffer *TB){
    // call this function whenever TB needs to be filled
    int length = fread(TB->buffer[TB->currentForward], sizeof(char), TB->SIZE, TB->fp);
    if(length != TB->SIZE) TB->buffer[TB->currentForward][length] = EOF;
    // printf("\n\nsize = %d\n_______________________\n%s\n______________________\n\n", length, TB->buffer[TB->currentForward]);
}

TwinBuffer* initializeTwinBuffer(char* fname, int bufferSize){
    TwinBuffer* TB = (TwinBuffer*) malloc(sizeof(TwinBuffer));
    TB->fp = fopen(fname,"r");
    TB->SIZE = bufferSize;
    TB->lexemeBegin = 0;
    TB->forward = 0;
    TB->currentLexemeBegin = 0;
    TB->currentForward = 0;
    TB->buffer[0] = malloc(bufferSize);
    TB->buffer[1] = malloc(bufferSize);
    populateTwinBuffer(TB);
    return TB;
}

void cleanTwinBuffer(TwinBuffer* TB){
    free(TB->buffer[0]);
    free(TB->buffer[1]);
}

void incrementForward(TwinBuffer *TB){
    // if forward reached end of buffer, fill up the other buffer and put forward to zero
    if(TB->forward == TB->SIZE - 1)  {
        TB->forward = 0;
        TB->currentForward = 1 - TB->currentForward;
        populateTwinBuffer(TB);
        return;
    }
    else TB->forward++;
    // else simply increment forward
}

void decrementForward(TwinBuffer *TB){
    // if forward reached end of buffer, fill up the other buffer and put forward to zero
    if(TB->forward == 0)  {
        TB->forward = TB->SIZE - 1;
        TB->currentForward =   1 - TB->currentForward;

        return;
    }
    else TB->forward--;
    // else simply increment forward
}

short findLexemeLength(TwinBuffer *TB){
    // Major case 1: when the forward is equal to or ahead of lexemeBegin
    if(TB->currentForward != TB->currentLexemeBegin) return TB->SIZE + TB->forward - TB->lexemeBegin;

    // Major case 2: when the forward is behind lexemeBegin
    else return  TB->forward - TB->lexemeBegin;
}


// not exported
char moveLexemeBegin(TwinBuffer *TB){
    if(TB->lexemeBegin == TB->SIZE - 1)  {
        char lexemeBeginCharacter = TB->buffer[TB->currentLexemeBegin][TB->SIZE - 1];
        TB->lexemeBegin = 0;
        TB->currentLexemeBegin = 1 - TB->currentLexemeBegin;
        return lexemeBeginCharacter;
    }
    else return TB->buffer[TB->currentLexemeBegin][ TB->lexemeBegin++];
}


/* MAKE SURE THAT LEXEME_BEGIN IS AT A NON-WHITESPACE CHARACTER */
char* extractLexeme(TwinBuffer *TB){

    short length = findLexemeLength(TB);
    short i = 0;
    for (i = 0; i < length; i++){
        ReturnLexeme[i] = moveLexemeBegin(TB);
    }
    ReturnLexeme[i] = '\0';
    return ReturnLexeme;
    
}

char getCharacterAtForward(TwinBuffer *TB){
    return TB->buffer[TB->currentForward][TB->forward];
}

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
 */
void skipComment(TwinBuffer *TB,short toPrint){
    char* input = extractLexeme(TB);
    if(toPrint == 1)printf("Skipped Comment\n");
}

LEXEME* tokenizeEOF(TwinBuffer *TB,short line){
    char* input = extractLexeme(TB);
    LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    lex->token = EOF_TOKEN;
    lex->lineNo = line;
    return lex;
}


int hashCode(char* str){
    int num=2;
    int k=214;
    int product=0;

    for(int i=0;i<strlen(str);i++){
        product=product*num+str[i];
    }

    product=product%k;

    return product;
}


LEXEME* tokenize(TwinBuffer *TB,short int line,short toPrint){
    char* input = extractLexeme(TB);
    // printf("Tokenize got input as %s\n",input);
    if(input[0] == ' ' || input[0] == '\n' || input[0] == '\t' || input[0] == EOF) return NULL; // If a white space is there do not tokenize it
    LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    lex->lexemedata = (union lexemeData*) malloc(sizeof(union lexemeData));
    lex->lineNo = line;

    /* 
        Checking For Int or Float 
    */
    if(input[0] >= '0' && input[0] <= '9'){
        if(isFloat(input)){
            char* endWord;
            lex->lexemedata->floatData = strtod(input,&endWord);
            lex->token = RNUM_TOKEN;
            if(toPrint == 1)printf("LINE NO: %d         LEXEME: %lf         TOKEN: %s\n",line,lex->lexemedata->floatData,"RNUM");
        }
        else{
            lex->lexemedata->intData = atoi(input);
            lex->token = NUM_TOKEN;
            if(toPrint == 1)printf("LINE NO: %d         LEXEME: %d         TOKEN: %s\n",line,lex->lexemedata->intData,"NUM");
        }
        return lex;
    }
    lex->lexemedata->data = input;
    short found = 0;
    int hc = hashCode(input);
    // printf("HASH IS %d\n",hc);
    if(strcmp(input,TOKENS_STRING[hc]) == 0){
        lex->token = (TOKENS) hc;
        found = 1;
        if(toPrint == 1)printf("LINE NO: %d         LEXEME: %s         TOKEN: %s\n",line,input,TERMINALS_STRINGS[hc]);
        // break;
    }
    if(found == 0){
        lex->token = IDENTIFIER_TOKEN;
        if(toPrint == 1)printf("LINE NO: %d         LEXEME: %s         TOKEN: %s\n",line,input,"ID");
    }

    /* Checking For Keywords */
    // for(short int i=0;i <= 52;i++){
        
    //     if(strcmp(input,TOKENS_STRING[i]) == 0){
    //         lex->token = (TOKENS) i;
    //         found = 1;
    //         if(toPrint == 1)printf("LINE NO: %d         LEXEME: %s         TOKEN: %s\n",line,input,TERMINALS_STRINGS[i]);
    //         break;
    //     }
    // } 


    return lex;
}

short int lineCount = 1;

LEXEME* simulateDFA(TwinBuffer *TB,short toPrint){
    char* error;
    short int state = 0;
    char c;
    short charCount;
    char errorChar;
    char* errorString;
    LEXEME* lex;
    while(1){
        switch(state){
            case -1:
                errorChar = getCharacterAtForward(TB);
                errorString = extractLexeme(TB);
                printf("Lexical Error occured at line %hi, \"%s\" ,  invalid character '%c'\n",lineCount,errorString,c);
                state = 0;
                break;
            case 0:
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
                else if ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z') || (c == '_')) {
                    state = 28;
                    charCount = 1;
                }
                else if (c == '>') state = 29;
                else if (c == '<') state = 33;
                else if (c == ' ') state = 37;
                else if (c == '\t') state = 38;
                else if (c == '\n') {
                    state = 39; 
                    (lineCount)++;
                    break;
                }
                else if (c == EOF || c == '\0') state = 40;
                else {
                    incrementForward(TB);
                    state = -1;

                }
                break;
            
            case 1:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 2:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 3:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 4:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 5:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 6:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 7:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 8:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 9:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 10:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 11;
                else state = -1;
                break;
            case 11:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 12:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 13;
                else state = -1;
                break;
            case 13:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 14:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '.') state = 15;
                else state = -1;
                break;
            case 15:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 16:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 17;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 17:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 18;
                else if(c == EOF) return tokenizeEOF(TB,lineCount);
                else if(c == '\n') ++lineCount;
                else state = 17;
                break;
            case 18:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 19;
                else state = 17;
                break;
            case 19:
                incrementForward(TB);
                skipComment(TB,toPrint);
                state=0;
                break;
            case 20:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 21;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 21:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 22:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '.') state = 23;
                else if(c >= '0' && c <= '9') state = 22;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 23:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if(c == '.'){
                    decrementForward(TB);
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                else state = -1;
                break;
            case 24:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if (c == 'e' || c == 'E') state = 25;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 25:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '+' || c == '-') state = 26;
                else if(c >= '0' && c <= '9') state = 27;
                else state = -1;
                break;
            case 26:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 27;
                else state = -1;
                break;
            case 27:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 27;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 28:
                charCount++;
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_')) state = 28;
                else {
                    if(charCount > 20){
                        errorString = extractLexeme(TB);
                        printf("Lexical Error occured at line %hi, \"%s\" , Variable Length can not be more than 20\n",lineCount,errorString);
                        state = 0;
                        break;
                    }
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 29:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 30;
                else if(c == '>') state = 31;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 30:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 31:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '>') state = 32;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 32:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 33:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 34;
                else if(c == '<') state = 35;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 34:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 35:
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '<') state = 36;
                else{
                    lex = tokenize(TB,lineCount,toPrint);
                    return lex;
                }
                break;
            case 36:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                return lex;
                break;
            case 37:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                state = 0;
                break;
            case 38:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                state = 0;
                break;
            case 39:
                incrementForward(TB);
                lex = tokenize(TB,lineCount,toPrint);
                state = 0;
                break;
            case 40:
                return tokenizeEOF(TB,lineCount);
        }
    }
}