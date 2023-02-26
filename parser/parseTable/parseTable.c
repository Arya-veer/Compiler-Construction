/*

^   24/02
*REQUIRES:
    TODO: FIRST AND FOLLOW SETS   => RUCHI  24/02   
    TODO: LINKED LIST IMPLEMENTATION OF RULES  => ARYA 24/02 IN PROGRESS

~PRODUCES PARSE TABLE

*/
#include<stdio.h>
#include<stdlib.h>

#include "parseTable.h"

void fillParseTable(){
    for(short int i=0; i<63; i++){
        for(short int j=0; j<57; j++){
            PARSETABLE[i][j] = -1;
        }
    }
}

void populateParseTable(){
    // printf("%d\n",RULES[0]->head->NODETYPE->nonterminal);
    fillParseTable();
    printf("PARSE TABLE FILLED WITH -1\n");
    short int numRules = 119;
    for(short int i = 0;i<numRules;i++){
        LISTNODE head = RULES[i];
        short int row = head -> NODETYPE -> nonterminal;
        short int size = firstFollowSet[i][0];
        for(short int j = 1;j <= size;j++){
            short int col = firstFollowSet[i][j];
            // printf("DATA ENTRY DONE AT row = %d,col = %d,rule = %d\n",row,col,i);
            PARSETABLE[row][col] = i;
        }
    }
}


void printParseTable(){
    for(short int i=0; i<63; i++){
        printf(" %s => ",NONTERMINALS_STRINGS[i]);
        for(short int j=0; j<57; j++){
            if(PARSETABLE[i][j] != -1)
            printf("%s = %d | ",TERMINALS_STRINGS[j] ,PARSETABLE[i][j]);
        }
        printf("\n");
    }
}

// int main(){
//     addRules("../../grammar.csv");
//     printRules(119);
//     populateParseTable();
//     printParseTable();
// }