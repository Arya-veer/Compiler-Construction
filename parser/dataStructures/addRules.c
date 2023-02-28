#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "addRules.h"

short int checkTerminal(char* string){
    for(short int i = 0;i<57;i++){
        if(strcmp(string,TERMINALS_STRINGS[i]) == 0){
            return 1;
        }
    }
    return 0;
}

short int getType(char* string,short int type){
    if(type == 1){
        for(short int i = 0;i<57;i++){
            if(strcmp(string,TERMINALS_STRINGS[i]) == 0){
                return i;
            }
        }
    }
    for(short int i = 0;i<68;i++){
        if(strcmp(string,NONTERMINALS_STRINGS[i]) == 0){
            return i;
        }
    }
    return -1;
}




/*
@params
ruleNum:int => Number of rule as per the grammar
strings[]:char* => The rule is form of array
num:int => Number of strings in the rule
*/
void addRule(short int ruleNum,char** strings,short int num,LISTNODE* RULES){
    LINKEDLIST ll = createLinkedList();
    for(short int i = 0;i < num;i++){
        if(strings[i] == (char*)NULL) break;
        short int isTerminal = checkTerminal(strings[i]);
        short int ndtype = getType(strings[i],isTerminal);
        insertionInLinkedList(ll,isTerminal,ndtype,ruleNum);
    }
    RULES[ruleNum] = ll->head;
    return;
}

void printRules(short int numRules, LISTNODE* RULES){
    for(short int i = 0;i < numRules;i++){
        LISTNODE curr = RULES[i];
        while(curr != NULL){
            short int rule = curr->ruleNum;
            short int isTerminal = curr->isTerminal;
            short int nodeType = isTerminal ? curr->NODETYPE->terminal : curr->NODETYPE->nonterminal;
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


LISTNODE* addRules(char* fname){
    short int ruleNum = 0;
    FILE* fp = fopen(fname,"r");
    LISTNODE* RULES = (LISTNODE*) malloc(128*sizeof(LISTNODE));
    while(1){
        char** row = csvReader(fp);
        if(row[0] == NULL) break;
        addRule(ruleNum,row,128,RULES);
        ruleNum++;
    }
    fclose(fp);
    return RULES;
}
