#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intermediateCodeGen.h"


void printNODE(TREENODE node){
    if(node == NULL) printf("NODE IS NULL  ");
    if(node->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d  ",node->TREENODEDATA->terminal->lexemedata->intData);
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

QUADRUPLEROW initializeQuadrupleRow(OPERATOR operator,TREENODE left,TREENODE op1,TREENODE op2){
    QUADRUPLEROW qr = malloc(sizeof(struct QuadrupleRow));
    qr->below = NULL;
    qr->left = left;
    qr->operator = operator;
    qr->op1 = op1;
    qr->op2 = op2;
    return qr;
}

QUADRUPLE insertRow(OPERATOR operator,TREENODE left,TREENODE op1,TREENODE op2){
    QUADRUPLE q = QR;
    QUADRUPLEROW qr = initializeQuadrupleRow( operator, left, op1, op2);
    q->curr->below = qr;
    q->curr = qr;
}

void printQuadRupleRow(QUADRUPLEROW qr){
    printf("%d  ",qr->operator);
    printNODE(qr->left);
    printNODE(qr->op1);
    printNODE(qr->op2);
}

void printQuadRuple(){
    QUADRUPLE q = QR;
    QUADRUPLEROW top = q->top;
    while(top!=NULL){
        printQuadRupleRow(top);
        top = top->below;
    }
}


void addInputParams(SYMBOLTABLEROW input_node){
    if(input_node == NULL) return;
    insertRow(FORMAL_INPUT_PARAMS,input_node,NULL,NULL);
    addInputParams(input_node->next);
}

void traversal(TREENODE node,SYMBOLTABLE SYMBOL_TABLE){
    if(node == NULL) return;
    
    // printf("\n\nLINE IS %d\n\n",node->TREENODEDATA->terminal->lineNo);
    // printASTNODE(node);

    /*MODULE DECLARATIONS => */
    if(node->parent != NULL && node->parent->TREENODEDATA->nonterminal == moduleDeclaration){
        insertRow(MODULE_DECLARATION,node,NULL,NULL);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*DRIVER MODULE => LAST ME PRINT KRNA HAI*/
    else if(node->TREENODEDATA->terminal->token == DRIVER_KEYWORD){
        insertRow(DRIVER_MODULE,node,NULL,NULL);
        SYMBOLTABLEROW row = GetFuncFromSymbolTable(SYMBOL_TABLE,node);
        currFunc = row; 
        traversal(node->left_child,row->SYMBOLTABLE);

        return;
    }

    /*OTHER MODULES*/
    else if(node->left_child!=NULL && node->left_child->TREENODEDATA->terminal->token == TAKES_KEYWORD){
        insertRow(MODULE_DEFINITION, node , NULL , NULL);
        SYMBOLTABLEROW row = GetFuncFromSymbolTable(SYMBOL_TABLE,node);
        currFunc = row;
        addInputParams(row->INPUTPARAMSHEAD);
        traversal(node->right_child,row->SYMBOLTABLE);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*DECLARE STMT*/
    else if(node->TREENODEDATA->terminal->token == DECLARE_KEYWORD){
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*FOR LOOP: ITERATIVE STMT*/
    else if(node->TREENODEDATA->terminal->token == FOR_KEYWORD){
        node -> left_child -> type = TYPE_INTEGER;
        SYMBOLTABLEROW row = StoreForIntoSymbolTable(SYMBOL_TABLE,node);
        row->SYMBOLTABLE = initializeSymbolTable("for");
        row->SYMBOLTABLE->parent = SYMBOL_TABLE;
        SYMBOLTABLEROW FORID = StoreVarIntoSymbolTable(row->SYMBOLTABLE,node->left_child,NULL);
        row->SYMBOLTABLE->TABLE[64] = FORID;
        traversal(node->right_child,row->SYMBOLTABLE);
        // printSymbolTable(row);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*WHILE LOOP ITERATIVE STMT*/
    else if(node->TREENODEDATA->terminal->token == WHILE_KEYWORD){
        SYMBOLTABLEROW row = StoreWhileIntoSymbolTable(SYMBOL_TABLE,node);
        row->SYMBOLTABLE = initializeSymbolTable("WHILE");
        row->SYMBOLTABLE->parent = SYMBOL_TABLE;
        typeExtractionExpr(node->left_child,row->SYMBOLTABLE);
        if(node->left_child->type != TYPE_BOOLEAN){
            printf("LINE %d: WHILE LOOP EXPRESSION MUST BE BOOLEAN\n\n",node->TREENODEDATA->terminal->lineNo);
        }
        traversal(node->right_child,row->SYMBOLTABLE);
        // printSymbolTable(row);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*CONDITIONAL STMT*/
    else if(node->parent!=NULL && node->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN && node->parent->TREENODEDATA->nonterminal == conditionalStmt){
        SYMBOLTABLEROW row = StoreSwitchIntoSymbolTable(SYMBOL_TABLE,node);
        row->SYMBOLTABLE = initializeSymbolTable("SWITCH");
        row->SYMBOLTABLE->parent = SYMBOL_TABLE;
        SYMBOLTABLEROW x = GetVarFromSymbolTable(SYMBOL_TABLE,node);
        int t = x->type;
        if(x->isDynamic != -1){
            printf("LINE %d, ARRAY VARIABLE CAN NOT BE PART OF SWITCH STMT",node->TREENODEDATA->terminal->lineNo);
        }
        if(t == TYPE_REAL){
            printf("LINE %d: SWITCH CASE CAN NOT HAVE REAL TYPE VARIABLE\n\n",node->TREENODEDATA->terminal->lineNo);
        }
        TREENODE caseVal = node->left_child;

        while(caseVal!=NULL){
            caseVal->type = getTypeAST(caseVal,SYMBOL_TABLE);
            if(t != TYPE_REAL && caseVal->type != t){
                printf("LINE %d: CASE STATEMENT MUST HAVE TYPE SAME AS SWITCH VAR\n",caseVal->TREENODEDATA->terminal->lineNo);
            }
            SYMBOLTABLEROW case_node = StoreCaseIntoSymbolTable(row->SYMBOLTABLE,caseVal);
            case_node->SYMBOLTABLE = initializeSymbolTable("CASE");
            case_node->SYMBOLTABLE->parent = row->SYMBOLTABLE;
            traversal(caseVal->left_child,case_node->SYMBOLTABLE);
            caseVal = caseVal->list_addr_syn;
        }
        if(t == TYPE_INTEGER && node->right_child == NULL){
            printf("LINE %d: DEFAULT STATEMENT MUST BE THERE IN CASE OF INTEGER\n",node->TREENODEDATA->terminal->lineNo);
        }
        else if(t == TYPE_INTEGER && node->right_child != NULL){
            traversal(node->right_child->left_child,row->SYMBOLTABLE);
        }
        else if(t == TYPE_BOOLEAN && node->right_child != NULL){
            printf("LINE %d: NO DEFAULT STATEMENT IN CASE OF BOOLEAN EXPRESSION\n\n",node->right_child->TREENODEDATA->terminal->lineNo);
        }
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*MODULE REUSE STMT: SIMPLE STMT*/
    else if(node->parent!=NULL && node->parent->TREENODEDATA->nonterminal == moduleReuseStmt){
        SYMBOLTABLEROW row = GetFuncFromSymbolTable(GST,node);
        if(row==NULL){
            printf("LINE %d: FUNCTION NOT DEFINED\n\n",node->TREENODEDATA->terminal->lineNo);
        }
        else if(row == currFunc){
            printf("LINE %d: RECURSION IS NOT ALLOWED\n\n",node->TREENODEDATA->terminal->lineNo);
        }
        else{
            if(row->INPUTPARAMSHEAD == NULL){
                row->isDynamic = 1;
            }
            else{
                checkInputList(node, row, SYMBOL_TABLE);
                checkOutputList(node, row, SYMBOL_TABLE);
            }
            traversal(node->list_addr_syn,SYMBOL_TABLE);
            return;
        }
    }

    /*ASSIGNMENT STMT: SIMPLE STMT*/
    else if(node->TREENODEDATA->terminal->token == ASSIGNOP_OPERATOR){
        checkForLoop(node->left_child,SYMBOL_TABLE);
        outputParamAssignment(node->left_child);
        typeExtractionExpr(node->right_child,SYMBOL_TABLE);
        // printASTNODE(node->right_child);
        SYMBOLTABLEROW rightRow = NULL;
        
        SYMBOLTABLEROW leftRow = GetVarFromSymbolTable(SYMBOL_TABLE,node->left_child);
        if(leftRow == NULL){
            printf("LINE %d: VARIABLE ON LEFT IS NOT DEFINED\n\n",node->left_child->TREENODEDATA->terminal->lineNo);
        }
        else{
            node->left_child->type = leftRow->type;
            if(node->left_child->right_child == NULL){
                if(leftRow->isDynamic != -1){
                    if(node->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN){
                        rightRow = GetVarFromSymbolTable(SYMBOL_TABLE,node->right_child);
                        if(rightRow == NULL){
                            printf("LINE %d, VARIABLE NOT DEFINED\n\n",node->right_child->TREENODEDATA->terminal->lineNo);
                        }
                    }
                    if(node->right_child->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN && rightRow != NULL && rightRow->isDynamic != -1){
                        if(leftRow->isDynamic == 0 && rightRow->isDynamic == 0){
                            if(leftRow->range->left == rightRow->range->left && leftRow->range->right == rightRow->range->right)printf("ARRAY ASSIGNED\n\n");
                            else printf("LINE %d: ARRAY CAN NOT BE ASSIGNED DUE TO RANGE MISMATCH\n\n",node->right_child->TREENODEDATA->terminal->lineNo);
                        }
                    }
                    else{
                        printf("LINE %d:CAN NOT ASSIGN VALUE TO AN ARRAY\n\n",node->left_child->TREENODEDATA->terminal->lineNo);
                    }
                }
                else{
                    if(node->left_child->type != node->right_child->type){
                        printf("LINE %d: ERROR OCCURED WHILE ASSIGNMENT, LEFT AND RIGHT TYPES DID NOT MATCH\n\n",node->TREENODEDATA->terminal->lineNo);
                    }
                }
            }
            else{
                int type = typeExtractionExpr(node->left_child->right_child,SYMBOL_TABLE);
                if(type != TYPE_INTEGER){
                    printf("LINE %d: ARRAY INDEX MUST BE AN INTEGER VALUE\n\n",node->left_child->TREENODEDATA->terminal->lineNo);
                }
            }
        }
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*GET VALUE: IO STMT*/
    else if(node->TREENODEDATA->terminal->token == GET_VALUE_KEYWORD){
        TREENODE ID = node->left_child;
        SYMBOLTABLEROW row = GetVarFromSymbolTable(SYMBOL_TABLE,ID);
        if(row == NULL) printf("LINE %d: VARIABLE NOT DECLARED\n\n",node->TREENODEDATA->terminal->lineNo);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }

    /*PRINT FUNCTION: IO STMT */
    else if(node->TREENODEDATA->terminal->token == PRINT_FUNCTION){
        getTypeAST(node->left_child,SYMBOL_TABLE);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
        return;
    }
    
    // ISME KUCH NHI JANA CHAHIYE
    else{
        printf("*****ERROR*****");
        printASTNODE(node);
        traversal(node->left_child,SYMBOL_TABLE);
        traversal(node->right_child,SYMBOL_TABLE);
        traversal(node->list_addr_syn,SYMBOL_TABLE);
    }
    
}