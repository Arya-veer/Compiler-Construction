#include <buffer.h>

/*
    Handler functions for the TwinBuffer struct object
*/

void incrementForward(TwinBuffer &TB){
    // if forward reached end of buffer, fill up the other buffer and put forward to zero
    if(TB.forward == SIZE - 1)  {
        populateTwinBuffer(TB);
        TB.forward = 0;
        return;
    }
    else TB.forward++
    // else simply increment forward

}

void incrementLexemeBegin(TwinBuffer &TB){
    if(TB.lexemeBegin == SIZE - 1)  {
        populateTwinBuffer(TB);
        TB.lexemeBegin = 0;
        return;
    }
    else TB.lexemeBegin++
}

char getCharacterAtForward(TwinBuffer &TB){

}

