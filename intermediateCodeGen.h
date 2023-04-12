#ifndef ICG_H
#define ICG_H
#include "intermediateCodeGenDef.h"

QUADRUPLE QR;
QUADRUPLE initializeQuadruple();
void printQuadRupleRow(QUADRUPLEROW qr);
void traversalForCodeGeneration(TREENODE node,SYMBOLTABLE SYMBOL_TABLE);
void printQuadRuple();
QUADRUPLEROW getRowFromQuadruple();
#endif