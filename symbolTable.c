#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbolTable.h"

int SYMTABSIZE = 59;

SYMBOLTABLEROW* initializeSymbolTable(){
    SYMBOLTABLEROW* SYMBOLTABLE = (SYMBOLTABLEROW*) malloc(SYMTABSIZE*sizeof(SYMBOLTABLEROW));
    for(int i = 0;i<SYMTABSIZE;i++){
        // SYMBOLTABLEROW str = malloc(sizeof(struct SymTabRowNode));
        SYMBOLTABLE[i] = NULL;
        // SYMBOLTABLE[i] = NULL;
    }
    return SYMBOLTABLE;
}


int hashCodeSymbolTable(char* str){
    // printf("GETTING HASH\n");
    // printf("GETTING HASH\n");
    int num=2;
    int k=SYMTABSIZE;
    int product=0;

    for(int i=0;i<strlen(str);i++){
        product=product*num+str[i];
    }

    product=product%k;
    // printf("HASH = %d\n",product);
    // printf("HASH = %d\n",product);
    return product;
}


void StoreVarIntoSymbolTable(SYMBOLTABLEROW* SYMBOLTABLE,TREENODE var){
    // printf("\n\nMAI HU: %ld\n\n",SYMBOLTABLE);
    
    // printf("STORING VARIABLE IN SYMBOL TABLE\n\n");
    // printf("%s\n\n",var->TREENODEDATA->terminal->lexemedata->data);
    // printf("STORING VARIABLE IN SYMBOL TABLE\n\n");
    int index = hashCodeSymbolTable(var->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOLTABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            printf("VARIABLE ALREADY DEFINED %s\n",var->TREENODEDATA->terminal->lexemedata->data);
            return;
        }
        str = str->next;
    }
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    // printf("IJDOFJ\n");
    // printf("IJDOFJ\n");
    // printf("IJDOFJ\n");
    row->id = var->TREENODEDATA->terminal;
    row->type = var->type;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMS = NULL;
    row->OUTPUTPARAMS = NULL;
    row->next = NULL;
    if(var->isArray == 1){
        row->range = malloc(sizeof(struct arrRange));
        TREENODE range = var->left_child->right_child;
        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            row->range = NULL;
        }
        else{
            if(range->left_child->left_child == NULL || range->left_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                row->range->left = range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                row->range->left = -1*range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            if(range->right_child->left_child == NULL || range->right_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                row->range->right = range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                row->range->right = -1*range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
        }
    }
    if(SYMBOLTABLE[index] == NULL){

        SYMBOLTABLE[index] = row;
    }
    else{
        SYMBOLTABLEROW str = SYMBOLTABLE[index];
        while(str->next != NULL){
            str = str->next;
        }
        str->next = row;
    }
}

SYMBOLTABLEROW StoreFuncIntoSymbolTable(SYMBOLTABLEROW* SYMBOLTABLE,TREENODE func){
    int index = hashCodeSymbolTable(func->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOLTABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,func->TREENODEDATA->terminal->lexemedata->data) == 0){
            break;
        }
        str = str->next;
    }
    if(str == NULL){
        SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
        row->id = func->TREENODEDATA->terminal;
        row->type = TYPE_UNDEFINED;
        row->SYMBOLTABLE = NULL;
        row->INPUTPARAMS = NULL;
        row->OUTPUTPARAMS = NULL;
        row->next = NULL;
        // printf("RETURNING ROW\n");
        SYMBOLTABLE[index] = row;
        return row;
    }
    else{
        if(str->INPUTPARAMS != NULL){
            printf("THIS MODULE HAS ALREADY BEEN DEFINED\n");
            return NULL;
        }
        else{
            return str;
        }
    }

}

SYMBOLTABLEROW GetVarFromSymbolTable(SYMBOLTABLEROW* SYMBOLTABLE, TREENODE var){
    int index = hashCodeSymbolTable(var->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOLTABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    return NULL;
}

SYMBOLTABLEROW GetFuncFromSymbolTable(SYMBOLTABLEROW* SYMBOLTABLE, TREENODE func){
    int index = hashCodeSymbolTable(func->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOLTABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,func->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        else{
            return NULL;
        }
        str = str->next;
    }
}

void printLinkedListST(SYMBOLTABLEROW row){
    if(row == NULL) return;
    printf("%s\n",row->id->lexemedata->data);
    printLinkedListST(row->next);
}

void printSymbolTable(SYMBOLTABLEROW* SYMBOLTABLE){
    // printf("%ld\n\n",SYMBOLTABLE);
    printf("\n\nPRINTING SYMBOL TABLE\n\n");
    for(int i = 0;i<SYMTABSIZE;i++){
        printf("\n%d: ",i);
        printLinkedListST(SYMBOLTABLE[i]);
    }
    printf("\n\nENDING PRINTING\n\n");
}