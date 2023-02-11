#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 4096


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

typedef struct twiBuff TwinBuffer;

void populateTwinBuff(TwinBuffer TB);