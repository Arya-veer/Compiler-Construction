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
            free()
        }
    }

}

