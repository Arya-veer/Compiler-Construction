#include <stdio.h>
#include <math.h>
#include <string.h>
#include "buffer.h"

TwinBuffer initializeTwinBuffer(char* fname){
    // preprocessFile(fname,-1);
    TwinBuffer TB;
    TB.fp = fopen(fname,"r");
    TB.lexemeBegin = 0;
    TB.forward = 0;
    TB.currentLexemeBegin = 0;
    TB.currentForward = 0;
    populateTwinBuffer(&TB);
    return TB;
}

void populateTwinBuffer(TwinBuffer *TB){
    // call this function whenever TB needs to be filled
    int length = fread(TB->buffer[TB->currentForward], sizeof(char), SIZE, TB->fp);
    // TB->buffer[TB->currentForward][length] = 0;
    // TB->buffer[TB->currentForward][length + 1] = 0;
    printf("size = %d ___________________\n%s\n", length, TB->buffer[TB->currentForward]);
}

/* 

  Buffer 1:   1  2
  Buffer 2:   3  4
    
 */