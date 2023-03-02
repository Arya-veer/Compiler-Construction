#include<stdio.h>
#include<stdlib.h>
#include "parseTree.h"

TREENODE createRootNode(LISTNODE ln){
    TREENODE root = (TREENODE) malloc(sizeof(struct TreeNode));
    root->child = NULL;
    root->next = NULL;
    root->isTerminal = 0;
    root->TREENODEDATA = (union TreeNodeData*) malloc(sizeof(union TreeNodeData));
    root->parent = NULL;
    if(ln->isTerminal == 0){
        root->TREENODEDATA->nonterminal = ln->NODETYPE->nonterminal;
    }
    return root;
}

TREENODE insertChildTree(TREENODE tn, LISTNODE ln){
    TREENODE childHead = (TREENODE) malloc(sizeof(struct TreeNode));
    tn->child = childHead;
    childHead->next = NULL;
    childHead->child = NULL;
    childHead->isTerminal = ln->isTerminal;
    childHead->TREENODEDATA = (union TreeNodeData*) malloc(sizeof(union TreeNodeData));
    childHead->parent = tn;
    if(ln->isTerminal == 0){
        childHead->TREENODEDATA->nonterminal = ln->NODETYPE->nonterminal;
    }
    else{
        childHead->TREENODEDATA->terminal = NULL;
    }
    return childHead;
}

TREENODE insertNextTree(TREENODE tn, LISTNODE ln){
    TREENODE nextNode = (TREENODE) malloc(sizeof(struct TreeNode));
    tn->next = nextNode;
    nextNode->next = NULL;
    nextNode->child = NULL;
    nextNode->isTerminal = ln->isTerminal;
    nextNode->TREENODEDATA = (union TreeNodeData*) malloc(sizeof(union TreeNodeData));
    nextNode->parent = tn->parent;
    if(ln->isTerminal == 0){
        nextNode->TREENODEDATA->nonterminal = ln->NODETYPE->nonterminal;
    }
    else{
        nextNode->TREENODEDATA->terminal = NULL;
    }
    return nextNode;
}

void inorderTraversal(TREENODE tn, short goNext, FILE* outputFile){
    if(tn == NULL) return;
    inorderTraversal(tn->child,0, outputFile);
    if(tn->isTerminal == 1){
        // printf("T\n");
        if(tn->TREENODEDATA->terminal != NULL){ 
            if(tn->TREENODEDATA->terminal->token == EOF_TOKEN) return;
            if(tn->TREENODEDATA->terminal->token != NUM_TOKEN || tn->TREENODEDATA->terminal->token != RNUM_TOKEN || tn->TREENODEDATA->terminal->token != IDENTIFIER_TOKEN)fprintf(outputFile, "       %s     ",TOKENS_STRING[tn->TREENODEDATA->terminal->token]);
            else if(tn->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) fprintf(outputFile, "       %s     ",tn->TREENODEDATA->terminal->lexemedata->data);
            else if(tn->TREENODEDATA->terminal->token == RNUM_TOKEN) fprintf(outputFile, "       %f     ",tn->TREENODEDATA->terminal->lexemedata->floatData);
            else if(tn->TREENODEDATA->terminal->token == NUM_TOKEN) fprintf(outputFile, "       %d     ",tn->TREENODEDATA->terminal->lexemedata->intData);
            fprintf(outputFile, "       %d     ",tn->TREENODEDATA->terminal->lineNo);
            fprintf(outputFile, "       %s     ",TERMINALS_STRINGS[tn->TREENODEDATA->terminal->token]);
            if(tn->TREENODEDATA->terminal->token == NUM_TOKEN){
                fprintf(outputFile, "       %d     ",tn->TREENODEDATA->terminal->lexemedata->intData);
            }
            else if(tn->TREENODEDATA->terminal->token == RNUM_TOKEN){
                fprintf(outputFile, "       %lf     ",tn->TREENODEDATA->terminal->lexemedata->floatData);
            }
            if(tn->parent) fprintf(outputFile, "%s      ",NONTERMINALS_STRINGS[tn->parent->TREENODEDATA->nonterminal]);
            else fprintf(outputFile, "%s    ","ROOT");
            fprintf(outputFile,"YES\n\n");
        }
        else fprintf(outputFile,"Some Terminal Node with Error\n");
    }
    else if(tn->isTerminal == 0){
        // fprintf(outputFile,"NT\n");
        fprintf(outputFile, "       ----------     ");
        fprintf(outputFile, "       %s     ",NONTERMINALS_STRINGS[tn->TREENODEDATA->nonterminal]);
        if(tn->parent) fprintf(outputFile, "        %s      ",NONTERMINALS_STRINGS[tn->parent->TREENODEDATA->nonterminal]);
        else fprintf(outputFile, "      %s\t      ","ROOT");
        fprintf(outputFile,"NO\n\n");
    }
    else{
        fprintf(outputFile,"       epsilon     epsilon");
        if(tn->parent) fprintf(outputFile, "        %s      ",NONTERMINALS_STRINGS[tn->parent->TREENODEDATA->nonterminal]);
        else fprintf(outputFile, "      %s\t      ","ROOT");
        fprintf(outputFile,"YES\n\n");
    }
    if(tn->child != NULL){
        // printf("GOING RIGHT OF CHILD\n");
        inorderTraversal(tn->child->next,1, outputFile);
        // printf("GOING LEFT TO CHILD\n");
    }
    if(goNext == 1){
        inorderTraversal(tn->next, 1, outputFile);
    }
    
}

