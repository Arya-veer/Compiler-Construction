#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"
#include "parser.h"

TREENODE makeNode(char* nodeName,TREENODE left,TREENODE right){
    TREENODE tn = (TREENODE) malloc(sizeof(struct TreeNode));
    tn->isTerminal=2;
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

void applyRule(int ruleNum,TREENODE parent){

    switch(ruleNum){
        case 0: {
            TREENODE finalProgram = parent;
            TREENODE program = getChildNonTerminal(1,finalProgram); 
            applyRule(program->child->ruleNum,program);
            finalProgram->addr = program->addr;
            TREENODE eof = getChildTerminal(209,finalProgram);
            free(eof);
            break;
        }
        case 1:{

        }
        case 2:{
            TREENODE moduleDeclarations = parent;
            TREENODE moduleDeclaration = getChildNonTerminal(3,moduleDeclarations);
            TREENODE moduleDeclarations1 = getChildNonTerminal(2,moduleDeclarations);
            applyRule(moduleDeclaration->child->ruleNum,moduleDeclaration);
            applyRule(moduleDeclarations1->child->ruleNum,moduleDeclarations1);
            moduleDeclarations->list_addr_syn = insertAtBegin(moduleDeclaration->addr,moduleDeclarations1->list_addr_syn);
            moduleDeclarations->addr=moduleDeclarations->list_addr_syn;
            break;
        }
        case 3:{
            TREENODE moduleDeclarations = parent;
            moduleDeclarations->list_addr_syn = NULL;
            free(moduleDeclarations->child);
            break;
        }
        case 4:{
            TREENODE moduleDeclaration = parent;
            moduleDeclaration->addr = getChildTerminal(211,moduleDeclaration);
            free(getChildTerminal(DECLARE_KEYWORD,moduleDeclaration));
            free(getChildTerminal(SEMICOL_OPERATOR,moduleDeclaration));
            free(getChildTerminal(MODULE_KEYWORD,moduleDeclaration));
            break;
        }
        case 5:{
            TREENODE otherModules = parent;
            TREENODE module = getChildNonTerminal(6,otherModules);
            applyRule(module->child->ruleNum,module);
            TREENODE otherModules1 = getChildNonTerminal(4,otherModules); 
            applyRule(otherModules1->child->ruleNum,otherModules1);
            otherModules->list_addr_syn = insertAtBegin(module->addr,otherModules1->list_addr_syn);
            otherModules->addr = otherModules->list_addr_syn;
            break;
        }
        case 6:{
            TREENODE otherModules = parent;
            otherModules->list_addr_syn = NULL;
            free(otherModules->child);
            break;
        }
        case 7:{
            TREENODE driverModule = parent;
            TREENODE moduleDef = getChildNonTerminal(17,driverModule);
            applyRule(moduleDef->child->ruleNum,moduleDef);
            driverModule->addr = moduleDef->addr;
            free(getChildTerminal(DRIVERDEF_OPERATOR,driverModule));
            free(getChildTerminal(DRIVERENDDEF_OPERATOR,driverModule));
            free(getChildTerminal(PROGRAM_KEYWORD,driverModule));
            free(getChildTerminal(DRIVER_KEYWORD,driverModule));
            break;
        }
        case 8:{
            TREENODE module = parent;
            free(getChildTerminal(DEF_OPERATOR,module));
            free(getChildTerminal(MODULE_KEYWORD,module));
            free(getChildTerminal(IDENTIFIER_TOKEN,module));
            free(getChildTerminal(ENDDEF_OPERATOR,module));
            free(getChildTerminal(TAKES_KEYWORD,module));
            free(getChildTerminal(INPUT_KEYWORD,module));
            free(getChildTerminal(SQBO_TOKEN,module));
            free(getChildTerminal(SQBC_TOKEN,module));
            free(getChildTerminal(SEMICOL_OPERATOR,module));
            break;
        }
        case 9:{
            TREENODE ret = parent;
            free(getChildTerminal(RETURNS_KEYWORD,ret));
            free(getChildTerminal(SQBO_TOKEN,ret));
            free(getChildTerminal(SQBC_TOKEN,ret));
            free(getChildTerminal(SEMICOL_OPERATOR,ret));
            break;
        }
        case 10:{
            TREENODE ret = parent;
            free(ret->child);
            break;
        }
        case 11:{
            TREENODE input_plist = parent;
            free(getChildTerminal(IDENTIFIER_TOKEN,input_plist));
            free(getChildTerminal(COLON_OPERATOR,input_plist));
            break;
        }
        case 12:{
            TREENODE leftFactored_input_plist = parent;
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_input_plist));
            free(getChildTerminal(IDENTIFIER_TOKEN,leftFactored_input_plist));
            free(getChildTerminal(COLON_OPERATOR,leftFactored_input_plist));
            break;
        }
        case 13:{
            TREENODE leftFactored_input_plist = parent;
            free(leftFactored_input_plist->child);
            break;
        }
        case 14:{
            TREENODE output_plist = parent;
            free(getChildTerminal(IDENTIFIER_TOKEN,output_plist));
            free(getChildTerminal(COLON_OPERATOR,output_plist));
            break;
        }
        case 15:{
            TREENODE leftFactored_output_plist = parent;
            free(getChildTerminal(COMMA_OPERATOR,leftFactored_output_plist));
            free(getChildTerminal(IDENTIFIER_TOKEN,leftFactored_output_plist));
            free(getChildTerminal(COLON_OPERATOR,leftFactored_output_plist));
            break;
        }
        case 16:{
            TREENODE leftFactored_output_plist = parent;
            free(leftFactored_output_plist->child);
            break;
        }
        case 17:{
            TREENODE dataType = parent;
            break;
        }
        case 18:{
            TREENODE dataType = parent;
            break;
        }
        case 19:{
            TREENODE dataType = parent;
            break;
        }
        case 20:{
            TREENODE dataType = parent;
            free(getChildTerminal(ARRAY_KEYWORD,dataType));
            free(getChildTerminal(SQBO_TOKEN,dataType));
            free(getChildTerminal(SQBC_TOKEN,dataType));
            free(getChildTerminal(OF_KEYWORD,dataType));
            break;
        }
        case 21:{
            TREENODE arrRange = parent;
            break;
        }
        case 22:{
            TREENODE leftFactored_arrRange = parent;
            free(getChildTerminal(RANGEOP_OPERATOR,leftFactored_arrRange));
            break;
        }
        case 23:{
            TREENODE idNum = parent;
            free(getChildTerminal(IDENTIFIER_TOKEN,idNum));
            break;
        }
        case 24:{
            TREENODE idNum = parent;
            free(getChildTerminal(NUM_TOKEN,idNum));
            break;
        }
        case 25:{
            TREENODE sign = parent;
            break;
        }
        case 26:{
            TREENODE sign = parent;
            free(sign->child);
            break;
        }
        case 27:{
            TREENODE type = parent;
            break;
        }
        case 28:{
            TREENODE type = parent;
            break;
        }
        case 29:{
            TREENODE type = parent;
            break;
        }
        case 30:{
            TREENODE moduleDef = parent;
            free(getChildTerminal(START_KEYWORD,moduleDef));
            free(getChildTerminal(END_KEYWORD,moduleDef));
            break;
        }
        case 31:{
            TREENODE statements = parent;
            break;
        }
        case 32:{
            TREENODE statements = parent;
            free(statements->child);
            break;
        }
        case 33:{
            TREENODE statement = parent;
            break;
        }
        case 34:{
            TREENODE statement = parent;
            break;
        }
        case 35:{
            TREENODE statement = parent;
            break;
        }
        case 36:{
            TREENODE statement = parent;
            break;
        }
        case 37:{
            TREENODE statement = parent;
            break;
        }
        case 38:{
            TREENODE ioStmt = parent;
            free(getChildTerminal(GET_VALUE_KEYWORD,ioStmt));
            free(getChildTerminal(BO_TOKEN,ioStmt));
            free(getChildTerminal(BC_TOKEN,ioStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,ioStmt));
            break;
        }
        case 39:{
            TREENODE ioStmt = parent;
            free(getChildTerminal(PRINT_FUNCTION,ioStmt));
            free(getChildTerminal(BO_TOKEN,ioStmt));
            break;
        }
        case 40:{
            TREENODE leftFactored_ioStmt = parent;
            free(getChildTerminal(BC_TOKEN,leftFactored_ioStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_ioStmt));
            break;
        }
        case 41:{
            TREENODE leftFactored_ioStmt = parent;
            free(getChildTerminal(BC_TOKEN,leftFactored_ioStmt));
            free(getChildTerminal(SEMICOL_OPERATOR,leftFactored_ioStmt));
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

