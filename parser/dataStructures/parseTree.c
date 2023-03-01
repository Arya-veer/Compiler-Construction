#include<stdio.h>
#include<stdlib.h>
#include "parseTree.h"

TREENODE createRootNode(LISTNODE ln){
    TREENODE root = (TREENODE) malloc(sizeof(struct TreeNode));
    root->child = NULL;
    root->next = NULL;
    root->isTerminal = 0;
    root->TREENODEDATA = (union TreeNodeData*) malloc(sizeof(union TreeNodeData));
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
    if(ln->isTerminal == 0){
        nextNode->TREENODEDATA->nonterminal = ln->NODETYPE->nonterminal;
    }
    else{
        nextNode->TREENODEDATA->terminal = NULL;
    }
    return nextNode;
}

void inorderTraversal(TREENODE tn,short goNext){
    if(tn == NULL) return;
    inorderTraversal(tn->child,0);
    if(tn->isTerminal == 1){
        if(tn->TREENODEDATA->terminal != NULL) printf("Terminal = %s\n",TERMINALS_STRINGS[tn->TREENODEDATA->terminal->token]);
        else printf("Some Terminal Node with Error\n");
    }
    else if(tn->isTerminal == 0){
        printf("Non Terminal = %s\n",NONTERMINALS_STRINGS[tn->TREENODEDATA->nonterminal]);
    }
    else{
        printf("TERMINAL = EPSILON\n");
    }
    if(tn->child != NULL){
        // printf("GOING RIGHT OF CHILD\n");
        inorderTraversal(tn->child->next,1);
        // printf("GOING LEFT TO CHILD\n");
    }
    if(goNext == 1){
        inorderTraversal(tn->next,1);
    }
    
}