#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbolTable.h"

int SYMTABSIZE = 59;

SYMBOLTABLE initializeSymbolTable(char* name){
    SYMBOLTABLEROW* TABLE = (SYMBOLTABLEROW*) malloc(SYMTABSIZE*sizeof(SYMBOLTABLEROW));
    for(int i = 0;i<SYMTABSIZE;i++){
        // SYMBOLTABLEROW str = malloc(sizeof(struct SymTabRowNode));
        TABLE[i] = NULL;
        // TABLE[i] = NULL;
    }
    SYMBOLTABLE st = malloc(sizeof(struct SymbolTable));
    st->TABLE = TABLE;
    st->currOffset = 0;
    st->name = name;
    return st;
}


int hashCodeSymbolTable(char* str){
    int num=2;
    int k=SYMTABSIZE;
    int product=0;
    for(int i=0;i<strlen(str);i++){
        product=product*num+str[i];
    }
    product=product%k;
    return product;
}


void StoreVarIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE var,TREENODE range){
    
    int index = hashCodeSymbolTable(var->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            printf("VARIABLE ALREADY DEFINED %s\n",var->TREENODEDATA->terminal->lexemedata->data);
            return;
        }
        str = str->next;
    }
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    row->id = var->TREENODEDATA->terminal;
    row->type = var->type;
    row->range = NULL;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMSHEAD = NULL;
    row->OUTPUTPARAMSHEAD = NULL;
    row->next = NULL;
    if(var->isArray == 1){
        printf("ARRAY %s getting stored in SYMBOL TABLE\n\n",row->id->lexemedata->data);
        ARRRANGE aR = malloc(sizeof(struct arrRange));
        row->range = aR;
        printf("%s\n",range->TREENODEDATA->terminal->lexemedata->data);
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
    else{
        row->range = NULL;
    }

    if(SYMBOL_TABLE->TABLE[index] == NULL){

        SYMBOL_TABLE->TABLE[index] = row;

    }
    else{

        SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
        while(str->next != NULL){
            str = str->next;
        }
        str->next = row;
    }

}

SYMBOLTABLEROW StoreFuncIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE func){
    int index = hashCodeSymbolTable(func->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
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
        row->INPUTPARAMSHEAD = NULL;
        row->OUTPUTPARAMSHEAD = NULL;
        row->next = NULL;
        // printf("RETURNING ROW\n");
        SYMBOL_TABLE->TABLE[index] = row;

        return row;
    }
    else{
        if(str->INPUTPARAMSHEAD != NULL){
            printf("THIS MODULE HAS ALREADY BEEN DEFINED\n");
            return NULL;
        }
        else{
            return str;
        }
    }

}


SYMBOLTABLEROW GetFuncFromName(SYMBOLTABLE SYMBOL_TABLE, char* func){
    int index = hashCodeSymbolTable(func);
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,func) == 0){
            return str;
        }
        str = str->next;
    }
    return NULL;
}

SYMBOLTABLEROW GetVarFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE, TREENODE var){
    SYMBOLTABLEROW func = GetFuncFromName(SYMBOL_TABLE->parent,SYMBOL_TABLE->name);
    int index;
    SYMBOLTABLEROW str;
    index = hashCodeSymbolTable(var->TREENODEDATA->terminal->lexemedata->data);
    str = func->SYMBOLTABLE->TABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    // printf("DECLARE YE HUA NHI\n\n");
    if(func->INPUTPARAMSHEAD == NULL) return NULL;
    str = func->INPUTPARAMSHEAD;
    while(str!=NULL){
        // printf("%s\n\n",str->id->lexemedata->data);
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    // printf("INPUT ME YE HAI NHI\n\n");
    if(func->OUTPUTPARAMSHEAD == NULL) return NULL;
    str = func->OUTPUTPARAMSHEAD;
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    return NULL;
}

SYMBOLTABLEROW GetFuncFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE, TREENODE func){
    return GetFuncFromName(SYMBOL_TABLE,func->TREENODEDATA->terminal->lexemedata->data);
}


void printLinkedListST(SYMBOLTABLEROW row){
    if(row == NULL) return;
    printf("%s %d ",row->id->lexemedata->data,row->type);
    if(row->range == NULL) printf("0\n");
    else printf("1\n");
    printLinkedListST(row->next);
}

void printSymbolTable(SYMBOLTABLEROW func){
    // printf("%ld\n\n",SYMBOLTABLE);
    printf("\n\nPRINTING SYMBOL TABLE FOR FUNCTION %s\n\n",func->id->lexemedata->data);
    for(int i = 0;i<SYMTABSIZE;i++){
        printf("\n%d: ",i);
        printLinkedListST(func->SYMBOLTABLE->TABLE[i]);
    }
    printf("\n\nENDING PRINTING\n\n");
    if(func->INPUTPARAMSHEAD == NULL) return;
    printf("\n\nPRINTING INPUT TABLE FOR FUNCTION %s\n\n",func->id->lexemedata->data);
    printLinkedListST(func->INPUTPARAMSHEAD);
    if(func->OUTPUTPARAMSHEAD == NULL) return;
    printf("\n\nPRINTING OUTPUT TABLE FOR FUNCTION %s\n\n",func->id->lexemedata->data);
    printLinkedListST(func->OUTPUTPARAMSHEAD);
}

SYMBOLTABLEROW StoreVarAsInputParam(SYMBOLTABLEROW IP,TREENODE var){
    IP = malloc(sizeof(struct SymTabRowNode));
    IP->id = var->TREENODEDATA->terminal;
    IP->type = var->type;
    IP->SYMBOLTABLE = NULL;
    IP->INPUTPARAMSHEAD = NULL;
    IP->OUTPUTPARAMSHEAD = NULL;
    IP->next = NULL;
    if(var->isArray == 1){
        IP->range = malloc(sizeof(struct arrRange));
        TREENODE range = var->left_child->right_child;
        printf("ARRAY %s getting stored in INPUT TABLE\n\n",IP->id->lexemedata->data);
        printf("%s\n",range->TREENODEDATA->terminal->lexemedata->data);

        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            IP->range = NULL;
        }
        else{
            if(range->left_child->left_child == NULL || range->left_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                IP->range->left = range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                IP->range->left = -1*range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            if(range->right_child->left_child == NULL || range->right_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                IP->range->right = range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                IP->range->right = -1*range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
        }
    }
    printf("INPUT PARAMS LIST KA VAR ASSIGNED\n\n");
    return IP;
}

SYMBOLTABLEROW StoreVarAsOutputParam(SYMBOLTABLEROW OP,TREENODE var){
    OP = malloc(sizeof(struct SymTabRowNode));
    OP->id = var->TREENODEDATA->terminal;
    OP->type = var->type;

    OP->SYMBOLTABLE = NULL;
    OP->INPUTPARAMSHEAD = NULL;
    OP->OUTPUTPARAMSHEAD = NULL;
    OP->next = NULL;
    if(var->isArray == 1){
        OP->range = malloc(sizeof(struct arrRange));
        TREENODE range = var->left_child->right_child;
        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            OP->range = NULL;
        }
        else{
            if(range->left_child->left_child == NULL || range->left_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                OP->range->left = range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                OP->range->left = -1*range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            if(range->right_child->left_child == NULL || range->right_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                OP->range->right = range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                OP->range->right = -1*range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
        }
    }
    else{
        OP->range = NULL;
    }
    return OP;
}