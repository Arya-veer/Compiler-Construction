//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbolTable.h"

int SYMTABSIZE = 59;
int FOR_ROW = 60;
int WHILE_ROW = 61; 
int SWITCH_ROW = 62; 
int CASE_ROW = 63; 
int FOR_VAR = 64;
int WHILE_VAR = 65;
int OFFSETS[] = {2,4,1};
int OFFSET = 0;



int getWidth(SYMBOLTABLEROW str,int isParam){
    int width;
    width = OFFSETS[str->type];
    if(isParam == 1 && str->isDynamic != -1) return 1 + 2*OFFSETS[str->type];
    if(str->isDynamic == 0){
        width = width*(str->range->rightVal - str->range->leftVal + 1) + 1;
    }
    else if(str->isDynamic == 1) return 1;
    // printf("WIDTH OF %s is %d\n\n",str->id->lexemedata->data,width);
    return width;
}


void printLinkedListST(SYMBOLTABLEROW row){
    if(row == NULL) return;
    if(row->id->token == IDENTIFIER_TOKEN)printf("%s %d ",row->id->lexemedata->data,row->type);
    else if(row->id->token == NUM_TOKEN)printf("%d %d ",row->id->lexemedata->intData,row->type);
    else printf("%s %d ",row->id->lexemedata->data,row->type);
    // if(row->isDynamic == -1
    printf("%d \n\n",row->isDynamic);
    printLinkedListST(row->next);
}

void printTable(SYMBOLTABLE SYMBOL_TABLE){
    for(int i = 0;i<(SYMTABSIZE+10);i++){
        printf("\n%d: ",i);
        printLinkedListST(SYMBOL_TABLE->TABLE[i]);
    }
    printf("\n\n\n");
}

