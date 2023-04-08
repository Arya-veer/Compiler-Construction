#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbolTable.h"

int SYMTABSIZE = 59;
int FOR_ROW = 60;
int WHILE_ROW = 61; 
int SWITCH_ROW = 62; 
int CASE_ROW = 63; 
int OFFSETS[] = {4,4,1};




void printLinkedListST(SYMBOLTABLEROW row){
    if(row == NULL) return;
    if(row->id->token == IDENTIFIER_TOKEN)printf("%s %d ",row->id->lexemedata->data,row->type);
    else if(row->id->token == NUM_TOKEN)printf("%d %d ",row->id->lexemedata->intData,row->type);
    if(row->isDynamic == -1) printf("0\n");
    else printf("1\n");
    printLinkedListST(row->next);
}

void printTable(SYMBOLTABLE SYMBOL_TABLE){
    for(int i = 0;i<(SYMTABSIZE+5);i++){
        printf("\n%d: ",i);
        printLinkedListST(SYMBOL_TABLE->TABLE[i]);
    }
    printf("\n\n\n");
}

void printSymbolTable(SYMBOLTABLEROW func){
    // printf("%ld\n\n",SYMBOLTABLE);
    printf("\n\nPRINTING SYMBOL TABLE FOR FUNCTION %s\n\n",func->id->lexemedata->data);
    for(int i = 0;i<(SYMTABSIZE+5);i++){
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


SYMBOLTABLE initializeSymbolTable(char* name){
    SYMBOLTABLEROW* TABLE = (SYMBOLTABLEROW*) malloc((SYMTABSIZE+5)*sizeof(SYMBOLTABLEROW));
    for(int i = 0;i<(SYMTABSIZE+5);i++){
        // SYMBOLTABLEROW str = malloc(sizeof(struct SymTabRowNode));
        TABLE[i] = NULL;
        // TABLE[i] = NULL;
    }
    SYMBOLTABLE st = malloc(sizeof(struct SymbolTable));
    st->TABLE = TABLE;
    st->currOffset = 0;
    st->name = name;
    st->parent = NULL;
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
            printf("LINE %d: VARIABLE ALREADY DEFINED %s\n",var->TREENODEDATA->terminal->lineNo, var->TREENODEDATA->terminal->lexemedata->data);
            return;
        }
        str = str->next;
    }
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    row->id = var->TREENODEDATA->terminal;
    row->offset = SYMBOL_TABLE->currOffset;
    SYMBOL_TABLE->currOffset += OFFSETS[var->type];
    row->type = var->type;
    row->range = NULL;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMSHEAD = NULL;
    row->OUTPUTPARAMSHEAD = NULL;
    row->next = NULL;
    row->isDynamic = -1; 
    if(var->isArray == 1){
        row->isDynamic = 0; 
        ARRRANGE aR = malloc(sizeof(struct arrRange));
        row->range = aR;
        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            row->range = NULL;
            row->isDynamic = 1; 

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
            printf("LINE %d: THIS MODULE HAS ALREADY BEEN DEFINED\n",func->TREENODEDATA->terminal->lineNo);
            return NULL;
        }
        else{
            return str;
        }
    }


}

SYMBOLTABLEROW StoreForIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE FOR){
    int index = FOR_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    row->id = FOR->TREENODEDATA->terminal;
    row->type = TYPE_UNDEFINED;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMSHEAD = NULL;
    row->OUTPUTPARAMSHEAD = NULL;
    row->next = NULL;
    if(str == NULL){ 
        SYMBOL_TABLE->TABLE[index] = row;
    }
    else{
        while(str->next != NULL) str = str->next;
        str->next= row;
    }

    return row;
}

SYMBOLTABLEROW StoreWhileIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE WHILE){
    int index = WHILE_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    row->id = WHILE->TREENODEDATA->terminal;
    row->type = TYPE_UNDEFINED;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMSHEAD = NULL;
    row->OUTPUTPARAMSHEAD = NULL;
    row->next = NULL;
    if(str == NULL){ 
        SYMBOL_TABLE->TABLE[index] = row;
    }
    else{
        while(str->next != NULL) str = str->next;
        str->next= row;
    }

    return row;
}

