#ifndef PARSER_FNFSETS_AUTOMATE_H
#define PARSER_FNFSETS_AUTOMATE_H
#include "./addRules.h"

int FIRSTANDFOLLOWSETS[129][20];
// int FOLLOWSETS[129][20];
// int SYNCSET[70][20];
void automateFirstandFollow(LISTNODE* RULES);
int inSyncSet(int terminal,int nonterminal);
#endif