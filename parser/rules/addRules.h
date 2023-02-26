#ifndef PARSER_RULES_ADDRULES_H
#define PARSER_RULES_ADDRULES_H

#include "../../utils/nonTerminals/nonTerminals.h"
#include "../../utils/terminals/terminals.h"
#include "../dataStructures/linkedList.h"
#include "../../utils/csvReader/index.h"


LINKEDLIST RULES[120];
void addRules(char* fname);

#endif