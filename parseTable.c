#include<stdio.h>
#include<stdlib.h>

#include "parseTable.h"

void fillParseTable(){
    for(short int i=0; i<70; i++){
        for(short int j=0; j<214; j++){
            PARSETABLE[i][j] = -1;
        }
    }
}

void populateParseTable(LISTNODE* RULES){
    fillParseTable();
    automateFirstandFollow(RULES);
    
    short int numRules = 129;
    for(short int i = 0;i<numRules;i++){
        LISTNODE head = RULES[i];
        short int row = head -> NODETYPE -> nonterminal;
        short int size = FIRSTANDFOLLOWSETS[i][0];
        for(short int j = 1;j <= size;j++){
            short int col = FIRSTANDFOLLOWSETS[i][j];
            PARSETABLE[row][col] = i;
        }
    }
}


void printParseTable(){
    for(short int i=0; i<70; i++){
        printf("\n %s => ",NONTERMINALS_STRINGS[i]);
        for(short int j=0; j<214; j++){
            if(PARSETABLE[i][j] != -1)
            printf("%s = %d | ",TERMINALS_STRINGS[j] ,PARSETABLE[i][j]);
        }
    }
}