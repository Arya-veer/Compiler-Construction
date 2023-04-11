#ifndef ICG_H
#define ICG_H
#include "intermediateCodeGenDef.h"

QUADRUPLE QR;
QUADRUPLE initializeQuadruple();
void traversalForCodeGeneration(TREENODE node,SYMBOLTABLE SYMBOL_TABLE);
void printQuadRuple();
#endif