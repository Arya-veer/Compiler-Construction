#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"
#include "parser.h"

TREENODE insertAtBegin(TREENODE toPut,TREENODE nextList){
    toPut -> next = nextList;
    return toPut;
}

TREENODE makeNode(TREENODE assign,TREENODE left,TREENODE right){
    printf("MAKENODE\n");
    // if(assign->isTerminal == 1){
    // }
    if(assign->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d\n",assign->TREENODEDATA->terminal->lexemedata->intData);
    else if(assign->TREENODEDATA->terminal->token == RNUM_TOKEN) printf("%f\n",assign->TREENODEDATA->terminal->lexemedata->floatData);
    else if(assign->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s\n",assign->TREENODEDATA->terminal->lexemedata->data);
    else printf("%s\n",assign->TREENODEDATA->terminal->lexemedata->data);
    assign->left_child = left;
    printf("LEFT ASSIGNED\n");
    if(left != NULL){
        if(left->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d\n",left->TREENODEDATA->terminal->lexemedata->intData);
        else if(left->TREENODEDATA->terminal->token == RNUM_TOKEN) printf("%f\n",left->TREENODEDATA->terminal->lexemedata->floatData);
        else if(left->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s\n",left->TREENODEDATA->terminal->lexemedata->data);
        else printf("%s\n",left->TREENODEDATA->terminal->lexemedata->data);
    }
    else{
        printf("LEFT IS NULL\n");
    }
    assign->right_child = right;
    printf("RIGHT ASSIGNED\n");
    if(right != NULL){
        if(right->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%d\n",right->TREENODEDATA->terminal->lexemedata->intData);
        else if(right->TREENODEDATA->terminal->token == RNUM_TOKEN) printf("%f\n",right->TREENODEDATA->terminal->lexemedata->floatData);
        else if(right->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s\n",right->TREENODEDATA->terminal->lexemedata->data);
        else printf("%s\n",right->TREENODEDATA->terminal->lexemedata->data);
    }
    else{
        printf("RIGHT IS NULL\n");
    }
    return assign;

}


void applyRule(TREENODE parent){

    int ruleNum = parent->child->ruleNum;

    printf("STARTING RULE %d\n",ruleNum);
    

    switch(ruleNum){
        case 0: {
            TREENODE finalProgram_node = parent;
            // printf("SEARCHING FOR CHILD PROGRAM\n");
            TREENODE program_node = getChildNonTerminal(program,finalProgram_node);
            applyRule(program_node);
            finalProgram_node->addr = program_node->addr;
            TREENODE eof_node = getChildTerminal(EOF_TOKEN,finalProgram_node);
            free(eof_node);
            // printf("EYB\n");
            
            return;
        }
        case 1:{
            TREENODE program_node = parent;
            TREENODE moduleDeclarations_node = getChildNonTerminal(moduleDeclarations,parent);
            applyRule(moduleDeclarations_node);
            // printf("DRIVER MODULE LENE JA RHA HU\n");
            TREENODE driverModule_node = getChildNonTerminal(driverModule,parent);
            applyRule(driverModule_node);

            TREENODE* otherModules_node = getDualNonTerminal(otherModules,parent);
            TREENODE otherModules_node1 = otherModules_node[0];
            // printf("%ld\n",otherModules_node1);
            TREENODE otherModules_node2 = otherModules_node[1];
            // printf("%ld\n",otherModules_node2);
            applyRule(otherModules_node1);
            printf("HELLO\n");
            applyRule(otherModules_node2);
            program_node->addr = moduleDeclarations_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;

        }
        case 2:{
            TREENODE moduleDeclarations_node = parent;
            TREENODE moduleDeclaration_node = getChildNonTerminal(moduleDeclaration,moduleDeclarations_node);
            TREENODE moduleDeclarations1_node = getChildNonTerminal(moduleDeclarations,moduleDeclarations_node);
            applyRule(moduleDeclaration_node);
            applyRule(moduleDeclarations1_node);
            moduleDeclarations_node->list_addr_syn = insertAtBegin(moduleDeclaration_node->addr,moduleDeclarations1_node->list_addr_syn);
            moduleDeclarations_node->addr=moduleDeclarations_node->list_addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 3:{
            TREENODE moduleDeclarations_node = parent;
            moduleDeclarations_node->list_addr_syn = NULL;
            moduleDeclarations_node->addr = NULL;
            free(moduleDeclarations_node->child);
            // printf("3 HO GYA\n");
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 4:{
            TREENODE moduleDeclaration_node = parent;
            moduleDeclaration_node->addr = getChildTerminal(IDENTIFIER_TOKEN,moduleDeclaration_node);
            free(getChildTerminal(SEMICOL_OPERATOR,moduleDeclaration_node));
            free(getChildTerminal(MODULE_KEYWORD,moduleDeclaration_node));
            free(getChildTerminal(DECLARE_KEYWORD,moduleDeclaration_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 5:{
            TREENODE otherModules_node = parent;
            TREENODE module_node = getChildNonTerminal(module,otherModules_node);
            applyRule(module_node);
            TREENODE otherModules1_node = getChildNonTerminal(otherModules,otherModules_node); 
            applyRule(otherModules1_node);
            otherModules_node->list_addr_syn = insertAtBegin(module_node->addr,otherModules1_node->list_addr_syn);
            otherModules_node->addr = otherModules_node->list_addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 6:{
            TREENODE otherModules_node = parent;
            otherModules_node->list_addr_syn = NULL;
            otherModules_node->addr = NULL;
            free(otherModules_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 7:{
            TREENODE driverModule_node = parent;
            // printf("SEARCHING FOR CHILD MODULE DEF\n");
            TREENODE moduleDef_node = getChildNonTerminal(moduleDef,parent);
            applyRule(moduleDef_node);
            driverModule_node->addr = moduleDef_node->addr;
            free(getChildTerminal(DRIVERENDDEF_OPERATOR,driverModule_node));
            free(getChildTerminal(PROGRAM_KEYWORD,driverModule_node));
            free(getChildTerminal(DRIVER_KEYWORD,driverModule_node));
            free(getChildTerminal(DRIVERDEF_OPERATOR,driverModule_node));
            // printf("7 HO GYA\n");
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 8:{
            TREENODE module_node = parent;
            TREENODE input_plist_node = getChildNonTerminal(input_plist,module_node);
            applyRule(input_plist_node);
            TREENODE ret_node = getChildNonTerminal(ret,module_node);
            applyRule(ret_node);
            TREENODE TAKES = getChildTerminal(TAKES_KEYWORD,parent);
            TREENODE temp = makeNode(TAKES,input_plist_node->addr,ret_node->addr);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,module_node);
            TREENODE moduleDef_node = getChildNonTerminal(moduleDef,module_node);
            applyRule(moduleDef_node);
            module_node->addr = makeNode(ID,temp,moduleDef_node->addr);
            free(getChildTerminal(SEMICOL_OPERATOR,module_node));
            free(getChildTerminal(SQBC_TOKEN,module_node));
            free(getChildTerminal(SQBO_TOKEN,module_node));
            free(getChildTerminal(INPUT_KEYWORD,module_node));
            free(getChildTerminal(ENDDEF_OPERATOR,module_node));
            free(getChildTerminal(MODULE_KEYWORD,module_node));
            free(getChildTerminal(DEF_OPERATOR,module_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 9:{
            TREENODE ret_node = parent;
            TREENODE output_plist_node = getChildNonTerminal(output_plist,ret_node);
            applyRule(output_plist_node);
            ret_node->addr = output_plist_node->addr;
            free(getChildTerminal(SEMICOL_OPERATOR,ret_node));
            free(getChildTerminal(SQBC_TOKEN,ret_node));
            free(getChildTerminal(SQBO_TOKEN,ret_node));
            free(getChildTerminal(RETURNS_KEYWORD,ret_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 10:{
            TREENODE ret_node = parent;
            ret_node->addr = NULL;
            free(ret_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 11:{
            TREENODE input_plist_node = parent;
            TREENODE dataType_node = getChildNonTerminal(dataType,parent);
            applyRule(dataType_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,input_plist_node);
            input_plist_node->addr = makeNode(ID,dataType_node->addr,NULL);
            TREENODE leftFactored_input_plist_node = getChildNonTerminal(leftFactored_input_plist,input_plist_node);
            applyRule(leftFactored_input_plist_node);
            free(getChildTerminal(COLON_OPERATOR,input_plist_node));
            input_plist_node->list_addr_syn = insertAtBegin(input_plist_node->addr,leftFactored_input_plist_node->list_addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 12:{
            TREENODE leftFactored_input_plist_node = parent;
            TREENODE dataType_node = getChildNonTerminal(dataType,parent);
            applyRule(dataType_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            leftFactored_input_plist_node->addr = makeNode(ID,dataType_node->addr,NULL);
            TREENODE leftFactored_input_plist_node1 = getChildNonTerminal(leftFactored_input_plist,leftFactored_input_plist_node);
            free(getChildTerminal(COLON_OPERATOR,leftFactored_input_plist_node));
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_input_plist_node));
            leftFactored_input_plist_node->list_addr_syn = insertAtBegin(leftFactored_input_plist_node->addr,leftFactored_input_plist_node1->list_addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 13:{
            TREENODE leftFactored_input_plist_node = parent;
            leftFactored_input_plist_node -> list_addr_syn = NULL;
            free(leftFactored_input_plist_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 14:{
            TREENODE output_plist_node = parent;
            TREENODE type_node = getChildNonTerminal(type,parent);
            applyRule(type_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            output_plist_node->addr = makeNode(ID,type_node->addr,NULL);
            free(getChildTerminal(COLON_OPERATOR,output_plist_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 15:{
            TREENODE leftFactored_output_plist_node = parent;
            TREENODE type_node = getChildNonTerminal(type,parent);
            applyRule(type_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            leftFactored_output_plist_node->addr = makeNode(ID,type_node->addr,NULL);
            free(getChildTerminal(COLON_OPERATOR,leftFactored_output_plist_node));
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_output_plist_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 16:{
            TREENODE leftFactored_output_plist_node = parent;
            leftFactored_output_plist_node ->addr = NULL;
            free(leftFactored_output_plist_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 17:{
            TREENODE dataType_node = parent;
            TREENODE INTEGER = getChildTerminal(INTEGER_TYPE,parent);
            dataType_node->addr = INTEGER;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 18:{
            TREENODE dataType_node = parent;
            TREENODE REAL = getChildTerminal(REAL_TYPE,parent);
            dataType_node->addr = REAL;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 19:{
            TREENODE dataType_node = parent;
            TREENODE BOOLEAN = getChildTerminal(BOOLEAN_TYPE,parent);
            dataType_node->addr = BOOLEAN;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 20:{
            TREENODE dataType_node = parent;
            TREENODE type_node = getChildNonTerminal(type,parent);
            applyRule(type_node);
            TREENODE arrRange_node = getChildNonTerminal(arrRange,parent);
            applyRule(arrRange_node);
            TREENODE ARRAY = getChildTerminal(ARRAY_KEYWORD,dataType_node);
            dataType_node->addr = makeNode(ARRAY,type_node->addr,arrRange_node->addr_syn);
            free(getChildTerminal(OF_KEYWORD,dataType_node));
            free(getChildTerminal(SQBC_TOKEN,dataType_node));
            free(getChildTerminal(SQBO_TOKEN,dataType_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 21:{
            TREENODE arrRange_node = parent;
            TREENODE sign_node = getChildNonTerminal(sign,parent);
            applyRule(sign_node);
            arrRange_node->addr = sign_node->addr;
            TREENODE leftFactored_arrRange_node = getChildNonTerminal(leftFactored_arrRange,parent);
            leftFactored_arrRange_node->addr_inh = arrRange_node->addr;
            applyRule(leftFactored_arrRange_node);
            arrRange_node->addr_syn = leftFactored_arrRange_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 22:{
            TREENODE leftFactored_arrRange_node = parent;
            TREENODE* idNum_node = getDualNonTerminal(idNum,parent);
            TREENODE idNum1 = idNum_node[0];
            TREENODE idNum2 = idNum_node[1];
            applyRule(idNum1);
            applyRule(idNum2);
            TREENODE RANGEOP = getChildTerminal(RANGEOP_OPERATOR,leftFactored_arrRange_node);
            leftFactored_arrRange_node->addr = makeNode(RANGEOP,idNum1->addr,idNum2->addr);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 23:{
            TREENODE idNum_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            idNum_node->addr = makeNode(ID,idNum_node->addr_inh,NULL);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 24:{
            TREENODE idNum_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            idNum_node->addr = makeNode(NUM,idNum_node->addr_inh,NULL);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 25:{
            TREENODE sign_node = parent;
            TREENODE pm_node = getChildNonTerminal(pm,parent);
            applyRule(pm_node);
            sign_node->addr = pm_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 26:{
            TREENODE sign_node = parent;
            sign_node->addr = NULL;
            free(sign_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 27:{
            TREENODE type_node = parent;
            TREENODE INTEGER = getChildTerminal(INTEGER_TYPE,parent);
            type_node->addr = INTEGER;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 28:{
            TREENODE type_node = parent;
            TREENODE REAL = getChildTerminal(REAL_TYPE,parent);
            type_node->addr = REAL;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 29:{
            TREENODE type_node = parent;
            TREENODE BOOLEAN = getChildTerminal(BOOLEAN_TYPE,parent);
            type_node->addr = BOOLEAN;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 30:{
            TREENODE moduleDef_node = parent;
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            moduleDef_node->addr = statements_node->addr;
            // printf("BAMCHE SE LEKE AA GYA\n");
            free(getChildTerminal(END_KEYWORD,moduleDef_node));
            free(getChildTerminal(START_KEYWORD,moduleDef_node));
            // printf("SAHI HO GYA\n");
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 31:{
            TREENODE statements_node = parent;
            TREENODE statement_node = getChildNonTerminal(statement,parent);
            applyRule(statement_node);
            TREENODE statements_node1 = getChildNonTerminal(statements,parent);
            applyRule(statements_node1);
            statements_node->list_addr_syn = insertAtBegin(statement_node->addr,statements_node1->list_addr_syn);
            statements_node->addr = statements_node->list_addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 32:{
            TREENODE statements_node = parent;
            statements_node->list_addr_syn = NULL;
            statements_node->addr = NULL;
            // printf("FREE KR RHA HU\n");
            free(statements_node->child);
            // printf("FREE HO GYA\n");
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 33:{
            TREENODE statement_node = parent;
            TREENODE ioStmt_node = getChildNonTerminal(ioStmt,parent);
            applyRule(ioStmt_node);
            statement_node->addr = ioStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 34:{
            TREENODE statement_node = parent;
            TREENODE simpleStmt_node = getChildNonTerminal(simpleStmt,parent);
            applyRule(simpleStmt_node);
            statement_node->addr = simpleStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 35:{
            TREENODE statement_node = parent;
            TREENODE declareStmt_node = getChildNonTerminal(declareStmt,parent);
            applyRule(declareStmt_node);
            statement_node->addr = declareStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 36:{
            TREENODE statement_node = parent;
            TREENODE conditionalStmt_node = getChildNonTerminal(conditionalStmt,parent);
            applyRule(conditionalStmt_node);
            statement_node->addr = conditionalStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 37:{
            TREENODE statement_node = parent;
            TREENODE iterativeStmt_node = getChildNonTerminal(iterativeStmt,parent);
            applyRule(iterativeStmt_node);
            statement_node->addr = iterativeStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 38:{
            TREENODE ioStmt_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE GET_VALUE = getChildTerminal(GET_VALUE_KEYWORD,ioStmt_node);
            ioStmt_node->addr = makeNode(GET_VALUE,ID,NULL);
            free(getChildTerminal(SEMICOL_OPERATOR,ioStmt_node));
            free(getChildTerminal(BC_TOKEN,ioStmt_node));
            free(getChildTerminal(BO_TOKEN,ioStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 39:{
            TREENODE ioStmt_node = parent;
            TREENODE leftFactored_ioStmt_node = getChildNonTerminal(leftFactored_ioStmt,parent);
            applyRule(leftFactored_ioStmt_node);
            TREENODE PRINT = getChildTerminal(PRINT_FUNCTION,ioStmt_node);
            ioStmt_node->addr = makeNode(PRINT,leftFactored_ioStmt_node->addr,NULL);
            free(getChildTerminal(BO_TOKEN,ioStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 40:{
            TREENODE leftFactored_ioStmt_node = parent;
            TREENODE var_node = getChildNonTerminal(var,parent);
            applyRule(var_node);
            leftFactored_ioStmt_node->addr = var_node->addr;
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_ioStmt_node));
            free(getChildTerminal(BC_TOKEN,leftFactored_ioStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 41:{
            TREENODE leftFactored_ioStmt_node = parent;
            TREENODE boolValues_node = getChildNonTerminal(boolValues,parent);
            applyRule(boolValues_node);
            leftFactored_ioStmt_node->addr = boolValues_node->addr;
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_ioStmt_node));
            free(getChildTerminal(BC_TOKEN,leftFactored_ioStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 42:{
            TREENODE boolValues_node = parent;
            TREENODE TRUE = getChildTerminal(TRUE_BOOL,parent);
            boolValues_node->addr = TRUE;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 43:{
            TREENODE boolValues_node = parent;
            TREENODE FALSE = getChildTerminal(FALSE_BOOL,parent);
            boolValues_node->addr = FALSE;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 44:{
            TREENODE var_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE whichId_node = getChildNonTerminal(whichId,parent);
            applyRule(whichId_node);
            var_node->addr = makeNode(ID,whichId_node->addr_syn,whichId_node->addr);

            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 45:{
            TREENODE var_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            var_node->addr = NUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 46:{
            TREENODE var_node = parent;
            TREENODE RNUM = getChildTerminal(RNUM_TOKEN,parent);
            var_node->addr = RNUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 47:{
            TREENODE whichId_node = parent;
            TREENODE leftFactored_whichId_node = getChildNonTerminal(leftFactored_whichId,parent);
            applyRule(leftFactored_whichId_node);
            whichId_node->addr = leftFactored_whichId_node->addr;
            TREENODE sign_node = getChildNonTerminal(sign,parent);
            applyRule(sign_node);
            whichId_node->addr_syn = sign_node->addr;
            free(getChildTerminal(SQBO_TOKEN,whichId_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 48:{
            TREENODE whichId_node = parent;
            whichId_node->addr = NULL;
            whichId_node->addr_syn = NULL;
            free(whichId_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 49:{
            TREENODE leftFactored_whichId_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            leftFactored_whichId_node->addr = ID;
            free(getChildTerminal(SQBC_TOKEN,leftFactored_whichId_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 50:{
            TREENODE leftFactored_whichId_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            leftFactored_whichId_node->addr = NUM;
            free(getChildTerminal(SQBC_TOKEN,leftFactored_whichId_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 51:{
            TREENODE simpleStmt_node = parent;
            TREENODE assignmentStmt_node = getChildNonTerminal(assignmentStmt,parent);
            applyRule(assignmentStmt_node);
            simpleStmt_node->addr = assignmentStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 52:{
            TREENODE simpleStmt_node = parent;
            TREENODE moduleReuseStmt_node = getChildNonTerminal(moduleReuseStmt,parent);
            applyRule(moduleReuseStmt_node);
            simpleStmt_node->addr = moduleReuseStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 53:{
            TREENODE assignmentStmt_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE whichStmt_node = getChildNonTerminal(whichStmt,parent);
            whichStmt_node->addr_inh = ID;
            applyRule(whichStmt_node);
            assignmentStmt_node->addr = whichStmt_node->addr;

            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 54:{
            TREENODE whichStmt_node = parent;
            TREENODE lvalueIDStmt_node = getChildNonTerminal(lvalueIDStmt,parent);
            lvalueIDStmt_node->addr_inh = whichStmt_node->addr_inh;
            applyRule(lvalueIDStmt_node);
            whichStmt_node->addr = lvalueIDStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 55:{
            TREENODE whichStmt_node = parent;
            TREENODE lvalueARRStmt_node = getChildNonTerminal(lvalueARRStmt,parent);
            lvalueARRStmt_node->addr_inh = whichStmt_node->addr_inh;
            applyRule(lvalueARRStmt_node);
            whichStmt_node->addr = lvalueARRStmt_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 56:{
            TREENODE lvalueIDStmt_node = parent;
            TREENODE expression_node = getChildNonTerminal(expression,parent);
            applyRule(expression_node);
            TREENODE ASSIGNOP = getChildTerminal(ASSIGNOP_OPERATOR,parent);
            lvalueIDStmt_node->addr = makeNode(ASSIGNOP,lvalueIDStmt_node->addr_inh,expression_node->addr);
            free(getChildTerminal(SEMICOL_OPERATOR,lvalueIDStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 57:{
            TREENODE lvalueARRStmt_node = parent;
            TREENODE expression_node = getChildNonTerminal(expression,parent);
            applyRule(expression_node);
            TREENODE arithmeticExprWArr_node = getChildNonTerminal(arithmeticExprWArr,parent);
            applyRule(arithmeticExprWArr_node);
            TREENODE ASSIGNOP = getChildTerminal(ASSIGNOP_OPERATOR,parent);
            TREENODE SQBO = getChildTerminal(SQBO_TOKEN,lvalueARRStmt_node);
            TREENODE temp = makeNode(SQBO,lvalueARRStmt_node->addr_inh,arithmeticExprWArr_node->addr);
            lvalueARRStmt_node->addr = makeNode(ASSIGNOP,temp,expression_node->addr);
            free(getChildTerminal(SEMICOL_OPERATOR,lvalueARRStmt_node));
            free(getChildTerminal(SQBC_TOKEN,lvalueARRStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 58:{
            TREENODE moduleReuseStmt_node = parent;
            TREENODE optional_node = getChildNonTerminal(optional,parent);
            applyRule(optional_node);
            TREENODE paramList_node = getChildNonTerminal(paramList,parent);
            applyRule(paramList_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            moduleReuseStmt_node->addr = makeNode(ID,optional_node->addr,paramList_node->addr);
            free(getChildTerminal(SEMICOL_OPERATOR,moduleReuseStmt_node));
            free(getChildTerminal(PARAMETERS_KEYWORD,moduleReuseStmt_node));
            free(getChildTerminal(WITH_KEYWORD,moduleReuseStmt_node));
            free(getChildTerminal(MODULE_KEYWORD,moduleReuseStmt_node));
            free(getChildTerminal(USE_KEYWORD,moduleReuseStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 59:{
            TREENODE param_node = parent;
            TREENODE signedParam_node = getChildNonTerminal(signedParam,parent);
            applyRule(signedParam_node);
            TREENODE sign_node = getChildNonTerminal(sign,parent);
            applyRule(sign_node);
            // printf()
            param_node -> addr = makeNode(signedParam_node->addr,sign_node->addr,signedParam_node->addr_syn);
            // printf("%s\n",param_node->addr->TREENODEDATA->terminal->lexemedata->data);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 60:{
            TREENODE signedParam_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            // printf("gggg %s\n",ID->TREENODEDATA->terminal->lexemedata->data);
            signedParam_node->addr = ID;
            TREENODE arrID_node = getChildNonTerminal(arrID,parent);
            applyRule(arrID_node);
            signedParam_node->addr_syn = arrID_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 61:{
            TREENODE arrID_node = parent;
            TREENODE arithmeticExprWArr_node = getChildNonTerminal(arithmeticExprWArr,parent);
            applyRule(arithmeticExprWArr_node);
            arrID_node->addr = arithmeticExprWArr_node->addr;
            free(getChildTerminal(SQBC_TOKEN,arrID_node));
            free(getChildTerminal(SQBO_TOKEN,arrID_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 62:{
            TREENODE arrID_node = parent;
            arrID_node->addr = NULL;
            free(arrID_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 63:{
            TREENODE signedParam_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            signedParam_node->addr = NUM;
            signedParam_node->addr_syn = NULL;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 64:{
            TREENODE signedParam_node = parent;
            TREENODE RNUM = getChildTerminal(RNUM_TOKEN,parent);
            signedParam_node->addr = RNUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 65:{
            TREENODE param_node = parent;
            TREENODE boolValues_node = getChildNonTerminal(boolValues,parent);
            param_node->addr = boolValues_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 66:{
            TREENODE paramList_node = parent;
            TREENODE param_node = getChildNonTerminal(param,parent);
            applyRule(param_node);
            TREENODE leftFactored_paramList_node = getChildNonTerminal(leftFactored_paramList,parent);
            applyRule(leftFactored_paramList_node);
            paramList_node->list_addr_syn = insertAtBegin(param_node->addr,leftFactored_paramList_node->list_addr_syn);
            paramList_node->addr = paramList_node->list_addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 67:{
            TREENODE leftFactored_paramList_node = parent;
            TREENODE param_node = getChildNonTerminal(param,parent);
            applyRule(param_node);
            TREENODE leftFactored_paramList_node1 = getChildNonTerminal(leftFactored_paramList,parent);
            applyRule(leftFactored_paramList_node1);
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_paramList_node));
            leftFactored_paramList_node->list_addr_syn = insertAtBegin(param_node->addr,leftFactored_paramList_node1->list_addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 68:{
            TREENODE leftFactored_paramList_node = parent;
            leftFactored_paramList_node->list_addr_syn = NULL;
            free(leftFactored_paramList_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 69:{
            TREENODE optional_node = parent;
            TREENODE idList_node = getChildNonTerminal(idList,parent);
            applyRule(idList_node);
            optional_node->addr = idList_node->addr;
            free(getChildTerminal(ASSIGNOP_OPERATOR,optional_node));
            free(getChildTerminal(SQBC_TOKEN,optional_node));
            free(getChildTerminal(SQBO_TOKEN,optional_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 70:{
            TREENODE optional_node = parent;
            optional_node->addr = NULL;
            free(optional_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 71:{
            TREENODE idList_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE leftFactored_idList_node = getChildNonTerminal(leftFactored_idList,parent);
            applyRule(leftFactored_idList_node);
            idList_node->list_addr_syn = insertAtBegin(ID,leftFactored_idList_node->list_addr_syn);
            idList_node->addr = idList_node->list_addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 72:{
            TREENODE leftFactored_idList_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE leftFactored_idList_node1 = getChildNonTerminal(leftFactored_idList,parent);
            applyRule(leftFactored_idList_node1);
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_idList_node));
            leftFactored_idList_node->list_addr_syn = insertAtBegin(ID,leftFactored_idList_node1->list_addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 73:{
            TREENODE leftFactored_idList_node = parent;
            leftFactored_idList_node->list_addr_syn = NULL;
            free(leftFactored_idList_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 74:{
            TREENODE expression_node = parent;
            TREENODE arithmeticBooleanExpr_node = getChildNonTerminal(arithmeticBooleanExpr,parent);
            applyRule(arithmeticBooleanExpr_node);
            expression_node->addr = arithmeticBooleanExpr_node->addr_syn;
            // printf("%s\n",expression_node->addr->TREENODEDATA->terminal->lexemedata->data);
            // printf("%s\n",expression_node->addr->left_child->TREENODEDATA->terminal->lexemedata->data);
            // printf("%s\n",expression_node->addr->right_child->TREENODEDATA->terminal->lexemedata->data);

            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 75:{
            TREENODE expression_node = parent;
            TREENODE unaryTerm_node = getChildNonTerminal(unaryTerm,parent);
            applyRule(unaryTerm_node);
            expression_node->addr = unaryTerm_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 76:{
            TREENODE unaryTerm_node = parent;
            TREENODE pm_node = getChildNonTerminal(pm,parent);
            applyRule(pm_node);
            TREENODE arithmeticFactor_node = getChildNonTerminal(arithmeticFactor,parent);
            applyRule(arithmeticFactor_node);
            unaryTerm_node->addr = makeNode(pm_node->addr,arithmeticFactor_node->addr,NULL);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 77:{
            TREENODE arithmeticFactor_node = parent;
            TREENODE arithmeticExpr_node = getChildNonTerminal(arithmeticExpr,parent);
            applyRule(arithmeticExpr_node);
            arithmeticFactor_node->addr = arithmeticExpr_node->addr_syn;
            free(getChildTerminal(BC_TOKEN,arithmeticFactor_node));
            free(getChildTerminal(BO_TOKEN,arithmeticFactor_node));
            // printf("HO GYA 77\n");
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 78:{
            TREENODE arithmeticFactor_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            arithmeticFactor_node->addr = ID;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 79:{
            TREENODE arithmeticFactor_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            arithmeticFactor_node->addr = NUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 80:{
            TREENODE arithmeticFactor_node = parent;
            TREENODE RNUM = getChildTerminal(RNUM_TOKEN,parent);
            arithmeticFactor_node->addr = RNUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 81:{
            TREENODE arithmeticBooleanExpr_node = parent;
            TREENODE anyTerm_node = getChildNonTerminal(anyTerm,parent);
            applyRule(anyTerm_node);
            arithmeticBooleanExpr_node->addr = anyTerm_node->addr;
            TREENODE logicalTerm_node = getChildNonTerminal(logicalTerm,parent);
            logicalTerm_node->addr_inh = arithmeticBooleanExpr_node->addr;
            applyRule(logicalTerm_node);
            arithmeticBooleanExpr_node->addr_syn = logicalTerm_node->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 82:{
            TREENODE logicalTerm_node = parent;
            TREENODE logicalOp_node = getChildNonTerminal(logicalOp,parent);
            applyRule(logicalOp_node);
            TREENODE anyTerm_node = getChildNonTerminal(anyTerm,parent);
            applyRule(anyTerm_node);
            logicalTerm_node->addr = makeNode(logicalOp_node->addr,logicalTerm_node->addr_inh,anyTerm_node->addr);
            TREENODE logicalTerm_node1 = getChildNonTerminal(logicalTerm,parent);
            logicalTerm_node1->addr_inh = logicalTerm_node->addr;
            applyRule(logicalTerm_node1);
            logicalTerm_node->addr =  logicalTerm_node1->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 83:{
            TREENODE logicalTerm_node = parent;
            // printf("100\n");
            logicalTerm_node->addr_syn = logicalTerm_node->addr_inh;
            free(logicalTerm_node->child);
            // printf("FREE TO HO GYA HAI\n");
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 84:{
            TREENODE anyTerm_node = parent;
            TREENODE arithmeticExpr_node = getChildNonTerminal(arithmeticExpr,parent);
            applyRule(arithmeticExpr_node);
            anyTerm_node->addr_syn = arithmeticExpr_node->addr_syn;
            TREENODE relationalTerm_node = getChildNonTerminal(relationalTerm,parent);
            relationalTerm_node->addr_inh = anyTerm_node->addr_syn;
            applyRule(relationalTerm_node);
            anyTerm_node->addr = relationalTerm_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 85:{
            TREENODE relationalTerm_node = parent;
            TREENODE relationalOp_node = getChildNonTerminal(relationalOp,parent);
            applyRule(relationalOp_node);
            TREENODE arithmeticExpr_node = getChildNonTerminal(arithmeticExpr,parent);
            applyRule(arithmeticExpr_node);
            relationalTerm_node->addr = makeNode(relationalOp_node->addr,relationalTerm_node->addr_inh,arithmeticExpr_node->addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 86:{
            TREENODE relationalTerm_node = parent;
            relationalTerm_node->addr = relationalTerm_node->addr_inh;
            free(relationalTerm_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 87:{
            TREENODE arithmeticExpr_node = parent;
            TREENODE term_node = getChildNonTerminal(term,parent);
            applyRule(term_node);
            arithmeticExpr_node->addr = term_node->addr_syn;
            TREENODE leftFactored_arithmeticExpr_node = getChildNonTerminal(leftFactored_arithmeticExpr,parent);
            leftFactored_arithmeticExpr_node->addr_inh = arithmeticExpr_node->addr;
            applyRule(leftFactored_arithmeticExpr_node);
            arithmeticExpr_node->addr_syn = leftFactored_arithmeticExpr_node->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 88:{
            TREENODE leftFactored_arithmeticExpr_node = parent;
            TREENODE pm_node = getChildNonTerminal(pm,parent);
            applyRule(pm_node);
            TREENODE term_node = getChildNonTerminal(term,parent);
            applyRule(term_node);
            leftFactored_arithmeticExpr_node->addr = makeNode(pm_node->addr,leftFactored_arithmeticExpr_node->addr_inh,term_node->addr_syn);
            TREENODE leftFactored_arithmeticExpr_node1 = getChildNonTerminal(leftFactored_arithmeticExpr,parent);
            leftFactored_arithmeticExpr_node1->addr_inh = leftFactored_arithmeticExpr_node->addr;
            applyRule(leftFactored_arithmeticExpr_node1);
            leftFactored_arithmeticExpr_node->addr_syn = leftFactored_arithmeticExpr_node1->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 89:{
            TREENODE leftFactored_arithmeticExpr_node = parent;
            leftFactored_arithmeticExpr_node->addr_syn = leftFactored_arithmeticExpr_node->addr_inh;
            free(leftFactored_arithmeticExpr_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 90:{
            TREENODE pm_node = parent;
            TREENODE PLUS = getChildTerminal(PLUS_OPERATOR,parent);
            pm_node->addr = PLUS;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 91:{
            TREENODE pm_node = parent;
            TREENODE MINUS = getChildTerminal(MINUS_OPERATOR,parent);
            pm_node->addr = MINUS;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 92:{
            TREENODE md_node = parent;
            TREENODE MUL = getChildTerminal(MUL_OPERATOR,parent);
            md_node->addr = MUL;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 93:{
            TREENODE md_node = parent;
            TREENODE DIV = getChildTerminal(DIV_OPERATOR,parent);
            md_node->addr = DIV;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 94:{
            TREENODE term_node = parent;
            TREENODE factor_node = getChildNonTerminal(factor,parent);
            applyRule(factor_node);
            term_node->addr = factor_node->addr;
            TREENODE leftFactored_term_node = getChildNonTerminal(leftFactored_term,parent);
            leftFactored_term_node->addr_inh = term_node->addr;
            applyRule(leftFactored_term_node);
            term_node->addr_syn = leftFactored_term_node->addr_syn;
            // printf("%s\n",term_node->addr_syn)
            // printf("ENDING RULE %d\n",ruleNum);
            free(factor_node);
            break;
        }
        case 95:{
            TREENODE leftFactored_term_node = parent;
            TREENODE factor_node = getChildNonTerminal(factor,parent);
            applyRule(factor_node);
            TREENODE md_node = getChildNonTerminal(md,parent);
            applyRule(md_node);

            // if(factor_node->addr->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN)printf("%s\n",factor_node->addr->TREENODEDATA->terminal->lexemedata->data);
            // if(factor_node->addr->TREENODEDATA->terminal->token == NUM_TOKEN)printf("%d\n",factor_node->addr->TREENODEDATA->terminal->lexemedata->intData);
            // if(factor_node->addr->TREENODEDATA->terminal->token == RNUM_TOKEN)printf("%f\n",factor_node->addr->TREENODEDATA->terminal->lexemedata->floatData);
            
            
            leftFactored_term_node->addr = makeNode(md_node->addr,leftFactored_term_node->addr_inh,factor_node->addr);
            // printf("HGHGHG\n");
            TREENODE leftFactored_term_node1 = getChildNonTerminal(leftFactored_term,parent);
            leftFactored_term_node1->addr_inh = leftFactored_term_node->addr;
            applyRule(leftFactored_term_node1);
            leftFactored_term_node->addr_syn = leftFactored_term_node1->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            free(factor_node);
            free(md_node);
            break;
        }
        case 96:{
            TREENODE leftFactored_term_node = parent;
            leftFactored_term_node->addr_syn = leftFactored_term_node->addr_inh;
            free(leftFactored_term_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 97:{
            TREENODE factor_node = parent;
            TREENODE arithmeticBooleanExpr_node = getChildNonTerminal(arithmeticBooleanExpr,parent);
            applyRule(arithmeticBooleanExpr_node);
            factor_node->addr = arithmeticBooleanExpr_node->addr;
            free(getChildTerminal(BC_TOKEN,factor_node));
            free(getChildTerminal(BO_TOKEN,factor_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 98:{
            TREENODE factor_node = parent;
            TREENODE param_node = getChildNonTerminal(param,parent);
            applyRule(param_node);
            factor_node->addr = param_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 99:{
            TREENODE arithmeticExprWArr_node = parent;
            TREENODE termWArr_node = getChildNonTerminal(termWArr,parent);
            applyRule(termWArr_node);
            arithmeticExprWArr_node->addr = termWArr_node->addr;
            TREENODE leftFactored_arithmeticExprWArr_node = getChildNonTerminal(leftFactored_arithmeticExprWArr,parent);
            leftFactored_arithmeticExprWArr_node->addr_inh = arithmeticExprWArr_node->addr;
            applyRule(leftFactored_arithmeticExprWArr_node);
            arithmeticExprWArr_node->addr_syn = leftFactored_arithmeticExprWArr_node->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 100:{
            TREENODE leftFactored_arithmeticExprWArr_node = parent;
            TREENODE pm_node = getChildNonTerminal(pm,parent);
            applyRule(pm_node);
            TREENODE termWArr_node = getChildNonTerminal(termWArr,parent);
            applyRule(termWArr_node);
            leftFactored_arithmeticExprWArr_node->addr = makeNode(pm_node->addr,leftFactored_arithmeticExprWArr_node->addr_inh,termWArr_node->addr_syn);
            TREENODE leftFactored_arithmeticExprWArr_node1 = getChildNonTerminal(leftFactored_arithmeticExprWArr,parent);
            leftFactored_arithmeticExprWArr_node1->addr_inh = leftFactored_arithmeticExprWArr_node->addr;
            applyRule(leftFactored_arithmeticExprWArr_node1);
            leftFactored_arithmeticExprWArr_node->addr_syn = leftFactored_arithmeticExprWArr_node1->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 101:{
            TREENODE leftFactored_arithmeticExprWArr_node = parent;
            leftFactored_arithmeticExprWArr_node->addr_syn = leftFactored_arithmeticExprWArr_node->addr_inh;
            free(leftFactored_arithmeticExprWArr_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 102:{
            TREENODE termWArr_node = parent;
            TREENODE signedFactorWArr_node = getChildNonTerminal(signedFactorWArr,parent);
            applyRule(signedFactorWArr_node);
            termWArr_node->addr = signedFactorWArr_node->addr;
            TREENODE leftFactored_termWArr_node = getChildNonTerminal(leftFactored_termWArr,parent);
            leftFactored_termWArr_node->addr_inh = termWArr_node->addr;
            applyRule(leftFactored_termWArr_node);
            termWArr_node->addr_syn = leftFactored_termWArr_node->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 103:{
            TREENODE leftFactored_termWArr_node = parent;
            TREENODE md_node = getChildNonTerminal(md,parent);
            TREENODE signedFactorWArr_node = getChildNonTerminal(signedFactorWArr,parent);
            applyRule(md_node);
            applyRule(signedFactorWArr_node);
            leftFactored_termWArr_node->addr = makeNode(md_node->addr,leftFactored_termWArr_node->addr_inh,signedFactorWArr_node->addr);
            TREENODE leftFactored_termWArr_node1 = getChildNonTerminal(leftFactored_termWArr,parent);
            leftFactored_termWArr_node1->addr_inh = leftFactored_termWArr_node->addr;
            applyRule(leftFactored_termWArr_node1);
            leftFactored_termWArr_node->addr_syn = leftFactored_termWArr_node1->addr_syn;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 104:{
            TREENODE leftFactored_termWArr_node = parent;
            leftFactored_termWArr_node->addr_syn = leftFactored_termWArr_node->addr_inh;            
            free(leftFactored_termWArr_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 105:{
            TREENODE signedFactorWArr_node = parent;
            TREENODE sign_node = getChildNonTerminal(sign,parent);
            applyRule(sign_node);
            TREENODE factorWArr_node = getChildNonTerminal(factorWArr,parent);
            applyRule(factorWArr_node);
            signedFactorWArr_node->addr = makeNode(factorWArr_node->addr,sign_node->addr,NULL);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 106:{
            TREENODE factorWArr_node = parent;
            TREENODE arithmeticExprWArr_node = getChildNonTerminal(arithmeticExprWArr,parent);
            applyRule(arithmeticExprWArr_node);
            factorWArr_node->addr = arithmeticExprWArr_node->addr_syn;
            free(getChildTerminal(BC_TOKEN,factorWArr_node));
            free(getChildTerminal(BO_TOKEN,factorWArr_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 107:{
            TREENODE factorWArr_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            factorWArr_node->addr = ID;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 108:{
            TREENODE factorWArr_node = parent;
            TREENODE RNUM = getChildTerminal(RNUM_TOKEN,parent);
            factorWArr_node->addr = RNUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 109:{
            TREENODE factorWArr_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            factorWArr_node->addr = NUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 110:{
            TREENODE logicalOp_node = parent;
            TREENODE AND = getChildTerminal(AND_OPERATOR,parent);
            logicalOp_node->addr = AND;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 111:{
            TREENODE logicalOp_node = parent;
            TREENODE OR = getChildTerminal(OR_OPERATOR,parent);
            logicalOp_node->addr = OR;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 112:{
            TREENODE relationalOp_node = parent;
            TREENODE LT = getChildTerminal(LT_OPERATOR,parent);
            relationalOp_node->addr = LT;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 113:{
            TREENODE relationalOp_node = parent;
            TREENODE LE = getChildTerminal(LE_OPERATOR,parent);
            relationalOp_node->addr = LE;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 114:{
            TREENODE relationalOp_node = parent;
            TREENODE GT = getChildTerminal(GT_OPERATOR,parent);
            relationalOp_node->addr = GT;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 115:{
            TREENODE relationalOp_node = parent;
            TREENODE GE = getChildTerminal(GE_OPERATOR,parent);
            relationalOp_node->addr = GE;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 116:{
            TREENODE relationalOp_node = parent;
            TREENODE EQ = getChildTerminal(EQ_OPERATOR,parent);
            relationalOp_node->addr = EQ;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 117:{
            TREENODE relationalOp_node = parent;
            TREENODE NE = getChildTerminal(NE_OPERATOR,parent);
            relationalOp_node->addr = NE;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 118:{
            TREENODE declareStmt_node = parent;
            TREENODE idList_node = getChildNonTerminal(idList,parent);
            applyRule(idList_node);
            TREENODE dataType_node = getChildNonTerminal(dataType,parent);
            applyRule(dataType_node);
            TREENODE DECLARE = getChildTerminal(DECLARE_KEYWORD,parent);
            declareStmt_node->addr = makeNode(DECLARE,idList_node->addr,dataType_node->addr);
            free(getChildTerminal(SEMICOL_OPERATOR,declareStmt_node));
            free(getChildTerminal(COLON_OPERATOR,declareStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 119:{
            TREENODE conditionalStmt_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE caseStmt_node = getChildNonTerminal(caseStmt,parent);
            applyRule(caseStmt_node);
            TREENODE dfault_node = getChildNonTerminal(dfault,parent);
            applyRule(dfault_node);
            conditionalStmt_node->addr = makeNode(ID,caseStmt_node,dfault_node);
            free(getChildTerminal(END_KEYWORD,conditionalStmt_node));
            free(getChildTerminal(START_KEYWORD,conditionalStmt_node));
            free(getChildTerminal(BC_TOKEN,conditionalStmt_node));
            free(getChildTerminal(BO_TOKEN,conditionalStmt_node));
            free(getChildTerminal(SWITCH_KEYWORD,conditionalStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 120:{
            TREENODE caseStmt_node = parent;
            TREENODE value_node = getChildNonTerminal(value,parent);
            applyRule(value_node);
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            caseStmt_node->addr = makeNode(value_node->addr,statements_node->addr,NULL);
            TREENODE leftFactored_caseStmt_node = getChildNonTerminal(leftFactored_caseStmt,parent);
            applyRule(leftFactored_caseStmt_node);
            free(getChildTerminal(SEMICOL_OPERATOR,caseStmt_node));
            free(getChildTerminal(BREAK_KEYWORD,caseStmt_node));
            free(getChildTerminal(COLON_OPERATOR,caseStmt_node));
            free(getChildTerminal(CASE_KEYWORD,caseStmt_node));
            caseStmt_node->list_addr_syn = insertAtBegin(caseStmt_node->addr,leftFactored_caseStmt_node->list_addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 121:{
            TREENODE leftFactored_caseStmt_node = parent;
            TREENODE value_node = getChildNonTerminal(value,parent);
            applyRule(value_node);
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            leftFactored_caseStmt_node->addr = makeNode(value_node->addr,statements_node->addr,NULL);
            TREENODE leftFactored_caseStmt_node1 = getChildNonTerminal(leftFactored_caseStmt,parent);
            applyRule(leftFactored_caseStmt_node1);
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_caseStmt_node));
            free(getChildTerminal(BREAK_KEYWORD,leftFactored_caseStmt_node));
            free(getChildTerminal(COLON_OPERATOR,leftFactored_caseStmt_node));
            free(getChildTerminal(CASE_KEYWORD,leftFactored_caseStmt_node));
            leftFactored_caseStmt_node->list_addr_syn = insertAtBegin(leftFactored_caseStmt_node->addr,leftFactored_caseStmt_node1->list_addr_syn);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 122:{
            TREENODE leftFactored_caseStmt_node = parent;
            leftFactored_caseStmt_node->list_addr_syn = NULL;
            free(leftFactored_caseStmt_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 123:{
            TREENODE value_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            value_node->addr = NUM;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 124:{
            TREENODE value_node = parent;
            TREENODE boolValues_node = getChildNonTerminal(boolValues,parent);
            applyRule(boolValues_node);
            value_node->addr = boolValues_node->addr;
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 125:{
            TREENODE dfault_node = parent;
            TREENODE DEFAULT = getChildTerminal(DEFAULT_KEYWORD,dfault_node);
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            dfault_node->addr = makeNode(DEFAULT,statements_node->addr,NULL);
            free(getChildTerminal(SEMICOL_OPERATOR,dfault_node));
            free(getChildTerminal(BREAK_KEYWORD,dfault_node));
            free(getChildTerminal(COLON_OPERATOR,dfault_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 126:{
            TREENODE dfault_node = parent;
            dfault_node->addr = NULL;
            free(dfault_node->child);
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 127:{
            TREENODE iterativeStmt_node = parent;
            TREENODE FOR = getChildTerminal(FOR_KEYWORD,iterativeStmt_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            TREENODE* NUM = getDualTerminal(NUM_TOKEN,parent);
            TREENODE* sign_node = getDualNonTerminal(sign,parent);
            TREENODE sign1 = sign_node[0];
            applyRule(sign1);
            TREENODE sign2 = sign_node[1];
            applyRule(sign2);
            TREENODE NUM1 = NUM[0];
            TREENODE NUM2 = NUM[1];
            TREENODE temp1 = makeNode(NUM1,sign1->addr,NULL);
            TREENODE temp2 = makeNode(NUM2,sign2->addr,NULL);
            TREENODE temp3 = makeNode(ID,temp1,temp2);
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            iterativeStmt_node->addr = makeNode(FOR,temp3,statements_node);
            free(getChildTerminal(END_KEYWORD,iterativeStmt_node));
            free(getChildTerminal(START_KEYWORD,iterativeStmt_node));
            free(getChildTerminal(BC_TOKEN,iterativeStmt_node));
            free(getChildTerminal(RANGEOP_OPERATOR,iterativeStmt_node));
            free(getChildTerminal(IN_KEYWORD,iterativeStmt_node));
            free(getChildTerminal(BO_TOKEN,iterativeStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
        case 128:{
            TREENODE iterativeStmt_node = parent;
            TREENODE WHILE = getChildTerminal(WHILE_KEYWORD,iterativeStmt_node);
            TREENODE arithmeticBooleanExpr_node = getChildNonTerminal(arithmeticBooleanExpr,parent);
            applyRule(arithmeticBooleanExpr_node);
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            iterativeStmt_node->addr = makeNode(WHILE,arithmeticBooleanExpr_node->addr,statements_node->addr);
            free(getChildTerminal(END_KEYWORD,iterativeStmt_node));
            free(getChildTerminal(START_KEYWORD,iterativeStmt_node));
            free(getChildTerminal(BC_TOKEN,iterativeStmt_node));
            free(getChildTerminal(BO_TOKEN,iterativeStmt_node));
            // printf("ENDING RULE %d\n",ruleNum);
            break;
        }
    }
    if(parent->addr != NULL){
        if(parent->addr->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%s addr : %d\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->addr->TREENODEDATA->terminal->lexemedata->intData);
        else if(parent->addr->TREENODEDATA->terminal->token == RNUM_TOKEN) printf("%s addr : %f\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->addr->TREENODEDATA->terminal->lexemedata->floatData);
        else if(parent->addr->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s addr : %s\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->addr->TREENODEDATA->terminal->lexemedata->data);
        else printf("%s addr : %s\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->addr->TREENODEDATA->terminal->lexemedata->data);
    }
    else{
        printf("%s addr : NULL\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal]);
    }
    if(parent->list_addr_syn != NULL){
        if(parent->list_addr_syn->TREENODEDATA->terminal->token == NUM_TOKEN) printf("%s list_addr_syn : %d\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->list_addr_syn->TREENODEDATA->terminal->lexemedata->intData);
        else if(parent->list_addr_syn->TREENODEDATA->terminal->token == RNUM_TOKEN) printf("%s list_addr_syn : %f\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->list_addr_syn->TREENODEDATA->terminal->lexemedata->floatData);
        else if(parent->list_addr_syn->TREENODEDATA->terminal->token == IDENTIFIER_TOKEN) printf("%s list_addr_syn : %s\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->list_addr_syn->TREENODEDATA->terminal->lexemedata->data);
        else printf("%s list_addr_syn : %s\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal],parent->list_addr_syn->TREENODEDATA->terminal->lexemedata->data);
    }
    else{
        printf("%s list_addr_syn : NULL\n",NONTERMINALS_STRINGS[parent->TREENODEDATA->nonterminal]);
    }
    printf("ENDING RULE %d\n\n______________________________\n\n",ruleNum);
}

