#include <stdio.h>
#include <math.h>
#include <string.h>
#include <buffer.h>


TwinBuffer initializeTwinBuffer(char* fname){
    TwinBuffer TB;
    TB.fp = fopen(fname,"w");
    TB.lexemeBegin = 0;
    TB.forward = 0;
    TB.currentBuffer = 0;
}

void populateTwinBuffer(TwinBuffer& TB){
    // call this function whenever TB needs to be filled
    if(TB.lexemeBegin > LEXEME_SIZE) return;
    fread(TB.buffer[1 - TB.currentBuffer], sizeof(char), SIZE, TB.fp);
}