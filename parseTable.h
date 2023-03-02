#ifndef PARSER_PARSETABLE_PARSETABLE_H
#define PARSER_PARSETABLE_PARSETABLE_H

#include "./addRules.h"
#include "./automation.h"



void populateParseTable(LISTNODE* RULES);
void printParseTable();
short PARSETABLE[70][214];

#endif