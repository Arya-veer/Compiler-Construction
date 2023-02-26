#ifndef PARSER_PARSETABLE_PARSETABLE_H
#define PARSER_PARSETABLE_PARSETABLE_H

#include "../rules/addRules.h"
#include "../FnFsets/sets.h"


void populateParseTable(LISTNODE* RULES);
void printParseTable();
short PARSETABLE[63][57];

#endif