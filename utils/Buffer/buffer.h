#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 4096
#define Buffer char[SIZE]
#ifndef UTILS_READFILE_READFILE_H
#define UTILS_READFILE_READFILE_H

typedef struct twinBuffer TwinBuffer;
struct twinBuffer{
    
    /* Buffers
    */
    Buffer buffer[2];
    /* Begin Pointer
    */
    int lexemeBegin;
    /* Begin Pointer
    */
    int forward;
    /* Current Buffer
    */
    int currentBuffer;
    /* Filename
    */
    FILE* fp;
};

void populateTwinBuffer(TwinBuffer& TB);
TwinBuffer initializeTwinBuffer(char* fname);
void incrementForward(TwinBuffer &TB);
void incrementLexemeBegin(TwinBuffer &TB);
char getCharacterAtForward(TwinBuffer &TB);

#endif 
