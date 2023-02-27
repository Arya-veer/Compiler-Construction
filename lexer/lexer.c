#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lexer.h"
// #include "../utils/errors/errors.c"
// #include "tokenize.c"

void populateTwinBuffer(TwinBuffer *TB){
    // call this function whenever TB needs to be filled
    int length = fread(TB->buffer[TB->currentForward], sizeof(char), SIZE, TB->fp);
    if(length != SIZE) TB->buffer[TB->currentForward][length] = EOF;
    // TB->buffer[TB->currentForward][length + 1] = -1;
    // printf("\n\nsize = %d\n_______________________\n%s\n______________________\n\n", length, TB->buffer[TB->currentForward]);
}

TwinBuffer* initializeTwinBuffer(char* fname){
    // preprocessFile(fname,-1);
    char dta[2];
    dta[0] = -1;
    dta[1] = -1;
    TwinBuffer* TB = (TwinBuffer*) malloc(sizeof(TwinBuffer));
    // TB->fp = fopen(fname,"a");
    // fputs(dta,TB->fp);
    // fclose(TB->fp);
    TB->fp = fopen(fname,"r");
    TB->lexemeBegin = 0;
    TB->forward = 0;
    TB->currentLexemeBegin = 0;
    TB->currentForward = 0;
    populateTwinBuffer(TB);
    return TB;
}

void incrementForward(TwinBuffer *TB){
    // if forward reached end of buffer, fill up the other buffer and put forward to zero
    if(TB->forward == SIZE - 1)  {
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
        TB->forward = SIZE - 1;
        TB->currentForward =   1 - TB->currentForward;

        return;
    }
    else TB->forward--;
    // else simply increment forward
}

short findLexemeLength(TwinBuffer *TB){
    // Major case 1: when the forward is equal to or ahead of lexemeBegin
    if(TB->currentForward != TB->currentLexemeBegin) return SIZE + TB->forward - TB->lexemeBegin;

    // Major case 2: when the forward is behind lexemeBegin
    else return  TB->forward - TB->lexemeBegin;
}


// not exported
char moveLexemeBegin(TwinBuffer *TB){
    if(TB->lexemeBegin == SIZE - 1)  {
        char lexemeBeginCharacter = TB->buffer[TB->currentLexemeBegin][SIZE - 1];
        TB->lexemeBegin = 0;
        TB->currentLexemeBegin = 1 - TB->currentLexemeBegin;
        return lexemeBeginCharacter;
    }
    else return TB->buffer[TB->currentLexemeBegin][ TB->lexemeBegin++];
}

// not exported
short isWhiteSpace(char c){
     return (
                c == ' ' ||
                c == '\t' ||
                c == '\n' ||
                c == '\r' ||
                c == '\b' ||
                c == EOF
     );
}

/* MAKE SURE THAT LEXEME_BEGIN IS AT A NON-WHITESPACE CHARACTER */
char* extractLexeme(TwinBuffer *TB){

    // TODO: need to test this function
    short length = findLexemeLength(TB);
    short i = 0;
    // printf("length = %d\n",length);
    for (i = 0; i < length; i++)
    {
        ReturnLexeme[i] = moveLexemeBegin(TB);
        // printf("Inside extractLexeme ==============> %c\n",ReturnLexeme[i]);

        // if(isWhiteSpace(ReturnLexeme[i])) --i;
    }
    ReturnLexeme[i] = '\0';
    // printf(" Extracted Lexeme is _______\n%s\n_____________",ReturnLexeme);
    return ReturnLexeme;
    
}

char getCharacterAtForward(TwinBuffer *TB){

    char c =  TB->buffer[TB->currentForward][TB->forward];
    return c;
}


char* TOKENS_STRING[] = {

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
    };

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
void skipComment(TwinBuffer *TB){
    char* input = extractLexeme(TB);
    // LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    // lex -> token = EOF_TOKEN;
    printf("Skipped Comment\n");
    // return lex;
}

LEXEME* tokenizeEOF(TwinBuffer *TB,short line){
    char* input = extractLexeme(TB);
    LEXEME* lex = (LEXEME*) malloc(sizeof(LEXEME));
    lex -> token = EOF_TOKEN;
    lex->lineNo = line;
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
    // printf("Tokenized %d , sending it for parsing\n",lex->token);
    return lex;
}

short int lineCount = 1;

