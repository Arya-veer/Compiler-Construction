//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#include<stdio.h>
#ifndef LEXER_H
#define LEXER_H
#include "lexerDef.h"
TwinBuffer* initializeTwinBuffer(char* fname, int bufferSize);
LEXEME* simulateDFA(TwinBuffer *TB,short toPrint);
void cleanTwinBuffer(TwinBuffer* TB);

#endif