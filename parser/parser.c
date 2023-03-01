#include<stdio.h>
#include<stdlib.h>
#include "parser.h"

int error = 0;

void errorHandling(STACK st,LEXEME* lex,short type,STACKNODE stNode){

    printf("\n \x1B[1m\033[31m PARSING ERROR At line %d, ",lex->lineNo);
    error = 1;
    if(type == 1){
        printf("PARSER GOT INVALID TOKEN \"%s\" , EXPECTED \"%s\"",TERMINALS_STRINGS[lex->token],TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
        

    }
    if(type == 2){
        printf("PARSER GOT INVALID TOKEN \"%s\" ",TOKENS_STRING[lex->token]);

    }
    if(type == 4){
        printf("INPUT IS YET TO BE PROCESSED \"%s\" ",TOKENS_STRING[lex->token]);

    }
    printf("\033[0m\033[0m\n\n");
}


void parser(char* grammarFile,char* inputFile, char* outputFile){
    short int line = 0;
    FILE* output = fopen(outputFile, "w");
    LISTNODE* RULES = addRules(grammarFile);
    // printf("RULES ADDED\n");
    RULES[0]->NODETYPE->nonterminal;
    populateParseTable(RULES);
    // printf("\nPARSE TABLE POPULATED\n");
    TwinBuffer* TB = initializeTwinBuffer(inputFile);
    // printf("\nTWIN BUFFER INITIALIZED\n");
    STACK st = createStack();
    // printf("\nSTACK CREATED\n");
    TREENODE root = createRootNode(RULES[0]);
    pushInStack(st,RULES[0]->next,root,1);
    LEXEME* lex = simulateDFA(TB);
    STACKNODE stNode;
    short canContinue = 0;
    while(st->size > 0){
        stNode = popFromStack(st);
        /* Checking for the terminal */

        if(stNode->isTerminal == 1){
            printf("Popped Terminal %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
            if(lex->token == stNode->NODETYPE->terminal){
                stNode->treenode->TREENODEDATA->terminal = lex;
                lex = simulateDFA(TB);
            }
            else{

                errorHandling(st,lex,1,stNode);
                while(lex->token != SEMICOL_OPERATOR){
                    lex = simulateDFA(TB);
                    if(lex->token == EOF_TOKEN) break;
                }
                if(lex->token == SEMICOL_OPERATOR) canContinue = 1;
                else{ 
                    canContinue = 0;
                    break;
                }
                while(1){
                    stNode = popFromStack(st);
                    // if(stNode->isTerminal == 1) printf("Terminal = %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
                    // else if(stNode->isTerminal == 0) printf("Non Terminal = %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal]);
                    if(stNode->isTerminal == 1 && stNode->NODETYPE->terminal == EOF_TOKEN){
                        while(lex->token != EOF_TOKEN) lex = simulateDFA(TB);
                        stNode->treenode->TREENODEDATA->terminal = lex;
                        canContinue = 0;
                        break;
                    }
                    if(st->top->isTerminal == 1 && (st->top->NODETYPE->terminal == SEMICOL_OPERATOR)) {
                        canContinue = 1;
                        break;
                    }
                }
                if(canContinue == 1){
                    stNode->treenode->TREENODEDATA->terminal = lex;
                    printf("\033[032mERROR RECOVERY DONE\033[0m\n\n");
                    lex = simulateDFA(TB);
                }
                // else break;
            }
        }
        else if(stNode->isTerminal == 0){
            printf("Popped Non Terminal %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->terminal]);
            if(PARSETABLE[stNode->NODETYPE->nonterminal][lex->token] != -1){
                pushInStack(st,RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->next,stNode->treenode,1);
                if(RULES[PARSETABLE[stNode->NODETYPE->nonterminal][lex->token]]->next->isTerminal == -1) stNode = popFromStack(st);
            }
            else{
                errorHandling(st,lex,2,stNode);
                while(lex->token != SEMICOL_OPERATOR){
                    lex = simulateDFA(TB);
                    if(lex->token == EOF_TOKEN) break;
                }
                if(lex->token == SEMICOL_OPERATOR) canContinue = 1;
                else break;
                while(1){
                    stNode = popFromStack(st);
                    if(stNode->isTerminal == 1 && (stNode->NODETYPE->terminal == SEMICOL_OPERATOR)) {
                        canContinue = 1;
                        break;
                    }
                    if(st->size == 0){
                        canContinue = 0;
                        break;
                    }
                    // if(stNode->isTerminal == 0) printf("stNode = %s\n",NONTERMINALS_STRINGS[stNode->NODETYPE->nonterminal]);
                    // else printf("stNode = %s\n",TERMINALS_STRINGS[stNode->NODETYPE->terminal]);
                }
                if(canContinue == 1){
                    stNode->treenode->TREENODEDATA->terminal = lex;
                    printf("\033[032mERROR RECOVERY DONE\033[0m\n");
                    lex = simulateDFA(TB);

                }
                // else break;
            }
        }
        free(stNode);
    }
    lex = simulateDFA(TB);
    if(lex->token != EOF_TOKEN) errorHandling(st,lex,4,stNode);
    else if(error!=1) printf("\nGIVEN SOURCE CODE IS SYNTACTICALLY CORRECT\n\n\n");
    fclose(TB->fp);
    printf("\nPRINTING PARSE TREE\n\n\n");
    inorderTraversal(root,0, output);

}

/*Test Automation using this*/
void testAutomation(char* grammarFile){
    LISTNODE* RULES = addRules(grammarFile);
    automateFirstandFollow(RULES);
}