SYMBOLTABLEROW StoreSwitchIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE SWITCH){
    int index = SWITCH_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    row->id = SWITCH->TREENODEDATA->terminal;
    row->type = TYPE_UNDEFINED;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMSHEAD = NULL;
    row->OUTPUTPARAMSHEAD = NULL;
    row->next = NULL;
    if(str == NULL){ 
        SYMBOL_TABLE->TABLE[index] = row;
    }
    else{
        while(str->next != NULL) str = str->next;
        str->next= row;
    }

    return row;
}

SYMBOLTABLEROW StoreCaseIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE CASE){
    int index = CASE_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    SYMBOLTABLEROW row = malloc(sizeof(struct SymTabRowNode));
    row->id = CASE->TREENODEDATA->terminal;
    row->type = TYPE_UNDEFINED;
    row->SYMBOLTABLE = NULL;
    row->INPUTPARAMSHEAD = NULL;
    row->OUTPUTPARAMSHEAD = NULL;
    row->next = NULL;
    if(str == NULL){ 
        SYMBOL_TABLE->TABLE[index] = row;
    }
    else{
        while(str->next != NULL) str = str->next;
        str->next= row;
    }

    return row;
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
    if(SYMBOL_TABLE == NULL || SYMBOL_TABLE->parent == NULL || var == NULL) return NULL;
    SYMBOLTABLEROW func = GetFuncFromName(SYMBOL_TABLE->parent,SYMBOL_TABLE->name);
    int index;
    SYMBOLTABLEROW str;
    index = hashCodeSymbolTable(var->TREENODEDATA->terminal->lexemedata->data);
    str = SYMBOL_TABLE->TABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    if(func == NULL || func->INPUTPARAMSHEAD == NULL){ 
        if(SYMBOL_TABLE->parent == NULL) return NULL;
        // printf("PARENT ME LENE JA RHA HU\n\n");
        // printTable(SYMBOL_TABLE->parent);
        return GetVarFromSymbolTable(SYMBOL_TABLE->parent,var);
    }
    str = func->INPUTPARAMSHEAD;
    while(str!=NULL){
        // printf("%s\n\n",str->id->lexemedata->data);
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    // printf("INPUT ME YE HAI NHI\n\n");
    if(func->OUTPUTPARAMSHEAD == NULL){ 
        if(SYMBOL_TABLE->parent == NULL) return NULL;
        return GetVarFromSymbolTable(SYMBOL_TABLE->parent,var);
    }
    str = func->OUTPUTPARAMSHEAD;
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            return str;
        }
        str = str->next;
    }
    if(SYMBOL_TABLE->parent == NULL) return NULL;
    return GetVarFromSymbolTable(SYMBOL_TABLE->parent,var);
}

SYMBOLTABLEROW GetFuncFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE, TREENODE func){
    return GetFuncFromName(SYMBOL_TABLE,func->TREENODEDATA->terminal->lexemedata->data);
}


SYMBOLTABLEROW StoreVarAsInputParam(SYMBOLTABLEROW IP,TREENODE var){
    IP = malloc(sizeof(struct SymTabRowNode));
    IP->id = var->TREENODEDATA->terminal;
    IP->type = var->type;
    IP->SYMBOLTABLE = NULL;
    IP->INPUTPARAMSHEAD = NULL;
    IP->OUTPUTPARAMSHEAD = NULL;
    IP->next = NULL;
    IP->range = NULL;
    IP->isDynamic = -1;
    TREENODE range = var->left_child->right_child;
    if(range != NULL){
        IP->isDynamic = 0;
        ARRRANGE aR = malloc(sizeof(struct arrRange));
        IP->range = aR;

        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            IP->range = NULL;
            IP->isDynamic = 1;
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
            if(IP->range->left > IP->range->right){
                printf("LINE %d: LEFT RANGE MUST BE SMALLER THAN RIGHT RANGE\n\n",var->TREENODEDATA->terminal->lineNo);
            }
        }
    }
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
    OP->isDynamic = -1;
    if(var->isArray == 1){
        ARRRANGE aR = malloc(sizeof(struct arrRange));
        OP->range = aR;
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