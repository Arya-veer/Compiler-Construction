#include<stdio.h>
#include<stdlib.h>

#include "../rules/addRules.c"
int FIRSTANDFOLLOWSETS[119][20]; 

void follow(){
    for(int j = 0 ; j < numRules ; j++){
        LISTNODE temp = RULES[j] -> head;
        temp = temp ->next;
        while(temp){
            if(temp->NODETYPE->nonterminal == RULES[i] -> head ->NODETYPE -> nonterminal){
                if(temp->next)LISTNODE help = temp->next;
               for(int k = FIRSTANDFOLLOWSETS[i][0]+1 ; k <= FIRSTANDFOLLOWSETS[i][0] + FIRSTANDFOLLOWSETS[j][0] ; k++){
                    FIRSTANDFOLLOWSETS[i][k] = FIRSTANDFOLLOWSETS[j][k - FIRSTANDFOLLOWSETS[i][0]];
            }
        }
    }
}

void find(int *vis,LINKEDLIST *RULES, int i , int prev_i , LISTNODE* prev_curr){
      if(vis[i] == 1){
        return;
      }
        
        int numRules = 119;
        LISTNODE curr = RULES[i]->head;
        curr = curr->next;
        
        if(curr->isTerminal == 1){
            int terminal = (int)curr->NODETYPE->terminal;
            vis[i] = 1;
            FIRSTANDFOLLOWSETS[i][0] = 1;
            FIRSTANDFOLLOWSETS[i][1] = terminal;
            return;
        }
        
        if(curr->isTerminal == 0){
            vis[i] = 1;
            for(int j = 0 ; j < numRules ; j++){
                if(RULES[j]->head->NODETYPE->nonterminal == curr->NODETYPE->nonterminal){
                    if(vis[j] == 0){
                    find(vis, RULES , j , i  , curr);
                }
                
                for(int k = FIRSTANDFOLLOWSETS[i][0]+1 ; k <= FIRSTANDFOLLOWSETS[i][0] + FIRSTANDFOLLOWSETS[j][0] ; k++){
                    FIRSTANDFOLLOWSETS[i][k] = FIRSTANDFOLLOWSETS[j][k - FIRSTANDFOLLOWSETS[i][0]];
                }
                FIRSTANDFOLLOWSETS[i][0] += FIRSTANDFOLLOWSETS[j][0];
            }
        }
    }

        else{ 
            if(vis[i] != 2){
                vis[i] = 2;
                follow();
            }
            
            if(prev_curr-> next){
            prev_curr = prev_curr->next;
            find(vis , RULES , prev_i , prev_i , prev_curr);
        }  
}


void automateFirstandFollow(){
    
    int vis[119];
    int numRules = 119;
    for(int i = 0;i<numRules;i++){
        LISTNODE curr = RULES[i]->head;
        curr = curr->next;
        find(vis , RULES , i , -1 , NULL);
    }
}



int main(){
   
}
