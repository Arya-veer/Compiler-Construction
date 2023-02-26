#include <stdio.h>
#include <stdlib.h>

// #include "../rules/addRules.c"
#include "automation.h"
// int FIRSTANDFOLLOWSETS[119][20];

// void follow(){
//     for(int j = 0 ; j < numRules ; j++){
//         LISTNODE temp = RULES[j] -> head;
//         temp = temp ->next;
//         while(temp){
//             if(temp->NODETYPE->nonterminal == RULES[i] -> head -> NODETYPE -> nonterminal){
//                 if(temp->next)LISTNODE help = temp->next;
//                for(int k = FIRSTANDFOLLOWSETS[i][0]+1 ; k <= FIRSTANDFOLLOWSETS[i][0] + FIRSTANDFOLLOWSETS[j][0] ; k++){
//                     FIRSTANDFOLLOWSETS[i][k] = FIRSTANDFOLLOWSETS[j][k - FIRSTANDFOLLOWSETS[i][0]];
//             }
//         }
//     }
// }

void find(int *vis, LISTNODE *RULES, int i, int prev_i, LISTNODE prev_curr){
//    printf("i = %d, prev_i = %d\n",i,prev_i);
    if (vis[i] == 1 ){
        // printf("")
        return;
    }
    
    int numRules = 119;
    LISTNODE curr = RULES[i];
    curr = curr->next;

    if (curr->isTerminal == 1){
        // printf("THIS IS TERMINAL\n");
        int terminal = (int)curr->NODETYPE->terminal;
        vis[i] = 1;
        FIRSTANDFOLLOWSETS[i][0] = 1;
        FIRSTANDFOLLOWSETS[i][1] = terminal;
        return;
    }

    if (curr->isTerminal == 0){
        vis[i] = 1;
        for (int j = 0; j < numRules; j++){
            if (RULES[j]->NODETYPE->nonterminal == curr->NODETYPE->nonterminal)
            {   
                
                if (vis[j] != 1)
                {
                    // printf("WILL NEED W\n");
                    find(vis, RULES, j, i, curr);
                    
                    vis[j] = 1;
                    
                }

                for (int k = FIRSTANDFOLLOWSETS[i][0] + 1; k <= FIRSTANDFOLLOWSETS[i][0] + FIRSTANDFOLLOWSETS[j][0]; k++)
                {
                    FIRSTANDFOLLOWSETS[i][k] = FIRSTANDFOLLOWSETS[j][k - FIRSTANDFOLLOWSETS[i][0]];
                }
                FIRSTANDFOLLOWSETS[i][0] += FIRSTANDFOLLOWSETS[j][0];
            }
        }
    }

    else{
        if (vis[i] != 2){
            vis[i] = 2;
            // follow();
            // printf("WILL NEED FOLLOW\n");
        }
// printf("WILL NEED FOLLOW\n");
        if (prev_curr && prev_curr->next){
            // printf("prev_curr = %d\n",prev_curr->NODETYPE->nonterminal);
            prev_curr = prev_curr->next;
            if(prev_curr->isTerminal == 1){
                // printf("prev curr is terminal\n");
                // FIRSTANDFOLLOWSETS[prev_curr->NODETYPE->terminal][]
                FIRSTANDFOLLOWSETS[prev_i][FIRSTANDFOLLOWSETS[prev_i][0]] = prev_curr->NODETYPE->terminal;
                FIRSTANDFOLLOWSETS[prev_i][0]++;
                return;
            }
            for(int l = 0 ; l < 119 ; l++){
                // printf("l = %d\n",l);
                if (RULES[l]->NODETYPE->nonterminal == prev_curr->NODETYPE->nonterminal || RULES[l]->NODETYPE->terminal == prev_curr->NODETYPE->terminal){

                    find(vis, RULES, l , prev_i, prev_curr);
                }
                for (int k = FIRSTANDFOLLOWSETS[prev_i][0] + 1; k <= FIRSTANDFOLLOWSETS[prev_i][0] + FIRSTANDFOLLOWSETS[l][0]; k++)
                {
                    FIRSTANDFOLLOWSETS[prev_i][k] = FIRSTANDFOLLOWSETS[l][k - FIRSTANDFOLLOWSETS[prev_i][0]];
                }
                FIRSTANDFOLLOWSETS[prev_i][0] += FIRSTANDFOLLOWSETS[l][0];
        }
    }
}
}
void printFirstFollow(){
    for(int i = 0;i<119;i++){
        int size = FIRSTANDFOLLOWSETS[i][0];
        for(int j = 1;j<=size;j++){
            printf("%d, ",FIRSTANDFOLLOWSETS[i][j]);
        }
        printf("\n");
    }
}
void automateFirstandFollow(LISTNODE* RULES){

    int vis[119];
    int numRules = 119;
    for (int i = 0; i < numRules; i++){
        // LISTNODE curr = RULES[i];
        // curr = curr->next;
        find(vis, RULES, i, -1, NULL);
         
    }
    printf("PRINTING FIRST\n");
    for(int i = 0;i<119;i++){
        int size = FIRSTANDFOLLOWSETS[i][0];
        printf("size = %d, ",size);
        for(int j = 1;j<=size;j++){
            printf("%d, ",FIRSTANDFOLLOWSETS[i][j]);
        }
        printf("\n");
    }
}


// int main(){
//     LISTNODE* RULES = addRules("../../grammar.csv");
//     automateFirstandFollow(RULES);
//     return;
// }
