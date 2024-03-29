//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#ifndef ICG_DEFH
#define ICG_DEFH
#include "ast.h"

typedef enum{
    MODULE_DECLARATION,
    DRIVER_MODULE,
    MODULE_DEFINITION,
    FORMAL_INPUT_PARAMS,
    FORMAL_OUTPUT_PARAMS,
    MODULE_REUSE,
    MODULE_END,
    DECLARE_VARIABLE,
    GET_VALUE,
    PRINT_VALUE,
    PASS_PARAM,
    GET_RETURN,
    FOR_LOOP,
    FOR_LOOP_END,
    SWITCH_START,
    SWITCH_END,
    CASE_START,
    CASE_BREAK,
    DEFAULT_START,
    WHILE_START,
    WHILE_END,
    ASSIGN,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    UNARY_MINUS,
    ARRAY_ACCESS,
    ARRAY_ASSIGNMENT,
    DRIVER_MODULE_END,
    LESS_THAN,
    LESS_THAN_EQUAL,
    GREATER_THAN,
    GREATER_THAN_EQUAL,
    EQUAL,
    NOT_EQUAL,
    AND,
    OR
} OPERATOR;

typedef struct Quadruple* QUADRUPLE; 

typedef struct QuadrupleRow* QUADRUPLEROW; 

struct QuadrupleRow{
    OPERATOR operator;
    TREENODE left;
    TREENODE op1;
    TREENODE op2;
    QUADRUPLEROW below;
    SYMBOLTABLEROW currFunc;
    SYMBOLTABLE ST;
    int data;
};

struct Quadruple{
    QUADRUPLEROW top;
    QUADRUPLEROW curr;
};

#endif