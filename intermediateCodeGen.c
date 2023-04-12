#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intermediateCodeGen.h"

int TEMP_NUM = 0;
int FOR_COUNT = 0;
int WHILE_COUNT = 0;
int CASE_COUNT = 0;
int SWITCH_COUNT = 0;
int DEFAULT_COUNT = 0;

TREENODE getTemp(TREENODE node){
    TREENODE temp;
    temp = malloc(sizeof(struct TreeNode));
    temp->TREENODEDATA = (union TreeNodeData*) malloc(sizeof(union TreeNodeData));
    temp->TREENODEDATA->terminal = (LEXEME*) malloc(sizeof(LEXEME));
    temp->TREENODEDATA->terminal->lexemedata = (union lexemeData*) malloc(sizeof(union lexemeData));
    char name[5];

    sprintf(name,"t%d",TEMP_NUM++);
    temp->TREENODEDATA->terminal->lexemedata->data = (char*) malloc(sizeof(char)*5);
    strcpy(temp->TREENODEDATA->terminal->lexemedata->data,name);
    temp->TREENODEDATA->terminal->token = IDENTIFIER_TOKEN;
    return temp;
}

void printNODE(TREENODE node){
    if(node == NULL) printf("NULL  ");
    else if(node->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d  ",node->TREENODEDATA->terminal->lexemedata->intData);
    else if(node->TREENODEDATA->terminal->token == RNUM_TOKEN) printf("%f  ",node->TREENODEDATA->terminal->lexemedata->floatData);
    else if(node->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s  ",node->TREENODEDATA->terminal->lexemedata->data);
    else printf("%s  ",node->TREENODEDATA->terminal->lexemedata->data);
}

QUADRUPLE initializeQuadruple(){
    QUADRUPLE q = malloc(sizeof(struct Quadruple));
    q->top = NULL;
    q->curr = NULL;
    return q;
}

QUADRUPLEROW initializeQuadrupleRow(OPERATOR operator,TREENODE left,TREENODE op1,TREENODE op2,SYMBOLTABLEROW func,SYMBOLTABLE ST,int data){
    QUADRUPLEROW qr = malloc(sizeof(struct QuadrupleRow));
    qr->below = NULL;
    qr->left = left;
    qr->operator = operator;
    qr->op1 = op1;
    qr->op2 = op2;
    qr->ST = ST;
    qr->currFunc = func;
    qr->data = data;
    return qr;
}

void printQuadRupleRow(QUADRUPLEROW qr){
    printf("%d  ",qr->operator);
    printNODE(qr->left);
    printNODE(qr->op1);
    printNODE(qr->op2);
}

QUADRUPLE insertRow(OPERATOR operator,TREENODE left,TREENODE op1,TREENODE op2,SYMBOLTABLEROW func,SYMBOLTABLE ST,int data){
    QUADRUPLE q = QR;

    QUADRUPLEROW qr = initializeQuadrupleRow( operator, left, op1, op2,func,ST,data);
    if(q->top == NULL){
        q->top = qr;
        q->curr = qr;
        return q;
    }
    q->curr->below = qr;
    q->curr = qr;
    return q;
}

QUADRUPLEROW getRowFromQuadruple(){
    QUADRUPLE q = QR;
    QUADRUPLEROW top = q->top;
    q->top = top->below;
    return top;
}

void printQuadRuple(){
    QUADRUPLE q = QR;
    QUADRUPLEROW top = q->top;
    while(top!=NULL){
        printQuadRupleRow(top);
        printf("\n\n");
        top = top->below;
    }
}

void passParam(TREENODE param,SYMBOLTABLEROW func,SYMBOLTABLE ST){
    if(param == NULL) return;
    insertRow(PASS_PARAM,param,NULL,NULL,func,ST,-1);
    passParam(param->list_addr_syn,func,ST);
}

void getReturn(TREENODE param,SYMBOLTABLEROW func,SYMBOLTABLE ST){
    if(param == NULL) return;
    getReturn(param->list_addr_syn,func,ST);
    insertRow(GET_RETURN,param,NULL,NULL,func,ST,-1);
}

void addDeclareVars(TREENODE var,SYMBOLTABLEROW func,SYMBOLTABLE ST){
    if(var == NULL) return;
    insertRow(DECLARE_VARIABLE,var,NULL,NULL,func,ST,-1);
    addDeclareVars(var->list_addr_syn,func,ST);
}

void addInputParams(TREENODE input_node,SYMBOLTABLEROW func,SYMBOLTABLE ST){
    if(input_node == NULL) return;
    addInputParams(input_node->list_addr_syn,func,ST);
    insertRow(FORMAL_INPUT_PARAMS,input_node,NULL,NULL,func,ST,-1);
}

void addOutputParams(TREENODE output_node,SYMBOLTABLEROW func,SYMBOLTABLE ST){
    if(output_node == NULL) return;
    insertRow(FORMAL_OUTPUT_PARAMS,output_node,NULL,NULL,func,ST,-1);
    addOutputParams(output_node->list_addr_syn,func,ST);
}


TREENODE expressionGenerator(TREENODE expression_node,SYMBOLTABLEROW func,SYMBOLTABLE ST){
    if(expression_node == NULL) return NULL;
    TREENODE left = expressionGenerator(expression_node->left_child,func,ST);
    TREENODE right = expressionGenerator(expression_node->right_child,func,ST);

    if(expression_node->TREENODEDATA->terminal->token == PLUS_OPERATOR){
        if(left == NULL && right == NULL) return NULL;
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        
        insertRow(ADDITION,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == MINUS_OPERATOR){
        if(left == NULL && right == NULL) return NULL;
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(SUBTRACTION,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == MUL_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(MULTIPLICATION,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == DIV_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(DIVISION,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == LT_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(LESS_THAN,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == LE_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(LESS_THAN_EQUAL,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == GT_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(GREATER_THAN,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == GE_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(GREATER_THAN_EQUAL,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == EQ_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(EQUAL,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == NE_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(NOT_EQUAL,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == AND_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(AND,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == OR_OPERATOR){
        TREENODE temp = getTemp(expression_node);
        StoreVarIntoSymbolTable(ST,temp,NULL);
        insertRow(OR,temp,left,right,currFunc,ST,-1);
        return temp;
    }
    else if(expression_node->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
        SYMBOLTABLEROW row = GetVarFromSymbolTable(ST,expression_node);
        if(row->isDynamic != -1){
            printf("LINE %d\n",expression_node->TREENODEDATA->terminal->lineNo);
            printASTNODE(expression_node);
            printASTNODE(expression_node->right_child);

            TREENODE temp1 = getTemp(expression_node);
            StoreVarIntoSymbolTable(ST,temp1,NULL);
            if(row->isDynamic == 1){
                // TYPE CHECK KRNA HAI
            }
            insertRow(ARRAY_ACCESS,temp1,expression_node,right,currFunc,ST,-1);
            return temp1;
        }
        else if(expression_node->left_child != NULL && expression_node->left_child->TREENODEDATA->terminal->token == MINUS_OPERATOR){
            TREENODE temp = getTemp(expression_node);
            StoreVarIntoSymbolTable(ST,temp,NULL);
            insertRow(UNARY_MINUS,temp,expression_node,NULL,currFunc,ST,-1);
            return temp;
            
        }

        
            /*YE BAAD ME KRNA HAI*/
        return expression_node;

    }

    else if(expression_node->TREENODEDATA->terminal->token == NUM_TOKEN){
        return expression_node;
    }
    else if(expression_node->TREENODEDATA->terminal->token == RNUM_TOKEN){
        return expression_node;
    }
    else if(expression_node->TREENODEDATA->terminal->token == TRUE_BOOL){
        return expression_node;
    }
    else if(expression_node->TREENODEDATA->terminal->token == FALSE_BOOL){
        return expression_node;
    }
    else{
        printf("*****ERROR IN EXPRESSION*****");
        printASTNODE(expression_node);
        traversalForCodeGeneration(expression_node->left_child,ST);
        traversalForCodeGeneration(expression_node->right_child,ST);
        traversalForCodeGeneration(expression_node->list_addr_syn,ST);   
    }
}


void traversalForCodeGeneration(TREENODE node,SYMBOLTABLE SYMBOL_TABLE){
    if(node == NULL) return;
    
    // printf("\n\nLINE IS %d\n\n",node->TREENODEDATA->terminal->lineNo);
    // printASTNODE(node);

    /*MODULE DECLARATIONS*/
    if(node->parent != NULL && node->parent->TREENODEDATA->nonterminal == moduleDeclaration){
        insertRow(MODULE_DECLARATION,node,NULL,NULL,currFunc,SYMBOL_TABLE,-1);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*DRIVER MODULE*/
    else if(node->TREENODEDATA->terminal->token == DRIVER_KEYWORD){
        insertRow(DRIVER_MODULE,node,NULL,NULL,currFunc,SYMBOL_TABLE,-1);
        SYMBOLTABLEROW row = GetFuncFromSymbolTable(SYMBOL_TABLE,node);
        currFunc = row; 
        traversalForCodeGeneration(node->left_child,row->SYMBOLTABLE);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        insertRow(DRIVER_MODULE_END,NULL,NULL,NULL,NULL,NULL,-1);
        return;
    }

    /*OTHER MODULES*/
    else if(node->left_child!=NULL && node->left_child->TREENODEDATA->terminal->token == TAKES_KEYWORD){
        insertRow(MODULE_DEFINITION, node , NULL , NULL, currFunc,SYMBOL_TABLE,-1);
        SYMBOLTABLEROW row = GetFuncFromSymbolTable(SYMBOL_TABLE,node);
        currFunc = row;
        addInputParams(node->left_child->left_child, currFunc,row->SYMBOLTABLE);
        traversalForCodeGeneration(node->right_child,row->SYMBOLTABLE);
        addOutputParams(node->left_child->right_child, currFunc,row->SYMBOLTABLE);
        insertRow(MODULE_END, node , NULL , NULL, currFunc,SYMBOL_TABLE,-1);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*DECLARE STMT*/
    else if(node->TREENODEDATA->terminal->token == DECLARE_KEYWORD){
        addDeclareVars(node->left_child, currFunc,SYMBOL_TABLE);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*FOR LOOP: ITERATIVE STMT*/
    else if(node->TREENODEDATA->terminal->token == FOR_KEYWORD){
        SYMBOLTABLEROW row = GetForFromSymbolTable(SYMBOL_TABLE,node);
        if(node->left_child->left_child->left_child != NULL && node->left_child->left_child->left_child->TREENODEDATA->terminal->token == MINUS_OPERATOR){
            node->left_child->left_child->TREENODEDATA->terminal->lexemedata->intData*=-1;
        }
        if(node->left_child->right_child->left_child != NULL && node->left_child->right_child->left_child->TREENODEDATA->terminal->token == MINUS_OPERATOR){
            node->left_child->right_child->TREENODEDATA->terminal->lexemedata->intData*=-1;
        }
        int for_label = FOR_COUNT++;
        insertRow(FOR_LOOP,node->left_child,NULL,NULL, currFunc,row->SYMBOLTABLE,for_label);
        traversalForCodeGeneration(node->right_child,row->SYMBOLTABLE);
        insertRow(FOR_LOOP_END,NULL,NULL,NULL, currFunc,SYMBOL_TABLE,for_label);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*WHILE LOOP ITERATIVE STMT*/
    else if(node->TREENODEDATA->terminal->token == WHILE_KEYWORD){
        SYMBOLTABLEROW row = GetWhileFromSymbolTable(SYMBOL_TABLE,node);
        TREENODE left = expressionGenerator(node->left_child,currFunc,SYMBOL_TABLE);
        int while_label = WHILE_COUNT++;
        insertRow(WHILE_START,left,NULL,NULL,currFunc,SYMBOL_TABLE,while_label);
        traversalForCodeGeneration(node->right_child,row->SYMBOLTABLE);
        insertRow(WHILE_END,left,NULL,NULL,currFunc,SYMBOL_TABLE,while_label);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*CONDITIONAL STMT*/
    else if(node->parent!=NULL && node->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN && node->parent->TREENODEDATA->nonterminal == conditionalStmt){
        SYMBOLTABLEROW row = GetSwitchFromSymbolTable(SYMBOL_TABLE,node);
        int switch_label = SWITCH_COUNT++;
        insertRow(SWITCH_START,node,NULL,NULL,currFunc,SYMBOL_TABLE,switch_label);
        TREENODE caseVal = node->left_child;
        while(caseVal!=NULL){
            int case_label = CASE_COUNT;
            insertRow(CASE_START,caseVal,NULL,NULL,currFunc,SYMBOL_TABLE,case_label);
            SYMBOLTABLEROW case_node = GetCaseFromSymbolTable(row->SYMBOLTABLE,caseVal);
            traversalForCodeGeneration(caseVal->left_child,case_node->SYMBOLTABLE);
            insertRow(CASE_BREAK,NULL,NULL,NULL,currFunc,SYMBOL_TABLE,case_label);
            caseVal = caseVal->list_addr_syn;
        }
        if(node->right_child !=NULL){
            insertRow(DEFAULT_START,NULL,NULL,NULL,currFunc,SYMBOL_TABLE,DEFAULT_COUNT++);
            traversalForCodeGeneration(node->right_child->left_child,SYMBOL_TABLE);
        }
        insertRow(SWITCH_END,node,NULL,NULL,currFunc,SYMBOL_TABLE,switch_label);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*MODULE REUSE STMT: SIMPLE STMT*/
    else if(node->parent!=NULL && node->parent->TREENODEDATA->nonterminal == moduleReuseStmt){
        passParam(node->right_child, currFunc,SYMBOL_TABLE);
        insertRow(MODULE_REUSE,node,NULL,NULL, currFunc,SYMBOL_TABLE,-1);
        getReturn(node->left_child, currFunc,SYMBOL_TABLE);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*ASSIGNMENT STMT: SIMPLE STMT*/
    else if(node->TREENODEDATA->terminal->token == ASSIGNOP_OPERATOR){
        SYMBOLTABLEROW leftRow = GetVarFromSymbolTable(SYMBOL_TABLE,node->left_child);
        if(leftRow->isDynamic != -1 && node->left_child->right_child == NULL){
            insertRow(ARRAY_ASSIGNMENT,node->left_child,node->right_child,NULL,currFunc,SYMBOL_TABLE,-1);
        }
        else if(leftRow->isDynamic != -1 && node->left_child->right_child != NULL){
            TREENODE temp1 = expressionGenerator(node->left_child->right_child,currFunc,SYMBOL_TABLE);
            TREENODE temp = getTemp(node);
            StoreVarIntoSymbolTable(SYMBOL_TABLE,temp,NULL);
            insertRow(ARRAY_ACCESS,temp,node->left_child,temp1,currFunc,SYMBOL_TABLE,-1);
            TREENODE right = expressionGenerator(node->right_child,currFunc,SYMBOL_TABLE);
            insertRow(ASSIGN,temp,right,NULL,currFunc,SYMBOL_TABLE,-1);
        }
        else{
            TREENODE right = expressionGenerator(node->right_child,currFunc,SYMBOL_TABLE);
            insertRow(ASSIGN,node->left_child,right,NULL,currFunc,SYMBOL_TABLE,-1);
        }
        // insertRow(ASSIGN,node->left_child,)
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*GET VALUE: IO STMT*/
    else if(node->TREENODEDATA->terminal->token == GET_VALUE_KEYWORD){
        TREENODE ID = node->left_child;
        insertRow(GET_VALUE,ID,NULL,NULL, currFunc,SYMBOL_TABLE,-1);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*PRINT FUNCTION: IO STMT */
    else if(node->TREENODEDATA->terminal->token == PRINT_FUNCTION){
        insertRow(PRINT_VALUE,node->left_child,NULL,NULL, currFunc,SYMBOL_TABLE,-1);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }
    
    // // ISME KUCH NHI JANA CHAHIYE
    else{
        printf("*****ERROR*****");
        printASTNODE(node);
        traversalForCodeGeneration(node->left_child,SYMBOL_TABLE);
        traversalForCodeGeneration(node->right_child,SYMBOL_TABLE);
        traversalForCodeGeneration(node->list_addr_syn,SYMBOL_TABLE);
    }
    
}