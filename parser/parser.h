
#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "dataStructures/parseTable.h"
#include "dataStructures/stack.h"
#include "FnFsets/automation.h"
#include "../lexer/lexer.h"

void parser(char* grammarFile,char* inputFile);
void testAutomation(char* grammarFile);

#endif