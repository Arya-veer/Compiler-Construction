//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain


char* TOKENS_STRING[] = { "default" , "module" , "$" , "$" , "$" , "$" , ">>>" , "true" , "$" , "$" , "$" , "$" , "$" , "case" , "$" , "$" , "$" , "$" , "driver" , "$" , "$" , "$" , "$" , "$" , "$" , "array" , "OR" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "print" , "$" , "$" , "$" , "(" , ")" , "*" , "+" , "," , "-" , "$" , "/" , "$" , "while" , "$" , "program" , "$" , "$" , "$" , "$" , "AND" , "$" , ":" , ";" , "<" , "$" , ">" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "start" , "$" , "$" , "$" , "$" , "$" , "end" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "[" , "$" , "]" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "for" , "$" , "$" , "$" , "in" , "$" , "$" , "$" , "of" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "boolean" , "get_value" , "real" , "$" , "$" , "$" , "$" , "$" , "$" , "!=" , "switch" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , ".." , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "input" , "$" , "integer" , "$" , "$" , "$" , "$" , "$" , "$" , "use" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "takes" , "$" , "$" , "$" , "declare" , "$" , "$" , "$" , "false" , "$" , ":=" , "$" , "$" , "<<" , "<=" , "$" , "==" , "$" , ">=" , ">>" , "parameters" , "$" , "break" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "returns" , "$" , "$" , "$" , "$" , "<<<" , "$" , "$" , "$" , "with" , "$" , "$" , "$"};


char* TERMINALS_STRINGS[] = { "DEFAULT" , "MODULE" , "$" , "$" , "$" , "$" , "DRIVERENDDEF", "true" , "$" , "$" , "$" , "$" , "$" , "CASE" , "$" , "$" , "$" , "$" , "DRIVER" , "$" , "$" , "$" , "$" , "$" , "$" , "ARRAY" , "OR" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "PRINT" , "$" , "$" , "$" , "BO" , "BC" , "MUL" , "PLUS" , "COMMA" , "MINUS" , "$" , "DIV" , "$" , "WHILE" , "$" , "PROGRAM" , "$" , "$" , "$" , "$" , "AND" , "$" , "COLON" , "SEMICOL" , "LT" , "$" , "GT" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "START" , "$" , "$" , "$" , "$" , "$" , "END" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "SQBO" , "$" , "SQBC" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "FOR" , "$" , "$" , "$" , "IN" , "$" , "$" , "$" , "OF" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "BOOLEAN" , "GET_VALUE" , "REAL" , "$" , "$" , "$" , "$" , "$" , "$" , "NE" , "SWITCH" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "RANGEOP" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "INPUT" , "$" , "INTEGER" , "$" , "$" , "$" , "$" , "$" , "$" , "USE" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "TAKES" , "$" , "$" , "$" , "DECLARE" , "$" , "$" , "$" , "false" , "$" , "ASSIGNOP" , "$" , "$" , "DEF" , "LE" , "$" , "EQ" , "$" , "GE" , "ENDDEF" , "PARAMETERS" , "$" , "BREAK" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "$" , "RETURNS" , "$" , "$" , "$" , "$" , "DRIVERDEF" , "$" , "$" , "EOF" , "WITH" , "ID" , "NUM" , "RNUM"};


char* NONTERMINALS_STRINGS[] = {
    "finalProgram",
    "program",
    "moduleDeclarations",
    "moduleDeclaration",
    "otherModules",
    "driverModule",
    "module",
    "ret",
    "input_plist",
    "leftFactored_input_plist",
    "output_plist",
    "leftFactored_output_plist",
    "dataType",
    "arrRange",
    "leftFactored_arrRange",
    "sign",
    "type",
    "moduleDef",
    "statements",
    "statement",
    "ioStmt",
    "leftFactored_ioStmt",
    "boolValues",
    "var",
    "whichId",
    "leftFactored_whichId",
    "simpleStmt",
    "assignmentStmt",
    "whichStmt",
    "lvalueIDStmt",
    "lvalueARRStmt",
    "moduleReuseStmt",
    "optional",
    "idList",
    "leftFactored_idList",
    "expression",
    "unaryTerm",
    "arithmeticFactor",
    "arithmeticBooleanExpr",
    "logicalTerm",
    "relationalTerm",
    "arithmeticExpr",
    "leftFactored_arithmeticExpr",
    "pm",
    "md",
    "term",
    "leftFactored_term",
    "factor",
    "arithmeticExprWArr",
    "leftFactored_arithmeticExprWArr",
    "termWArr",
    "leftFactored_termWArr",
    "signedFactorWArr",
    "factorWArr",
    "logicalOp",
    "relationalOp",
    "declareStmt",
    "conditionalStmt",
    "caseStmt",
    "leftFactored_caseStmt",
    "value",
    "dfault",
    "iterativeStmt",
    "param",
    "arrID",
    "paramList",
    "leftFactored_paramList",
    "signedParam",
    "anyTerm",
    "idNum"
};