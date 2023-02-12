#include <stdio.h>
#include <math.h>
#include <string.h>
#include <buffer.h>


TwinBuffer initializeTwinBuffer(char* fname){
    TwinBuffer TB;
    TB.fp = fopen(fname,"w");
    TB.lexemeBegin = 0;
    TB.forward = 0;
    TB.curr = 0;
}

void populateTwinBuffer(TwinBuffer& TB){
    // call this function whenever TB needs to be filled
    if(! )
    if(TB.currentBuffer == 0) fread(TB.buffer[1], sizeof(char), SIZE, TB.fp)
    else fread(TB.buffer[0], sizeof(char), SIZE, TB.fp)
}