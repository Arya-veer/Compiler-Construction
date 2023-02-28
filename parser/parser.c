#include<stdio.h>
#include<stdlib.h>
#include "parser.h"


void errorHandiling(STACK st,LEXEME* lex,short type){

    printf("!!!!!!!!!!!!!!!!!!!!!!!\n At line %d, ",lex->lineNo);
    if(type == 1){
        // printf("ERROR OF TYPE 1 OCCURED\n");
        printf("PARSER GOT INVALID TOKEN %s\n",TERMINALS_STRINGS[lex->token]);
        

    }
    if(type == 2){
        printf("ERROR OF TYPE 2 OCCURED\n");
        printf("PARSER CANNOT DERIVE TOKEN %s\n",TERMINALS_STRINGS[lex->token]);

    }
    if(type == 4){
        printf("ERROR OF TYPE 4 OCCURED\n");
        printf("INPUT IS YET TO BE PROCESSED %s\n",TERMINALS_STRINGS[lex->token]);

    }
}


void parser(char* grammarFile,char* inputFile){
    short int line = 0;
    LISTNODE* RULES = addRules(grammarFile);
    printf("RULES ADDED\n");
    RULES[0]->NODETYPE->nonterminal;
    populateParseTable(RULES);
    printf("\nPARSE TABLE POPULATED\n");
    TwinBuffer* TB = initializeTwinBuffer(inputFile);
    printf("\nTWIN BUFFER INITIALIZED\n");
    STACK st = createStack();
    printf("\nSTACK CREATED\n");
    TREENODE root = createRootNode(RULES[0]);
    pushInStack(st,RULES[0]->next,root,1);
    LEXEME* lex = simulateDFA(TB);
    // printf("\nTOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);
    STACKNODE stNode;
    while(st->size > 0){
        // printf("SIZE OF STACK IS %d\n",st->size);
        stNode = popFromStack(st);
        /* Checking for the terminal */

        if(stNode->isTerminal == 1){
            printf("Popped Terminal %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
            if(lex->token == stNode->NODETYPE->terminal){
                stNode->treenode->TREENODEDATA->terminal = lex;
                // printf("LEAF NODE ADDED\n");
                lex = simulateDFA(TB);
                // printf("TOKEN GIVEN BY DFA IS %s\n",TERMINALS_STRINGS[lex->token]);

            }
            else{
                errorHandiling(st,lex,1);
                break;
            }
        }
        else if(stNode->isTerminal == 0){
            printf("Popped Non Terminal %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal]);
            if(PARSETABLE[stNode->NODETYPE->nonterminal][lex->token] != -1){
                if(RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->next->isTerminal != -1){ 
                    pushInStack(st,RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->next,stNode->treenode,1);
                }
            }
            else{
                errorHandiling(st,lex,2);

                break;
            }
        }
        free(stNode);


    }
    lex = simulateDFA(TB);
    if(lex->token != EOF_TOKEN){
        errorHandiling(st,lex,4);
    }
    fclose(TB->fp);
    // stNode = popFromStack(st);
    // printf("STACK BOTTOM IS %d %d\n",stNode->isTerminal,stNode->NODETYPE->nonterminal);
    // if(lex->token == stNode->NODETYPE->terminal){
    //     stNode->treenode->TREENODEDATA->terminal = lex;
    //     printf("LEAF NODE ADDED\n");

    // }
    // else{
    //     printf("ERROR TYPE 4\n");
    // }
    // printf("\nPRINTING PARSE TREE\n");
    // preorderTraversal(root);

}


void testAutomation(char* grammarFile){
    LISTNODE* RULES = addRules(grammarFile);
    automateFirstandFollow(RULES);
}

// int main(){
//     parser();
// }