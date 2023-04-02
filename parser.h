//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#ifndef PARSER_H
#define PARSER_H

// #include "./FnFsets/followSets.h"

TREENODE parser(char* grammarFile,char* inputFile, char* outputFile, int size);
void testAutomation(char* grammarFile);
TREENODE getChildNonTerminal(int nt,TREENODE tn);
TREENODE getChildTerminal(int nt,TREENODE tn);
TREENODE* getDualNonTerminal(int nt,TREENODE tn);
TREENODE* getDualTerminal(int nt,TREENODE tn);
#endif