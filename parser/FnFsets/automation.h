#ifndef PARSER_FNFSETS_AUTOMATE_H
#define PARSER_FNFSETS_AUTOMATE_H
#include "../dataStructures/addRules.h"

int FIRSTANDFOLLOWSETS[129][20];
void automateFirstandFollow(LISTNODE* RULES);

#endif