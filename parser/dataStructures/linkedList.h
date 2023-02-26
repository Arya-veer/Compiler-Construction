#ifndef PARSER_DATASTRUCTURES_LINKEDLIST_H
#define PARSER_DATASTRUCTURES_LINKEDLIST_H

#include "../../lexer/lexer.h"

typedef enum  {
    finalProgram,
    program,
    moduleDeclarations,
    moduleDeclaration,
    otherModules,
    driverModule,
    module,
    ret,
    input_plist,
    leftFactored_input_plist,
    output_plist,
    leftFactored_output_plist,
    dataType,
    arrRange,
    leftFactored_arrRange,
    sign,
    type,
    moduleDef,
    statements,
    statement,
    ioStmt,
    leftFactored_ioStmt,
    boolValues,
    var,
    whichId,
    leftFactored_whichId,
    simpleStmt,
    assignmentStmt,
    whichStmt,
    lvalueIDStmt,
    lvalueARRStmt,
    moduleReuseStmt,
    optional,
    idList,
    leftFactored_idList,
    expression,
    unaryTerm,
    arithmeticFactor,
    arithmeticBooleanExpr,
    logicalTerm,
    relationalTerm,
    arithmeticExpr,
    leftFactored_arithmeticExpr,
    pm,
    md,
    term,
    leftFactored_term,
    factor,
    arithmeticExprWArr,
    leftFactored_arithmeticExprWArr,
    termWArr,
    leftFactored_termWArr,
    signedFactorWArr,
    factorWArr,
    logicalOp,
    relationalOp,
    declareStmt,
    conditionalStmt,
    caseStmt,
    leftFactored_caseStmt,
    value,
    dfault,
    iterativeStmt,

} NONTERMINALS;

char* NONTERMINALS_STRINGS[63];
union NodeType {
    TOKENS terminal;
    NONTERMINALS nonterminal;
};


typedef struct ListNode* LISTNODE;
struct ListNode {
    short ruleNum;
    LISTNODE next;
    union NodeType* NODETYPE;
    short isTerminal;
};

typedef struct LinkedList* LINKEDLIST;

struct LinkedList{
    short size;
    LISTNODE head;
};

LINKEDLIST createLinkedList();
void insertionInLinkedList(LINKEDLIST ll, short isTerminal, short ndtype, short ruleNum);

#endif
