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





void parser(char* grammarFile,char* inputFile){
    short int line = 0;
    LISTNODE* RULES = addRules(grammarFile);
    printf("RULES ADDED\n");
    // printRules(119);
    RULES[0]->NODETYPE->nonterminal;
    populateParseTable(RULES);
    // printParseTable();
    printf("\nPARSE TABLE POPULATED\n");
    TwinBuffer* TB = initializeTwinBuffer(inputFile);
    printf("\nTWIN BUFFER INITIALIZED\n");
    STACK st = createStack();
    printf("\nSTACK CREATED\n");
    pushInStack(st,RULES[0]->next);
    LEXEME* lex = simulateDFA(TB);
    printf("\nTOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);
    STACKNODE stNode;
    while(lex->token != EOF_TOKEN && isStackEmpty(st) == 0){
        stNode = popFromStack(st);
        /* Checking for the terminal */

        if(stNode->isTerminal == 1){
            printf("Popped Terminal %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
            if(lex->token == stNode->NODETYPE->terminal){
                free(lex);
                lex = simulateDFA(TB);
                printf("TOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);

            }
            else{
                printf("ERROR TYPE 1\n");
                break;
            }
        }
        else if(stNode->isTerminal == 0){
            printf("Popped Non Terminal %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal]);
            if(PARSETABLE[stNode->NODETYPE->nonterminal][lex->token] != -1){
                if(RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->next->isTerminal != -1){ 
                    pushInStack(st,RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->next);
                }
            }
            else{
                printf("ERROR TYPE 2\n");
                break;
            }
        }
        free(stNode);


    }   
    fclose(TB->fp);

}


void testAutomation(char* grammarFile){
    LISTNODE* RULES = addRules(grammarFile);
    automateFirstandFollow(RULES);
}

// int main(){
//     parser();
// }