#ifndef PARSETABLE_H
#define PARSETABLE_H

#include "./addRules.h"
#include "./automation.h"



void populateParseTable(LISTNODE* RULES);
void printParseTable();
short PARSETABLE[70][214];

#endif