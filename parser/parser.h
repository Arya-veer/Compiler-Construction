
#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "parseTable/parseTable.h"
#include "dataStructures/stack.h"
// #include "rules/addRules.h"
#include "FnFsets/automation.h"
#include "../lexer/lexer.h"
// #include "../utils/Buffer/buffer.h"

void parser(char* grammarFile,char* inputFile);
void testAutomation(char* grammarFile);

#endif