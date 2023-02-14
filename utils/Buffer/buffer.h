#include <stdio.h>
#include <math.h>
#include <string.h>
#ifndef UTILS_READFILE_READFILE_H
#define UTILS_READFILE_READFILE_H
#define SIZE 4096
#define LEXEME_SIZE 32

typedef struct twinBuffer TwinBuffer;
typedef char SingleBuffer[SIZE];
char ReturnLexeme[LEXEME_SIZE];
struct twinBuffer{
    
    /* Buffers
    */
    SingleBuffer buffer[2];
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
char* extractLexeme(TwinBuffer &TB);
char getCharacterAtForward(TwinBuffer &TB);
void populateTwinBuffer(TwinBuffer& TB);
void decrementForward(TwinBuffer &TB);

#endif 
