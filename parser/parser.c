/*

^   26/02
*REQUIRES:
    &DONE PARSE TABLE                   24/02
    TODO: ERROR HANDLING                25/02
    TODO: PARSE TREE IMPLEMENTATION     26/02
    &LEXER
    &STACK

*/

#include<stdio.h>
#include<stdlib.h>

#include "parser.h"


void parser(){
    int line = 0;
    addRules("../grammar.csv");
    printf("RULES ADDED\n");
    // printRules(119);
    RULES[0]->head->NODETYPE->nonterminal;
    populateParseTable();
    printf("PARSE TABLE POPULATED\n");

    TwinBuffer TB = initializeTwinBuffer("_text.txt");
    printf("TWIN BUFFER INITIALIZED\n");
    STACK st = createStack();
    printf("STACK CREATED\n");
    pushInStack(st,RULES[0]->head->next);
    LEXEME* lex = simulateDFA(&TB);
    printf("TOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);
    STACKNODE stNode;
    while(lex->token != EOF_TOKEN && isStackEmpty(st) == 0){
        stNode = popFromStack(st);
        /* Checking for the terminal */
        // if(isStackEmpty(st) && lex->token == EOF_TOKEN)

        if(stNode->isTerminal == 1){
            printf("Popped Terminal %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
            if(lex->token == stNode->NODETYPE->terminal){
                lex = simulateDFA(&TB);
                printf("TOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);

            }
            else{
                printf("ERROR TYPE 1\n");
                break;
            }
        }
        else if(stNode->isTerminal == 0){
            printf("Popped Non Terminal %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal]);
            printf("Searching for %s,%s in parse table\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal],TERMINALS_STRINGS[lex->token]);
            if(PARSETABLE[stNode->NODETYPE->nonterminal][lex->token] != -1){
                if(RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->head->next->isTerminal == -1){ 
                // printf("Popped Non Terminal %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal]);

                    // stNode = popFromStack(st);
                    // printf("Popped Terminal %s Due to EPSILON\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
                    continue;
                    
                }
                else{
                    pushInStack(st,RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->head->next);
                }
            }
            else{
                printf("ERROR TYPE 2\n");
                break;
            }
        }
        else{
            continue;
        }

    }

}


// int main(){
//     parser();
// }