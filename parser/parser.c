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

#include "../lexer/lexer.c"
// #include "rules/addRules.c"
#include "parseTable/parseTable.c"
#include "dataStructures/stack.c"
#include "../utils/Buffer/readFile.c"
#include "../utils/Buffer/twinBuffer.c"


void parser(){
    int line = 0;
    addRules("../grammar.csv");
    printf("RULES ADDED\n");
    printRules(119);
    RULES[0]->head->NODETYPE->nonterminal;
    populateParseTable();
    printf("PARSE TABLE POPULATED\n");

    TwinBuffer TB = initializeTwinBuffer("_text.txt");
    printf("TWIN BUFFER INITIALIZED\n");
    STACK st = createStack();
    printf("STACK CREATED\n");
    pushInStack(st,RULES[0]->head);
    LEXEME* lex = simulateDFA(&TB);
    printf("TOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);
    STACKNODE stNode;
    while(lex->token != EOF_TOKEN){
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
            printf("Popped Terminal %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
            if(PARSETABLE[stNode->NODETYPE->nonterminal][lex->token] != -1){
                pushInStack(st,RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->head);
            }
            else{
                printf("ERROR TYPE 2\n");
            }
        }
        else{
            continue;
        }

    }

}


int main(){
    parser();
}