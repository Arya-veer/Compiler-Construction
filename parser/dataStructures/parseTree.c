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

    return nextNode;
}

void preorderTraversal(TREENODE tn){
    // printf("Traversing\n");
    if(tn == NULL) return;
    if(tn->isTerminal == 1){
        printf("Terminal = %d\n",tn->TREENODEDATA->terminal->token);
    }
    else if(tn->isTerminal == 0){
        printf("Non Terminal = %d\n",tn->TREENODEDATA->nonterminal);
    }
    else{
        printf("EPSILON\n");
    }
    if(tn->child != NULL){
        printf("GOING DOWN\n");
        preorderTraversal(tn->child);
        printf("GOING UP\n");
    }
    if(tn->next != NULL){
        printf("GOING RIGHT\n");
        preorderTraversal(tn->next);
        printf("GOING LEFT\n");
    }
}