LEXEME* simulateDFA(TwinBuffer *TB){
    char* error;
    short int state = 0;
    char c;
    short charCount;
    char errorChar;
    char* errorString;
    LEXEME* lex;
    // int lineCount = 0;
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
                // printf("STATE 1\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_PLUS\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 2:
                // printf("STATE 2\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_MINUS\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 3:
                // printf("STATE 3\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_DIV\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 4:
                // printf("STATE 4\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_SEMICOL\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 5:
                // printf("STATE 5\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_COMMA\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 6:
                // printf("STATE 6\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_SQBO\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 7:
                // printf("STATE 7\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_SQBC\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 8:
                // printf("STATE 8\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_BO\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 9:
                // printf("STATE 9\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_BC\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 10:
                // printf("STATE 10\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 11;
                else state = -1;
                break;
            case 11:
                // printf("STATE 11\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_NE\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 12:
                // printf("STATE 12\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 13;
                else state = -1;
                break;
            case 13:
                // printf("STATE 13\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_EQ\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 14:
                // printf("STATE 14\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '.') state = 15;
                else state = -1;
                break;
            case 15:
                // printf("STATE 15\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_RANGEOP\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 16:
                // printf("STATE 16\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 17;
                else{
                    // printf("TOKENIZE TK_MUL\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 17:
                // printf("STATE 17\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 18;
                else if(c == EOF) return tokenizeEOF(TB,lineCount);
                else if(c == '\n') ++lineCount;
                else state = 17;
                break;
            case 18:
                // printf("STATE 18\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '*') state = 19;
                else state = 17;
                break;
            case 19:
                // printf("STATE 19\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_COMMENTMARK\n");
                skipComment(TB);
                state=0;
                break;
            case 20:
                // printf("STATE 20\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 21;
                else{
                    // printf("TOKENIZE TK_COLON\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 21:
                // printf("STATE 21\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_ASSIGNOP\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 22:
                // printf("STATE 22\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '.') state = 23;
                else if(c >= '0' && c <= '9') state = 22;
                else{
                    // printf("TOKENIZE TK_NUM\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 23:
                // printf("STATE 23\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if(c == '.'){
                    decrementForward(TB);
                    // printf("TOKENIZE TK_NUM\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                else state = -1;
                break;
            case 24:
                // printf("STATE 24\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 24;
                else if (c == 'e' || c == 'E') state = 25;
                else{
                    // printf("TOKENIZE TK_RNUM\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 25:
                // printf("STATE 25\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '+' || c == '-') state = 26;
                else if(c >= '0' && c <= '9') state = 27;
                else state = -1;
                break;
            case 26:
                // printf("STATE 26\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 27;
                else state = -1;
                break;
            case 27:
                // printf("STATE 27\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c >= '0' && c <= '9') state = 27;
                else{
                    // printf("TOKENIZE TK_RNUM\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 28:
                // printf("STATE 28\n");
                charCount++;
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                // printf("%d\n",c);
                if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_')) state = 28;
                else {
                    // printf("TOKENIZE TK_ID OR TK_KW\n");
                    if(charCount > 20){
                        errorString = extractLexeme(TB);
                        printf("Lexical Error occured at line %hi, \"%s\" , Variable Length can not be more than 20\n",lineCount,errorString);
                        state = 0;
                        break;
                    }
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 29:
                // printf("STATE 29\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 30;
                else if(c == '>') state = 31;
                else{
                    // printf("TOKENIZE TK_GT\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 30:
                // printf("STATE 30\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_GE\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 31:
                // printf("STATE 31\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '>') state = 32;
                else{
                    // printf("TOKENIZE TK_ENDDEF\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 32:
                // printf("STATE 32\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_DRIVERENDDEF\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 33:
                // printf("STATE 33\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '=') state = 34;
                else if(c == '<') state = 35;
                else{
                    // printf("TOKENIZE TK_LT\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 34:
                // printf("STATE 34\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_LE\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 35:
                // printf("STATE 35\n");
                incrementForward(TB);
                c = getCharacterAtForward(TB);
                if(c == '<') state = 36;
                else{
                    // printf("TOKENIZE TK_DEF\n");
                    lex = tokenize(TB,lineCount);
                    return lex;
                }
                break;
            case 36:
                // printf("STATE 36\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_DRIVERDEF\n");
                lex = tokenize(TB,lineCount);
                return lex;
                break;
            case 37:
                // printf("STATE 37\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_SPACE\n");
                lex = tokenize(TB,lineCount);
                // return lex;
                state = 0;
                break;
            case 38:
                // printf("STATE 38\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_TAB\n");
                lex = tokenize(TB,lineCount);
                // return lex;
                state = 0;
                break;
            case 39:
                // printf("STATE 39\n");
                incrementForward(TB);
                // printf("TOKENIZE TK_NEWLINE\n");
                lex = tokenize(TB,lineCount);
                // return lex;
                state = 0;
                break;
            case 40:
                // printf("STATE 40\n");
                return tokenizeEOF(TB,lineCount);
        }
    }
}