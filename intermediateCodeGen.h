//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

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