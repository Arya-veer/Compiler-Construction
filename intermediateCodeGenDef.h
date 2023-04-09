#ifndef ICG_DEFH
#define ICG_DEFH
#include "ast.h"

typedef enum{
    MODULE_DECLARATION,
    DRIVER_MODULE,
    MODULE_DEFINITION,
    FORMAL_INPUT_PARAMS,
    MUDULE_RETURN,
    MODULE_REUSE,
    DECLARE_VARIABLE,
} OPERATOR;

typedef struct Quadruple* QUADRUPLE; 

typedef struct QuadrupleRow* QUADRUPLEROW; 

struct QuadrupleRow{
    OPERATOR operator;
    TREENODE left;
    TREENODE op1;
    TREENODE op2;
    QUADRUPLEROW below;
};

struct Quadruple{
    QUADRUPLEROW top;
    QUADRUPLEROW curr;
};

#endif