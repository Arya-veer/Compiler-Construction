#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 4096
#ifndef UTILS_READFILE_READFILE_H
#define UTILS_READFILE_READFILE_H

typedef struct twiBuff TwinBuffer;
struct twiBuff{
    /* Buffer 1
    */
    char buffFirst[SIZE];
    /* Buffer 2
    */
    char buffSecond[SIZE];
    /* Begin Pointer
    */
    int lexemeBegin;
    /* Begin Pointer
    */
    int forward;
    /* Current Buffer
    */
    int curr;
    /* Filename
    */
    FILE* fp;
};

#endif 
void populateTwinBuff(TwinBuffer TB);
