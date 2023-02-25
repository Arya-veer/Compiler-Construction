/*

^   24/02
*REQUIRES:
    TODO: FILE HANDLING OF grammar.txt => MADHAV    24/02 
    &DONE TERMINAL AND NONTERMINAL ARRAYS => RUCHI  24/02
    &DONE: LINKEDLIST ADT => ARYA AND RUCHI  24/02

~PRODUCES AN ARRAY OF LINKED LIST HAVING RULES STORED IN IT

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "addRules.h"

int checkTerminal(char* string){
    for(int i = 0;i<56;i++){
        if(strcmp(string,TERMINALS_STRINGS[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int getType(char* string,int type){
    if(type == 1){
        for(int i = 0;i<56;i++){
            if(strcmp(string,TERMINALS_STRINGS[i]) == 0){
                return i;
            }
        }
    }
    for(int i = 0;i<62;i++){
        if(strcmp(string,NONTERMINALS_STRINGS[i]) == 0){
            return i;
        }
    }
    return -1;
}

LINKEDLIST RULES[120];


/*
@params
ruleNum:int => Number of rule as per the grammar
strings[]:char* => The rule is form of array
num:int => Number of strings in the rule
*/
void addRule(int ruleNum,char* strings[],int num){
    LINKEDLIST ll = createLinkedList();
    for(int i = 0;i < num;i++){
        int isTerminal = checkTerminal(strings[i]);
        int ndtype = getType(strings[i],isTerminal);
        inserionInLinkedList(ll,isTerminal,ndtype,ruleNum);
    }
    RULES[ruleNum] = ll;
    return;
}

void printRules(int numRules){
    for(int i = 0;i < numRules;i++){
        LISTNODE curr = RULES[i] -> head;
        while(curr != NULL){
            int rule = curr->ruleNum;
            int isTerminal = curr->isTerminal;
            int nodeType = isTerminal ? curr->NODETYPE->terminal : curr->NODETYPE->nonterminal;
            if(isTerminal == 1){
                printf("Rule no. %d , Terminal %d",rule,nodeType);
            }
            else{
                printf("Rule no. %d , NonTerminal %d",rule,nodeType);
            }
        }
    }
}
