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
            break;
        }
        case 31:{
            
        }
        case 32:{
            
        }
        case 33:{
            
        }
        case 34:{
            
        }
        case 35:{
            
        }
        case 36:{
            
        }
        case 37:{
            
        }
        case 38:{
            
        }
        case 39:{
            
        }
        case 40:{
            
        }
        case 41:{
            
        }
        case 42:{
            
        }
        case 43:{
            
        }
        case 44:{
            
        }
        case 45:{
            
        }
        case 46:{
            
        }
        case 47:{
            
        }
        case 48:{
            
        }
        case 49:{
            
        }
        case 50:{
            
        }
        case 51:{
            
        }
        case 52:{
            
        }
        case 53:{
            
        }
        case 54:{
            
        }
        case 55:{
            
        }
        case 56:{
            
        }
        case 57:{
            
        }
        case 58:{
            
        }
        case 59:{
            
        }
        case 60:{
            
        }
        case 61:{
            
        }
        case 62:{
            
        }
        case 63:{
            
        }
        case 64:{
            
        }
        case 65:{
            
        }
        case 66:{
            
        }
        case 67:{
            
        }
        case 68:{
            
        }
        case 69:{
            
        }
        case 70:{
            
        }
        case 71:{
            
        }
        case 72:{
            
        }
        case 73:{
            
        }
        case 74:{
            
        }
        case 75:{
            
        }
        case 76:{
            
        }
        case 77:{
            
        }
        case 78:{
            
        }
        case 79:{
            
        }
        case 80:{
            
        }
        case 81:{
            
        }
        case 82:{
            
        }
        case 83:{
            
        }
        case 84:{
            
        }
        case 85:{
            
        }
        case 86:{
            
        }
        case 87:{
            
        }
        case 88:{
            
        }
        case 89:{
            
        }
        case 90:{
            
        }
        case 91:{
            
        }
        case 92:{
            
        }
        case 93:{
            
        }
        case 94:{
            
        }
        case 95:{
            
        }
        case 96:{
            
        }
        case 97:{
            
        }
        case 98:{
            
        }
        case 99:{
            
        }
        case 100:{
            
        }
        case 101:{
            
        }
        case 102:{
            
        }
        case 103:{
            
        }
        case 104:{
            
        }
        case 105:{
            
        }
        case 106:{
            
        }
        case 107:{
            
        }
        case 108:{
            
        }
        case 109:{
            
        }
        case 110:{
            
        }
        case 111:{
            
        }
        case 112:{
            
        }
        case 113:{
            
        }
        case 114:{
            
        }
        case 115:{
            
        }
        case 116:{
            
        }
        case 117:{
            
        }
        case 118:{
            
        }
        case 119:{
            
        }
        case 120:{
            
        }
        case 121:{
            
        }
        case 122:{
            
        }
        case 123:{
            
        }
        case 124:{
            
        }
        case 125:{
            
        }
        case 126:{
            
        }
        case 127:{
            
        }
        case 128:{
            
        }
        case 129:{
            
        }
    }

}