void printSymbolTable(SYMBOLTABLEROW func){
    // printf("%ld\n\n",SYMBOLTABLE);
    printf("\n\nPRINTING SYMBOL TABLE FOR FUNCTION %s\n\n",func->id->lexemedata->data);
    for(int i = 0;i<(SYMTABSIZE+10);i++){
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


SYMBOLTABLEROW copy(SYMBOLTABLEROW old_row){
    SYMBOLTABLEROW new_row = malloc(sizeof(struct SymTabRowNode));
    new_row->id = old_row->id;
    new_row->INPUTPARAMSHEAD = old_row->INPUTPARAMSHEAD;
    new_row->isDynamic = old_row->isDynamic;
    new_row->next = NULL;
    new_row->offset = old_row->offset;
    new_row->OUTPUTPARAMSHEAD = old_row->OUTPUTPARAMSHEAD;
    new_row->range = old_row->range;
    new_row->SYMBOLTABLE = old_row->SYMBOLTABLE;
    new_row->type = old_row->type;
    return new_row;
}

SYMBOLTABLE initializeSymbolTable(char* name,int first,int last){
    SYMBOLTABLEROW* TABLE = (SYMBOLTABLEROW*) malloc((SYMTABSIZE+10)*sizeof(SYMBOLTABLEROW));
    for(int i = 0;i<(SYMTABSIZE+10);i++){
        // SYMBOLTABLEROW str = malloc(sizeof(struct SymTabRowNode));
        TABLE[i] = NULL;
        // TABLE[i] = NULL;
    }
    SYMBOLTABLE st = malloc(sizeof(struct SymbolTable));
    st->TABLE = TABLE;
    st->currOffset = OFFSET;
    st->name = name;
    st->parent = NULL;
    st->first = first;
    st->last = last;
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


SYMBOLTABLEROW StoreVarIntoSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE var,TREENODE range){
    
    int index = hashCodeSymbolTable(var->TREENODEDATA->terminal->lexemedata->data);
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    while(str!=NULL){
        if(strcmp(str->id->lexemedata->data,var->TREENODEDATA->terminal->lexemedata->data) == 0){
            printf("LINE %d: VARIABLE '%s' ALREADY DECLARED \n",var->TREENODEDATA->terminal->lineNo, var->TREENODEDATA->terminal->lexemedata->data);
            return NULL;
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
    row->isDynamic = -1; 
    if(var->isArray == 1){
        row->isDynamic = 0; 
        ARRRANGE aR = malloc(sizeof(struct arrRange));
        row->range = aR;
        row->range->left = range->left_child;
        row->range->right = range->right_child;
        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            row->isDynamic = 1; 
            row->offset = OFFSET;
            OFFSET+=1;
        }
        else{
            row->offset = OFFSET;
            if(range->left_child->left_child == NULL || range->left_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                row->range->leftVal = range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                row->range->leftVal = -1*range->left_child->TREENODEDATA->terminal->lexemedata->intData;

            }
            if(range->right_child->left_child == NULL || range->right_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                row->range->rightVal = range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                row->range->rightVal = -1*range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            OFFSET += OFFSETS[var->type]*(row->range->rightVal-row->range->leftVal + 1) + 1;
        }
        if(range->left_child->left_child != NULL){
            row->range->leftSign = range->left_child->left_child->TREENODEDATA->terminal->lexemedata->data;
        }
        else{
            row->range->leftSign = NULL;
        }
        if(range->right_child->left_child != NULL){
            row->range->rightSign = range->right_child->left_child->TREENODEDATA->terminal->lexemedata->data;
        }
        else{
            row->range->rightSign = NULL;
        }
    }
    else{
            row->offset = OFFSET;
            OFFSET += OFFSETS[var->type];
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
    return row;
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
        row->isDynamic = 0;

        // printf("RETURNING ROW\n");
        str = SYMBOL_TABLE->TABLE[index];
        if(str == NULL) SYMBOL_TABLE->TABLE[index] = row;
        else{
            while(str->next != NULL){
                str = str->next;
            }
            str->next = row;
        }

        return row;
    }
    else{
        if(str->INPUTPARAMSHEAD != NULL){
            printf("LINE %d: FUNCTION %s OVERLOADING IS NOT ALLOWED\n\n",func->TREENODEDATA->terminal->lineNo,func->TREENODEDATA->terminal->lexemedata->data);
            return NULL;
        }
        else{
            if(str->isDynamic == 0){
                printf("LINE %d: FUNCTION IS DECLARED AND DEFINED BEFORE IT IS CALLED\n\n",func->TREENODEDATA->terminal->lineNo);
            }

        }
        return str;
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

SYMBOLTABLEROW GetForFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE FOR){
    int index = FOR_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];

    while(str!=NULL){
        if(str->id == FOR->TREENODEDATA->terminal){
            return str;
        }
        str = str->next;
    }
    return NULL;
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


SYMBOLTABLEROW GetWhileFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE WHILE){
    int index = WHILE_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];

    while(str!=NULL){
        if(str->id == WHILE->TREENODEDATA->terminal){
            return str;
        }
        str = str->next;
    }
    return NULL;
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

SYMBOLTABLEROW GetSwitchFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE SWITCH){
    int index = SWITCH_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];

    while(str!=NULL){
        if(str->id == SWITCH->TREENODEDATA->terminal){
            return str;
        }
        str = str->next;
    }
    return NULL;
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

SYMBOLTABLEROW GetCaseFromSymbolTable(SYMBOLTABLE SYMBOL_TABLE,TREENODE CASE){
    int index = CASE_ROW;
    SYMBOLTABLEROW str = SYMBOL_TABLE->TABLE[index];
    while(str!=NULL){
        if(str->id == CASE->TREENODEDATA->terminal){
            return str;
        }
        str = str->next;
    }
    return NULL;
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
    // printTable(SYMBOL_TABLE);
    // printf("NAHI MILA FUNCTION\n\n");
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
        
        ARRRANGE aR = malloc(sizeof(struct arrRange));
        IP->range = aR;
        IP->range->left = range->left_child;
        IP->range->right = range->right_child;
        if(range->left_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN || range->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
            IP->isDynamic = 1;
        }
        else{
            if(range->left_child->left_child == NULL || range->left_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                IP->range->leftVal = range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                IP->range->leftVal = -1*range->left_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            if(range->right_child->left_child == NULL || range->right_child->left_child->TREENODEDATA->terminal->token  == PLUS_OPERATOR){
                IP->range->rightVal = range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            else{
                IP->range->rightVal = -1*range->right_child->TREENODEDATA->terminal->lexemedata->intData;
            }
            IP->isDynamic = 0;
        }
        IP->offset = OFFSET;
        OFFSET += 2*(OFFSETS[TYPE_INTEGER]) + 1;
        if(range->left_child->left_child != NULL){
            IP->range->leftSign = range->left_child->left_child->TREENODEDATA->terminal->lexemedata->data;
        }
        else{
            IP->range->leftSign = NULL;
        }
        if(range->right_child->left_child != NULL){
            IP->range->rightSign = range->right_child->left_child->TREENODEDATA->terminal->lexemedata->data;
        }
        else{
            IP->range->rightSign = NULL;
        }
    }
    else{
        IP->offset = OFFSET;
        OFFSET += OFFSETS[var->type];
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
    OP->offset = OFFSET;
    OFFSET += OFFSETS[var->type];
    return OP;
}


/*
*PRINT FULL SYMBOL TABLE
*/


void printRowSymbolTable(SYMBOLTABLEROW function,SYMBOLTABLE scopeTable,SYMBOLTABLEROW row,int level){
    printf("%s\t\t",row->id->lexemedata->data);
    printf("%s\t\t",function->id->lexemedata->data);
    printf("[%d-%d]\t\t",scopeTable->first,scopeTable->last);
    if(row->type == TYPE_INTEGER){
        printf("integer\t\t");
    }
    if(row->type == TYPE_BOOLEAN){
        printf("boolean\t\t");
    }
    if(row->type == TYPE_REAL){
        printf("real\t\t");
    }
    if(row->isDynamic == -1){
        printf("no\t\t");
        printf("**\t\t");
        printf("**\t\t");
        // printf("%d\t\t",OFFSETS[row->type]);

    }
    else if(row->isDynamic == 0){
        printf("yes\t\t");
        printf("static\t\t");
        printf("[");
        printf("%d,",row->range->leftVal);
        printf("%d]\t\t",row->range->rightVal);
        // printf("%d\t\t",1 + OFFSETS[row->type]*(1 + row->range->right->TREENODEDATA->terminal->lexemedata->intData-row->range->left->TREENODEDATA->terminal->lexemedata->intData));
    }
    else{
        printf("yes\t\t");
        printf("dynamic\t\t");
        printf("[");
        if(row->range->leftSign != NULL){
            printf("%s",row->range->leftSign);
        }
        if(row->range->left->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d,",row->range->left->TREENODEDATA->terminal->lexemedata->intData);
        else if(row->range->left->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s,",row->range->left->TREENODEDATA->terminal->lexemedata->data);
        if(row->range->rightSign != NULL){
            printf("%s",row->range->rightSign);
        }
        if(row->range->right->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d]\t\t",row->range->right->TREENODEDATA->terminal->lexemedata->intData);
        else if(row->range->right->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s]\t\t",row->range->right->TREENODEDATA->terminal->lexemedata->data);
        // printf("1\t\t");
    }
    if(level == 0)printf("%d\t\t",getWidth(row,1));
    else printf("%d\t\t",getWidth(row,0));
    printf("%d\t\t",row->offset - function->SYMBOLTABLE->currOffset);
    printf("%d\t\t",level);
    printf("\n\n");
}


void printLinkedList(SYMBOLTABLEROW function,SYMBOLTABLEROW head,int level,SYMBOLTABLEROW scopeRow){
    if(head == NULL) return;
    printRowSymbolTable(function,scopeRow->SYMBOLTABLE,head,level);
    printLinkedList(function,head->next,level,scopeRow);
}

void printFunctionTable(SYMBOLTABLEROW function,SYMBOLTABLEROW scope_row,int level){
    if(scope_row == NULL || scope_row->SYMBOLTABLE == NULL || scope_row->SYMBOLTABLE->TABLE == NULL) return;
    if(function == NULL) return;
    if(scope_row->INPUTPARAMSHEAD != NULL){
        printLinkedList(function,function->INPUTPARAMSHEAD,0,scope_row);
        printLinkedList(function,function->OUTPUTPARAMSHEAD,0,scope_row);
    }
    // if(scope_row->INPUTPARAMSHEAD == NULL && level == 1) return;
    for(int i = 0;i<SYMTABSIZE;i++){
        printLinkedList(function,scope_row->SYMBOLTABLE->TABLE[i],level,scope_row);
    }
    if(scope_row->SYMBOLTABLE->TABLE[FOR_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[FOR_ROW];
        while(row!=NULL){
            printFunctionTable(function,row,level+1);
            row = row->next;
        }
    }
    if(scope_row->SYMBOLTABLE->TABLE[WHILE_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[WHILE_ROW];
        while(row!=NULL){
            printFunctionTable(function,row,level+1);
            row = row->next;
        }
    }
    if(scope_row->SYMBOLTABLE->TABLE[SWITCH_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[SWITCH_ROW];
        while(row!=NULL){
            SYMBOLTABLEROW caseRow = row->SYMBOLTABLE->TABLE[CASE_ROW];
            while(caseRow != NULL){
                printFunctionTable(function,caseRow,level+1);
                caseRow = caseRow->next;
            }
            row = row->next;
        }
    }
}

void printFullTable(SYMBOLTABLE ST){
    for(int i = 0;i<SYMTABSIZE;i++){
        SYMBOLTABLEROW str = ST->TABLE[i];
        while(str!=NULL){
            printFunctionTable(str,str,1);
            str=str->next;
        }
    }
}



/*
*PRINT FUNCTIONS
*/




int getLinkedListSum(SYMBOLTABLEROW function,SYMBOLTABLEROW head,SYMBOLTABLEROW scopeRow,int isParam){
    if(head == NULL) return 0;
    return getWidth(head,isParam) + getLinkedListSum(function,head->next,scopeRow,isParam);
}

int getSumFunction(SYMBOLTABLEROW function,SYMBOLTABLEROW scope_row){
    if(scope_row == NULL || scope_row->SYMBOLTABLE == NULL || scope_row->SYMBOLTABLE->TABLE == NULL) return 0;
    if(function == NULL) return 0;
    int sum = 0;
    if(scope_row->INPUTPARAMSHEAD != NULL){
        sum+=getLinkedListSum(function,function->INPUTPARAMSHEAD,scope_row,1);
        sum+=getLinkedListSum(function,function->OUTPUTPARAMSHEAD,scope_row,0);
    }
    // if(scope_row->INPUTPARAMSHEAD == NULL && level == 1) return;
    for(int i = 0;i<SYMTABSIZE;i++){
        sum+=getLinkedListSum(function,scope_row->SYMBOLTABLE->TABLE[i],scope_row,0);
    }
    if(scope_row->SYMBOLTABLE->TABLE[FOR_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[FOR_ROW];
        while(row!=NULL){
            sum+=getSumFunction(function,row);
            row = row->next;
        }
    }
    if(scope_row->SYMBOLTABLE->TABLE[WHILE_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[WHILE_ROW];
        while(row!=NULL){
            sum+=getSumFunction(function,row);
            row = row->next;
        }
    }
    if(scope_row->SYMBOLTABLE->TABLE[SWITCH_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[SWITCH_ROW];
        while(row!=NULL){
            SYMBOLTABLEROW caseRow = row->SYMBOLTABLE->TABLE[CASE_ROW];
            while(caseRow != NULL){
                sum+=getSumFunction(function,caseRow);
                caseRow = caseRow->next;
            }
            row = row->next;
        }
    }
    return sum;
}

void printFunctions(SYMBOLTABLE ST){
    for(int i = 0;i<SYMTABSIZE;i++){
        SYMBOLTABLEROW str = ST->TABLE[i];
        while(str!=NULL){
            int sum = getSumFunction(str,str);
            printf("\t\t%s\t\t\t\t\t%d\n\n\n",str->id->lexemedata->data,sum);
            str=str->next;
        }
    }
}

/*
*PRINT ARRAYS*
*/

void printArraySymbolTable(SYMBOLTABLEROW function,SYMBOLTABLE scopeTable,SYMBOLTABLEROW row,int level){
    if(row == NULL || row->isDynamic == -1) return;
    printf("%s\t\t",function->id->lexemedata->data);
    printf("[%d-%d]\t\t",scopeTable->first,scopeTable->last);
    printf("%s\t\t",row->id->lexemedata->data);

    if(row->isDynamic == 0){
        printf("static\t\t");
        printf("[");
        printf("%d,",row->range->leftVal);
        printf("%d]\t\t",row->range->rightVal);
    }
    else if(row->isDynamic == 1){
        printf("dynamic\t\t");
        printf("[");
        if(row->range->leftSign != NULL){
            printf("%s",row->range->leftSign);
        }
        if(row->range->left->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d,",row->range->left->TREENODEDATA->terminal->lexemedata->intData);
        else if(row->range->left->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s,",row->range->left->TREENODEDATA->terminal->lexemedata->data);
        if(row->range->rightSign != NULL){
            printf("%s",row->range->rightSign);
        }
        if(row->range->right->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d]",row->range->right->TREENODEDATA->terminal->lexemedata->intData);
        else if(row->range->right->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s]\t\t",row->range->right->TREENODEDATA->terminal->lexemedata->data);
    }
    if(row->type == TYPE_INTEGER){
        printf("integer\t\t");
    }
    if(row->type == TYPE_BOOLEAN){
        printf("boolean\t\t");
    }
    if(row->type == TYPE_REAL){
        printf("real\t\t");
    }
    printf("\n\n");
}


void printLinkedArrayList(SYMBOLTABLEROW function,SYMBOLTABLEROW head,int level,SYMBOLTABLEROW scopeRow){
    if(head == NULL) return;
    printArraySymbolTable(function,scopeRow->SYMBOLTABLE,head,level);
    printLinkedArrayList(function,head->next,level,scopeRow);
}

void printFunctionArrayTable(SYMBOLTABLEROW function,SYMBOLTABLEROW scope_row,int level){
    if(scope_row == NULL || scope_row->SYMBOLTABLE == NULL || scope_row->SYMBOLTABLE->TABLE == NULL) return;
    if(function == NULL) return;
    if(scope_row->INPUTPARAMSHEAD != NULL){
        printLinkedArrayList(function,function->INPUTPARAMSHEAD,0,scope_row);
        printLinkedArrayList(function,function->OUTPUTPARAMSHEAD,0,scope_row);
    }
    // if(scope_row->INPUTPARAMSHEAD == NULL && level == 1) return;
    for(int i = 0;i<SYMTABSIZE;i++){
        printLinkedArrayList(function,scope_row->SYMBOLTABLE->TABLE[i],level,scope_row);
    }
    if(scope_row->SYMBOLTABLE->TABLE[FOR_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[FOR_ROW];
        while(row!=NULL){
            printFunctionArrayTable(function,row,level+1);
            row = row->next;
        }
    }
    if(scope_row->SYMBOLTABLE->TABLE[WHILE_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[WHILE_ROW];
        while(row!=NULL){
            printFunctionArrayTable(function,row,level+1);
            row = row->next;
        }
    }
    if(scope_row->SYMBOLTABLE->TABLE[SWITCH_ROW] != NULL){
        SYMBOLTABLEROW row = scope_row->SYMBOLTABLE->TABLE[SWITCH_ROW];
        while(row!=NULL){
            SYMBOLTABLEROW caseRow = row->SYMBOLTABLE->TABLE[CASE_ROW];
            while(caseRow != NULL){
                printFunctionArrayTable(function,caseRow,level+1);
                caseRow = caseRow->next;
            }
            row = row->next;
        }
    }
}

void printArrayTable(SYMBOLTABLE ST){
    for(int i = 0;i<SYMTABSIZE;i++){
        SYMBOLTABLEROW str = ST->TABLE[i];
        while(str!=NULL){
            printFunctionArrayTable(str,str,1);
            str=str->next;
        }
    }
}