
#include<stdio.h>
#ifndef LEXER_H
#define LEXER_H
#include "lexerDef.h"
TwinBuffer* initializeTwinBuffer(char* fname, int bufferSize);
LEXEME* simulateDFA(TwinBuffer *TB,short toPrint);
void cleanTwinBuffer(TwinBuffer* TB);

#endif