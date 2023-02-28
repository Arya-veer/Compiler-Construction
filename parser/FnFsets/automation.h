#ifndef PARSER_FNFSETS_AUTOMATE_H
#define PARSER_FNFSETS_AUTOMATE_H
#include "../rules/addRules.h"

int FIRSTANDFOLLOWSETS[119][20];
void automateFirstandFollow(LISTNODE* RULES);

#endif