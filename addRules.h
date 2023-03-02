#ifndef PARSER_RULES_ADDRULES_H
#define PARSER_RULES_ADDRULES_H

#include "./linkedList.h"
#include "./csvReader.h"


LISTNODE* addRules(char* fname);
void printRules(short int numRules, LISTNODE* RULES);

#endif