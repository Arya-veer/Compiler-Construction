
#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "dataStructures/parseTable.h"
#include "dataStructures/stack.h"
// #include "FnFsets/automation.h"
#include "../lexer/lexer.h"
#include "./FnFsets/followSets.h"

void parser(char* grammarFile,char* inputFile, char* outputFile);
void testAutomation(char* grammarFile);

#endif