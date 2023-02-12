#include <buffer.h>

/*
    Handler functions for the TwinBuffer struct object
*/

void incrementForward(TwinBuffer &TB){
    // if forward reached end of buffer, fill up the other buffer and put forward to zero
    if(TB.forward == SIZE - 1)  {
        TB.forward = 0;
        return;
    }
    else TB.forward++
    // else simply increment forward

}

char* incrementLexemeBegin(TwinBuffer &TB){
    if(TB.lexemeBegin == SIZE - 1)  {
        char lexemeBeginCharacter = TB.buffer[TB.currentBuffer][SIZE - 1];
        TB.lexemeBegin = 0;
        TB.currentBuffer = 1 - TB.currentBuffer
        populateTwinBuffer(TB);
        return lexemeBeginCharacter;
    }
    else TB.buffer[TB.currentBuffer][ TB.lexemeBegin++];
}

char getCharacterAtForward(TwinBuffer &TB){
    // Major case 1: when the forward is equal to or ahead of lexemeBegin
    if(TB.forward >= TB.lexemeBegin) return TB.buffer[1 - TB.currentBuffer][TB.forward];

    // Major case 2: when the forward is behind lexemeBegin
    else return TB.buffer[TB.currentBuffer][TB.forward];
}

void decrementForward(TwinBuffer &TB){
    
}

