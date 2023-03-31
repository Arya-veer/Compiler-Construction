#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"
#include "parser.h"

TREENODE makeNode(char* nodeName,TREENODE left,TREENODE right,TREENODE assign,int which){
    if(which == 1){
        assign->left_child = left;
        assign->right_child = right;
        return assign;
    }
    TREENODE tn = (TREENODE) malloc(sizeof(struct TreeNode));
    tn->isTerminal=which;
    tn->TREENODEDATA = malloc(sizeof(union TreeNodeData));
    tn->TREENODEDATA->nodeName = nodeName;
    tn->left_child = left;
    tn->right_child = right;
    tn->addr = NULL;
    tn->next = NULL;
    tn->parent = NULL;
    tn->ruleNum = -1;
    return tn;
}

void applyRule(TREENODE parent){

    int ruleNum = parent->child->ruleNum;

    switch(ruleNum){
        case 0: {
            TREENODE finalProgram_node = parent;
            TREENODE program_node = getChildNonTerminal(program,finalProgram_node); 
            applyRule(program);
            finalProgram_node->addr = program_node->addr;
            TREENODE eof_node = getChildTerminal(EOF_TOKEN,finalProgram_node);
            free(eof_node);
            break;
        }
        case 1:{

        }
        case 2:{
            TREENODE moduleDeclarations_node = parent;
            TREENODE moduleDeclaration_node = getChildNonTerminal(moduleDeclaration,moduleDeclarations_node);
            TREENODE moduleDeclarations1_node = getChildNonTerminal(moduleDeclarations,moduleDeclarations_node);
            applyRule(moduleDeclaration);
            applyRule(moduleDeclarations1_node);
            moduleDeclarations_node->list_addr_syn = insertAtBegin(moduleDeclaration_node->addr,moduleDeclarations1_node->list_addr_syn);
            moduleDeclarations_node->addr=moduleDeclarations_node->list_addr_syn;
            break;
        }
        case 3:{
            TREENODE moduleDeclarations_node = parent;
            moduleDeclarations_node->list_addr_syn = NULL;
            free(moduleDeclarations_node->child);
            break;
        }
        case 4:{
            TREENODE moduleDeclaration_node = parent;
            moduleDeclaration_node->addr = getChildTerminal(IDENTIFIER_TOKEN,moduleDeclaration_node);
            free(getChildTerminal(DECLARE_KEYWORD,moduleDeclaration_node));
            free(getChildTerminal(SEMICOL_OPERATOR,moduleDeclaration_node));
            free(getChildTerminal(MODULE_KEYWORD,moduleDeclaration_node));
            break;
        }
        case 5:{
            TREENODE otherModules_node = parent;
            TREENODE module_node = getChildNonTerminal(module,otherModules_node);
            applyRule(module_node);
            TREENODE otherModules1 = getChildNonTerminal(otherModules,otherModules_node); 
            applyRule(otherModules1);
            otherModules_node->list_addr_syn = insertAtBegin(module_node->addr,otherModules1->list_addr_syn);
            otherModules_node->addr = otherModules_node->list_addr_syn;
            break;
        }
        case 6:{
            TREENODE otherModules_node = parent;
            otherModules_node->list_addr_syn = NULL;
            free(otherModules_node->child);
            break;
        }
        case 7:{
            TREENODE driverModule_node = parent;
            TREENODE moduleDef_node = getChildNonTerminal(moduleDef,driverModule_node);
            applyRule(moduleDef_node);
            driverModule_node->addr = moduleDef_node->addr;
            free(getChildTerminal(DRIVERDEF_OPERATOR,driverModule_node));
            free(getChildTerminal(DRIVERENDDEF_OPERATOR,driverModule_node));
            free(getChildTerminal(PROGRAM_KEYWORD,driverModule_node));
            free(getChildTerminal(DRIVER_KEYWORD,driverModule_node));
            break;
        }
        case 8:{
            TREENODE module_node = parent;
            TREENODE input_plist_node = getChildNonTerminal(input_plist,module_node);
            applyRule(input_plist_node);
            TREENODE ret_node = getChildNonTerminal(ret,module_node);
            applyRule(ret_node);
            TREENODE temp = makeNode("PARAMETERS",input_plist_node->addr,ret_node->addr,NULL,2);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,module_node);
            TREENODE moduleDef_node = getChildNonTerminal(moduleDef,module_node);
            applyRule(moduleDef_node);
            module_node->addr = makeNode("ID",temp,moduleDef_node->addr,ID->addr,1);
            free(getChildTerminal(DEF_OPERATOR,module_node));
            free(getChildTerminal(MODULE_KEYWORD,module_node));
            free(getChildTerminal(ENDDEF_OPERATOR,module_node));
            free(getChildTerminal(TAKES_KEYWORD,module_node));
            free(getChildTerminal(INPUT_KEYWORD,module_node));
            free(getChildTerminal(SQBO_TOKEN,module_node));
            free(getChildTerminal(SQBC_TOKEN,module_node));
            free(getChildTerminal(SEMICOL_OPERATOR,module_node));
            break;
        }
        case 9:{
            TREENODE ret_node = parent;
            TREENODE output_plist_node = getChildNonTerminal(output_plist,ret_node);
            applyRule(output_plist_node);
            ret_node->addr = output_plist_node->addr;
            free(getChildTerminal(RETURNS_KEYWORD,ret_node));
            free(getChildTerminal(SQBO_TOKEN,ret_node));
            free(getChildTerminal(SQBC_TOKEN,ret_node));
            free(getChildTerminal(SEMICOL_OPERATOR,ret_node));
            break;
        }
        case 10:{
            TREENODE ret_node = parent;
            ret_node->addr = NULL;
            free(ret_node->child);
            break;
        }
        case 11:{
            TREENODE input_plist_node = parent;
            TREENODE dataType_node = getChildNonTerminal(dataType,parent);
            applyRule(dataType_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,input_plist_node);
            input_plist_node->addr = makeNode("ID",dataType_node->addr,NULL,ID->addr,1);
            TREENODE leftFactored_input_plist_node = getChildNonTerminal(leftFactored_input_plist,input_plist_node);
            applyRule(leftFactored_input_plist_node);
            input_plist_node->list_addr_syn = insertAtBegin(input_plist_node->addr,leftFactored_input_plist_node->list_addr_syn);
            free(getChildTerminal(IDENTIFIER_TOKEN,input_plist));
            free(getChildTerminal(COLON_OPERATOR,input_plist));
            break;
        }
        case 12:{
            TREENODE leftFactored_input_plist_node = parent;
            TREENODE dataType_node = getChildNonTerminal(dataType,parent);
            applyRule(dataType_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            leftFactored_input_plist_node->addr = makeNode("ID",dataType_node->addr,NULL,ID->addr,1);
            TREENODE leftFactored_input_plist_node1 = getChildNonTerminal(leftFactored_input_plist,leftFactored_input_plist_node);
            leftFactored_input_plist_node->list_addr_syn = insertAtBegin(leftFactored_input_plist_node->addr,leftFactored_input_plist_node1->list_addr_syn);
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_input_plist_node));
            free(getChildTerminal(IDENTIFIER_TOKEN,leftFactored_input_plist_node));
            free(getChildTerminal(COLON_OPERATOR,leftFactored_input_plist_node));
            break;
        }
        case 13:{
            TREENODE leftFactored_input_plist_node = parent;
            leftFactored_input_plist_node -> list_addr_syn = NULL;
            free(leftFactored_input_plist_node->child);
            break;
        }
        case 14:{
            TREENODE output_plist_node = parent;
            TREENODE type_node = getChildNonTerminal(type,parent);
            applyRule(type_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            output_plist_node->addr = makeNode("ID",type_node->addr,NULL,ID->addr,1);
            free(getChildTerminal(IDENTIFIER_TOKEN,output_plist_node));
            free(getChildTerminal(COLON_OPERATOR,output_plist_node));
            break;
        }
        case 15:{
            TREENODE leftFactored_output_plist_node = parent;
            TREENODE type_node = getChildNonTerminal(type,parent);
            applyRule(type_node);
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            leftFactored_output_plist_node->addr = makeNode("ID",type_node->addr,NULL,ID->addr,1);
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_output_plist_node));
            free(getChildTerminal(IDENTIFIER_TOKEN,leftFactored_output_plist_node));
            free(getChildTerminal(COLON_OPERATOR,leftFactored_output_plist_node));
            break;
        }
        case 16:{
            TREENODE leftFactored_output_plist_node = parent;
            leftFactored_output_plist_node ->addr = NULL;
            free(leftFactored_output_plist_node->child);
            break;
        }
        case 17:{
            TREENODE dataType_node = parent;
            TREENODE INTEGER = getChildTerminal(INTEGER_TYPE,parent);
            dataType_node->addr = INTEGER->addr;
            break;
        }
        case 18:{
            TREENODE dataType_node = parent;
            TREENODE REAL = getChildTerminal(REAL_TYPE,parent);
            dataType_node->addr = REAL->addr;
            break;
        }
        case 19:{
            TREENODE dataType_node = parent;
            TREENODE BOOLEAN = getChildTerminal(BOOLEAN_TYPE,parent);
            dataType_node->addr = BOOLEAN->addr;
            break;
        }
        case 20:{
            TREENODE dataType_node = parent;
            TREENODE type_node = getChildNonTerminal(type,parent);
            applyRule(type_node);
            TREENODE arrRange_node = getChildNonTerminal(arrRange,parent);
            applyRule(arrRange_node);
            dataType_node->addr = makeNode("ARRAY",type_node->addr,arrRange_node->addr_syn,NULL,2);
            free(getChildTerminal(ARRAY_KEYWORD,dataType_node));
            free(getChildTerminal(SQBO_TOKEN,dataType_node));
            free(getChildTerminal(SQBC_TOKEN,dataType_node));
            free(getChildTerminal(OF_KEYWORD,dataType_node));
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
            break;
        }
        case 22:{
            /*
            TODO: 
            */
            TREENODE leftFactored_arrRange = parent;
            free(getChildTerminal(RANGEOP_OPERATOR,leftFactored_arrRange));
            break;
        }
        case 23:{
            TREENODE idNum_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            idNum_node->addr = makeNode("ID",idNum_node->addr_inh,NULL,ID->addr,1);
            break;
        }
        case 24:{
            TREENODE idNum_node = parent;
            TREENODE NUM = getChildTerminal(NUM_TOKEN,parent);
            idNum_node->addr = makeNode("NUM",idNum_node->addr_inh,NULL,NUM->addr,1);
            break;
        }
        case 25:{
            TREENODE sign_node = parent;
            TREENODE pm_node = getChildNonTerminal(pm,parent);
            sign_node->addr = pm_node->addr;
            break;
        }
        case 26:{
            TREENODE sign_node = parent;
            sign_node->addr = NULL;
            free(sign_node->child);
            break;
        }
        case 27:{
            TREENODE type_node = parent;
            TREENODE INTEGER = getChildTerminal(INTEGER_TYPE,parent);
            type_node->addr = INTEGER->addr;
            break;
        }
        case 28:{
            TREENODE type_node = parent;
            TREENODE REAL = getChildTerminal(REAL_TYPE,parent);
            type_node->addr = REAL->addr;
            break;
        }
        case 29:{
            TREENODE type_node = parent;
            TREENODE BOOLEAN = getChildTerminal(BOOLEAN_TYPE,parent);
            type_node->addr = BOOLEAN->addr;
            break;
        }
        case 30:{
            TREENODE moduleDef_node = parent;
            TREENODE statements_node = getChildNonTerminal(statements,parent);
            applyRule(statements_node);
            moduleDef_node->addr = statements_node->addr;
            free(getChildTerminal(START_KEYWORD,moduleDef_node));
            free(getChildTerminal(END_KEYWORD,moduleDef_node));
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
            break;
        }
        case 32:{
            TREENODE statements_node = parent;
            statements_node->list_addr_syn = NULL;
            free(statements_node->child);
            break;
        }
        case 33:{
            TREENODE statement_node = parent;
            TREENODE ioStmt_node = getChildNonTerminal(ioStmt,parent);
            statement_node->addr = ioStmt_node->addr;
            break;
        }
        case 34:{
            TREENODE statement_node = parent;
            TREENODE simpleStmt_node = getChildNonTerminal(simpleStmt,parent);
            statement_node->addr = simpleStmt_node->addr;
            break;
        }
        case 35:{
            TREENODE statement_node = parent;
            TREENODE declareStmt_node = getChildNonTerminal(declareStmt,parent);
            statement_node->addr = declareStmt_node->addr;
            break;
        }
        case 36:{
            TREENODE statement_node = parent;
            TREENODE conditionalStmt_node = getChildNonTerminal(conditionalStmt,parent);
            statement_node->addr = conditionalStmt_node->addr;
            break;
        }
        case 37:{
            TREENODE statement_node = parent;
            TREENODE iterativeStmt_node = getChildNonTerminal(iterativeStmt,parent);
            statement_node->addr = iterativeStmt_node->addr;
            break;
        }
        case 38:{
            TREENODE ioStmt_node = parent;
            TREENODE ID = getChildTerminal(IDENTIFIER_TOKEN,parent);
            ioStmt_node->addr = makeNode("GET_VALUE",ID->addr,NULL,NULL,2);
            free(getChildTerminal(GET_VALUE_KEYWORD,ioStmt_node));
            free(getChildTerminal(BO_TOKEN,ioStmt_node));
            free(getChildTerminal(BC_TOKEN,ioStmt_node));
            free(getChildTerminal(SEMICOL_OPERATOR,ioStmt_node));
            break;
        }
        case 39:{
            TREENODE ioStmt_node = parent;
            TREENODE leftFactored_ioStmt_node = getChildNonTerminal(leftFactored_ioStmt,parent);
            applyRule(leftFactored_ioStmt_node);
            ioStmt_node->addr = makeNode("PRINT",leftFactored_ioStmt_node->addr,NULL,NULL,2);
            free(getChildTerminal(PRINT_FUNCTION,ioStmt_node));
            free(getChildTerminal(BO_TOKEN,ioStmt_node));
            break;
        }
        case 40:{
            TREENODE leftFactored_ioStmt_node = parent;
            TREENODE var_node = getChildNonTerminal(var,parent);
            applyRule(var_node);
            leftFactored_ioStmt_node->addr = var_node->addr;
            free(getChildTerminal(BC_TOKEN,leftFactored_ioStmt_node));
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_ioStmt_node));
            break;
        }
        case 41:{
            TREENODE leftFactored_ioStmt_node = parent;
            
            free(getChildTerminal(BC_TOKEN,leftFactored_ioStmt_node));
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_ioStmt_node));
            break;
        }
        case 42:{
            TREENODE boolValues = parent;
            break;
        }
        case 43:{
            TREENODE boolValues = parent;
            break;
        }
        case 44:{
            TREENODE var = parent;
            free(getChildTerminal(IDENTIFIER_TOKEN,var));
            break;
        }
        case 45:{
            TREENODE var = parent;
            break;
        }
        case 46:{
            TREENODE var = parent;
            break;
        }
        case 47:{
            TREENODE whichId = parent;
            free(getChildTerminal(SQBO_TOKEN,whichId));
            break;
        }
        case 48:{
            TREENODE whichId = parent;
            free(whichId->child);
            break;
        }
        case 49:{
            TREENODE leftFactored_whichId = parent;
            free(getChildTerminal(SQBC_TOKEN,leftFactored_whichId));
            break;
        }
        case 50:{
            TREENODE leftFactored_whichId = parent;
            free(getChildTerminal(SQBC_TOKEN,leftFactored_whichId));
            break;
        }
        case 51:{
            TREENODE simpleStmt = parent;
            break;
        }
        case 52:{
            TREENODE simpleStmt = parent;
            break;
        }
        case 53:{
            TREENODE assignmentStmt = parent;
            break;
        }
        case 54:{
            TREENODE whichStmt = parent;
            break;
        }
        case 55:{
            TREENODE whichStmt = parent;
            break;
        }
        case 56:{
            TREENODE lvalueIDStmt = parent;
            free(getChildTerminal(ASSIGNOP_OPERATOR,lvalueIDStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,lvalueIDStmt));
            break;
        }
        case 57:{
            TREENODE lvalueARRStmt = parent;
            free(getChildTerminal(SQBO_TOKEN,lvalueARRStmt));
            free(getChildTerminal(SQBC_TOKEN,lvalueARRStmt));
            free(getChildTerminal(ASSIGNOP_OPERATOR,lvalueARRStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,lvalueARRStmt));
            break;
        }
        case 58:{
            TREENODE moduleReuseStmt = parent;
            free(getChildTerminal(USE_KEYWORD,moduleReuseStmt));
            free(getChildTerminal(MODULE_KEYWORD,moduleReuseStmt));
            free(getChildTerminal(IDENTIFIER_TOKEN,moduleReuseStmt));
            free(getChildTerminal(WITH_KEYWORD,moduleReuseStmt));
            free(getChildTerminal(PARAMETERS_KEYWORD,moduleReuseStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,moduleReuseStmt));
            break;
        }
        case 59:{
            TREENODE param = parent;
            break;
        }
        case 60:{
            TREENODE signedParam = parent;
            break;
        }
        case 61:{
            TREENODE arrID = parent;
            free(getChildTerminal(SQBO_TOKEN,arrID));
            free(getChildTerminal(SQBC_TOKEN,arrID));
            break;
        }
        case 62:{
            TREENODE arrID = parent;
            free(arrID->child);
            break;
        }
        case 63:{
            TREENODE signedParam = parent;
            break;
        }
        case 64:{
            TREENODE signedParam = parent;
            break;
        }
        case 65:{
            TREENODE param = parent;
            break;
        }
        case 66:{
            TREENODE paramList = parent;
            break;
        }
        case 67:{
            TREENODE leftFactored_paramList = parent;
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_paramList));
            break;
        }
        case 68:{
            TREENODE leftFactored_paramList = parent;
            free(leftFactored_paramList->child);
            break;
        }
        case 69:{
            TREENODE optional = parent;
            free(getChildTerminal(SQBO_TOKEN,optional));
            free(getChildTerminal(SQBC_TOKEN,optional));
            free(getChildTerminal(ASSIGNOP_OPERATOR,optional));
            break;
        }
        case 70:{
            TREENODE optional = parent;
            free(optional->child);
            break;
        }
        case 71:{
            TREENODE idList = parent;
            break;
        }
        case 72:{
            TREENODE leftFactored_idList = parent;
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_idList));
            free(getChildTerminal(IDENTIFIER_TOKEN,leftFactored_idList));
            break;
        }
        case 73:{
            TREENODE leftFactored_idList = parent;
            free(leftFactored_idList->child);
            break;
        }
        case 74:{
            TREENODE expression = parent;
            break;
        }
        case 75:{
            TREENODE expression = parent;
            break;
        }
        case 76:{
            TREENODE unaryTerm = parent;
            break;
        }
        case 77:{
            TREENODE arithmeticFactor = parent;
            free(getChildTerminal(BO_TOKEN,arithmeticFactor));
            free(getChildTerminal(BC_TOKEN,arithmeticFactor));
            break;
        }
        case 78:{
            TREENODE arithmeticFactor = parent;
            break;
        }
        case 79:{
            TREENODE arithmeticFactor = parent;
            break;
        }
        case 80:{
            TREENODE arithmeticFactor = parent;
            break;
        }
        case 81:{
            TREENODE arithmeticBooleanExpr = parent;
            break;
        }
        case 82:{
            TREENODE logicalTerm = parent;
            break;
        }
        case 83:{
            TREENODE logicalTerm = parent;
            free(logicalTerm->child);
            break;
        }
        case 84:{
            TREENODE anyTerm = parent;
            break;
        }
        case 85:{
            TREENODE relationalTerm = parent;
            break;
        }
        case 86:{
            TREENODE relationalTerm = parent;
            free(relationalTerm->child);
            break;
        }
        case 87:{
            TREENODE arithmeticExpr = parent;
            break;
        }
        case 88:{
            TREENODE leftFactored_arithmeticExpr = parent;
            break;
        }
        case 89:{
            TREENODE leftFactored_arithmeticExpr = parent;
            free(leftFactored_arithmeticExpr->child);
            break;
        }
        case 90:{
            TREENODE pm = parent;
            break;
        }
        case 91:{
            TREENODE pm = parent;
            break;
        }
        case 92:{
            TREENODE md = parent;
            break;
        }
        case 93:{
            TREENODE md = parent;
            break;
        }
        case 94:{
            TREENODE term = parent;
            break;
        }
        case 95:{
            TREENODE leftFactored_term = parent;
            break;;
        }
        case 96:{
            TREENODE leftFactored_term = parent;
            free(leftFactored_term->child);
            break;
        }
        case 97:{
            TREENODE factor = parent;
            free(getChildTerminal(BO_TOKEN,factor));
            free(getChildTerminal(BC_TOKEN,factor));
            break;
        }
        case 98:{
            TREENODE factor = parent;
            break;
        }
        case 99:{
            TREENODE arithmeticExprWArr = parent;
            break;
        }
        case 100:{
            TREENODE leftFactored_arithmeticExprWArr = parent;
            break;
        }
        case 101:{
            TREENODE leftFactored_arithmeticExprWArr = parent;
            free(leftFactored_arithmeticExprWArr->child);
            break;
        }
        case 102:{
            TREENODE termWArr = parent;
            break;
        }
        case 103:{
            TREENODE leftFactored_termWArr = parent;
            break;
        }
        case 104:{
            TREENODE leftFactored_termWArr = parent;
            free(leftFactored_termWArr->child);
            break;
        }
        case 105:{
            TREENODE signedFactorWArr = parent;
            break;
        }
        case 106:{
            TREENODE factorWArr = parent;
            free(getChildTerminal(BO_TOKEN,factorWArr));
            free(getChildTerminal(BC_TOKEN,factorWArr));
            break;
        }
        case 107:{
            TREENODE factorWArr = parent;
            break;
        }
        case 108:{
            TREENODE factorWArr = parent;
            break;
        }
        case 109:{
            TREENODE factorWArr = parent;
            break;
        }
        case 110:{
            TREENODE logicalOp = parent;
            break;
        }
        case 111:{
            TREENODE logicalOp = parent;
            break;
        }
        case 112:{
            TREENODE relationalOp = parent;
            break;
        }
        case 113:{
            TREENODE relationalOp = parent;
            break;
        }
        case 114:{
            TREENODE relationalOp = parent;
            break;
        }
        case 115:{
            TREENODE relationalOp = parent;
            break;
        }
        case 116:{
            TREENODE relationalOp = parent;
            break;
        }
        case 117:{
            TREENODE relationalOp = parent;
            break;
        }
        case 118:{
            TREENODE declareStmt = parent;
            free(getChildTerminal(DECLARE_KEYWORD,declareStmt));
            free(getChildTerminal(COLON_OPERATOR,declareStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,declareStmt));
            break;
        }
        case 119:{
            TREENODE conditionalStmt = parent;
            free(getChildTerminal(SWITCH_KEYWORD,conditionalStmt));
            free(getChildTerminal(BO_TOKEN,conditionalStmt));
            free(getChildTerminal(BC_TOKEN,conditionalStmt));
            free(getChildTerminal(START_KEYWORD,conditionalStmt));
            free(getChildTerminal(END_KEYWORD,conditionalStmt));
            break;
        }
        case 120:{
            TREENODE caseStmt = parent;
            free(getChildTerminal(CASE_KEYWORD,caseStmt));
            free(getChildTerminal(COLON_OPERATOR,caseStmt));
            free(getChildTerminal(BREAK_KEYWORD,caseStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,caseStmt));
            break;
        }
        case 121:{
            TREENODE leftFactored_caseStmt = parent;
            free(getChildTerminal(CASE_KEYWORD,leftFactored_caseStmt));
            free(getChildTerminal(COLON_OPERATOR,leftFactored_caseStmt));
            free(getChildTerminal(BREAK_KEYWORD,leftFactored_caseStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_caseStmt));
            break;
        }
        case 122:{
            TREENODE leftFactored_caseStmt = parent;
            free(leftFactored_caseStmt->child);
            break;
        }
        case 123:{
            TREENODE value = parent;
            break;
        }
        case 124:{
            TREENODE value = parent;
            break;
        }
        case 125:{
            TREENODE dfault = parent;
            free(getChildTerminal(DEFAULT_KEYWORD,dfault));
            free(getChildTerminal(COLON_OPERATOR,dfault));
            free(getChildTerminal(BREAK_KEYWORD,dfault));
            free(getChildTerminal(SEMICOL_OPERATOR,dfault));
            break;
        }
        case 126:{
            TREENODE dfault = parent;
            free(dfault->child);
            break;
        }
        case 127:{
            TREENODE iterativeStmt = parent;
            free(getChildTerminal(FOR_KEYWORD,iterativeStmt));
            free(getChildTerminal(BO_TOKEN,iterativeStmt));
            free(getChildTerminal(IDENTIFIER_TOKEN,iterativeStmt));
            free(getChildTerminal(IN_KEYWORD,iterativeStmt));
            free(getChildTerminal(RANGEOP_OPERATOR,iterativeStmt));
            free(getChildTerminal(BC_TOKEN,iterativeStmt));
            free(getChildTerminal(START_KEYWORD,iterativeStmt));
            free(getChildTerminal(END_KEYWORD,iterativeStmt));
            break;
        }
        case 128:{
            TREENODE iterativeStmt = parent;
            free(getChildTerminal(WHILE_KEYWORD,iterativeStmt));
            free(getChildTerminal(BO_TOKEN,iterativeStmt));
            free(getChildTerminal(BC_TOKEN,iterativeStmt));
            free(getChildTerminal(START_KEYWORD,iterativeStmt));
            free(getChildTerminal(END_KEYWORD,iterativeStmt));
            break;
        }
    }

}

