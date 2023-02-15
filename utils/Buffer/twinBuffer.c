#include "buffer.h"

/*
    Handler functions for the TwinBuffer struct object
*/

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

int findLexemeLength(TwinBuffer *TB){
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
int isWhiteSpace(char c){
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
    int length = findLexemeLength(TB);
    int i = 0;
    // printf("length = %d\n",length);
    for (i = 0; i < length; i++)
    {
        ReturnLexeme[i] = moveLexemeBegin(TB);
        // printf("Inside extractLexeme ==============> %c\n",ReturnLexeme[i]);

        // if(isWhiteSpace(ReturnLexeme[i])) --i;
    }
    ReturnLexeme[i] = '\0';
    // printf(" Extracted Lexeme is %s\n",ReturnLexeme);
    return ReturnLexeme;
    
}

char getCharacterAtForward(TwinBuffer *TB){

    char c =  TB->buffer[TB->currentForward][TB->forward];
    return c;
}