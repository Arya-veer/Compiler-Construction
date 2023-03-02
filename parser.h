
#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "./parseTable.h"
#include "./stack.h"
#include "./automation.h"
#include "./lexer.h"
// #include "./FnFsets/followSets.h"

void parser(char* grammarFile,char* inputFile, char* outputFile, int size);
void testAutomation(char* grammarFile);

#endif