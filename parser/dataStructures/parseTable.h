#ifndef PARSER_PARSETABLE_PARSETABLE_H
#define PARSER_PARSETABLE_PARSETABLE_H

#include "./addRules.h"
#include "../FnFsets/sets.h"


void populateParseTable(LISTNODE* RULES);
void printParseTable();
short PARSETABLE[70][57];

#endif