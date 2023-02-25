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
// #include "addRules.h"
#include "../../utils/nonTerminals/nonTerminals.c"
#include "../../utils/terminals/terminals.c"
#include "../dataStructures/linkedList.c"
#include "../../utils/csvReader/csvReader.c"

int checkTerminal(char* string){
    for(int i = 0;i<57;i++){
        if(strcmp(string,TERMINALS_STRINGS[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int getType(char* string,int type){
    if(type == 1){
        for(int i = 0;i<57;i++){
            if(strcmp(string,TERMINALS_STRINGS[i]) == 0){
                return i;
            }
        }
    }
    for(int i = 0;i<63;i++){
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
void addRule(int ruleNum,char** strings,int num){
    LINKEDLIST ll = createLinkedList();
    // printf("Linked List Created\n");
    for(int i = 0;i < num;i++){
        // printf("strings[i] = %s\n",strings[i]);
        if(strings[i] == (char*)NULL) break;
        // printf("STRING IS NOT NULL\n");
        int isTerminal = checkTerminal(strings[i]);
        // printf("isTerminal %d\n",isTerminal);
        int ndtype = getType(strings[i],isTerminal);
        // printf("RULE TYPE %d\n",ndtype);
        insertionInLinkedList(ll,isTerminal,ndtype,ruleNum);
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
                printf("Rule no. %d , Terminal %d\n",rule,nodeType);
            }
            else{
                printf("Rule no. %d , NonTerminal %d\n",rule,nodeType);
            }
            curr=curr->next;
        }
    }
}


void addRules(){
    int ruleNum = 0;
    FILE* fp = fopen("../../grammar.csv","r");
    // printf("File opened\n");
    while(1){
        // printf("RULE NUMBER = %d\n",ruleNum);
        char** row = csvReader(fp);
        // printf("Got a row\n");
        if(row[0] == NULL) break;
        addRule(ruleNum,row,119);
        // printf("Rule added\n");
        ruleNum++;
        // printf("__________________________________________\n");
    }
    // printRules(119);
    fclose(fp);

}

// int main(){
//     addRules();
// }