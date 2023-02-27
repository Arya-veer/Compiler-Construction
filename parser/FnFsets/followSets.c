#include<sets.h>
short int follow_finalprogram = {1 ,EOF_TOKEN};
short int follow_program      = {1, EOF_TOKEN};
short int follow_moduleDeclarations = { 3, DECLARE_KEYWORD , DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_moduleDeclaration = { 3 ,DECLARE_KEYWORD,DEF_OPERATOR,DRIVERDEF_OPERATOR };
short int follow_othermodules = {1,DRIVERDEF_OPERATOR}; 
short int follow_drivermodule = {3 ,DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_module = {3 ,DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_return = {1,START_KEYWORD};
short int follow_input_plist = {1 , SQBC_TOKEN};
short int follow_leftFactored_input_plist = { 1, EOF_TOKEN};
short int follow_output_plist = {1, SQBC_TOKEN};
short int follow_leftFactored_output_plist = { 1, EOF_TOKEN};
short int follow_dataType = { 3 , SEMICOL_OPERATOR, COMMA_OPERATOR , SQBC_TOKEN};
short int follow_arrRange = { 1, SQBC_TOKEN};
short int follow_leftFactored_arrRange = {1, EOF_TOKEN};
short int follow_sign = {4 , IDENTIFIER_TOKEN, NUM_TOKEN , BO_TOKEN , RNUM_TOKEN };
short int follow_type = {3 , COMMA_OPERATOR , SQBC_TOKEN , EOF_TOKEN};
short int follow_moduleDef = { 1, EOF_TOKEN};
short int follow_statements = { 2, END_KEYWORD , BREAK_KEYWORD};
short int follow_statement = {11, GET_VALUE_KEYWORD,PRINT_FUNCTION,IDENTIFIER_TOKEN,SQBO_TOKEN,USE_KEYWORD,DECLARE_KEYWORD,SWITCH_KEYWORD,FOR_KEYWORD,WHILE_KEYWORD , BREAK_KEYWORD,END_KEYWORD };
short int follow_ioStmt = { 1, EOF_TOKEN};
short int follow_leftFactored_ioStmt = {1 , EOF_TOKEN};
short int follow_boolValues = {2 , BC_TOKEN, EOF_TOKEN};
short int follow_var = {2 , BC_TOKEN, EOF_TOKEN};
short int follow_whichId = {1 , EOF_TOKEN};
short int follow_leftFactored_whichId = {};
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_
short int follow_md={4,BO_TOKEN,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN,PLUS_OPERATOR,MINUS_OPERATOR,BO_TOKEN,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN};
short int follow_term={12,PLUS_OPERATOR,MINUS_OPERATOR,BC_TOKEN,LT_OPERATOR,LE_OPERATOR,GE_OPERATOR,GT_OPERATOR,EQ_OPERATOR,NE_OPERATOR,AND_OPERATOR,OR_OPERATOR,SEMICOL_OPERATOR};
short int follow_leftFactored_term={2,MUL_OPERATOR,DIV_OPERATOR}; 
short int follow_factor={14,MUL_OPERATOR,DIV_OPERATOR,PLUS_OPERATOR,MINUS_OPERATOR,SEMICOL_OPERATOR,BC_TOKEN,LT_OPERATOR,LE_OPERATOR,GT_OPERATOR,GE_OPERATOR,EQ_OPERATOR,NE_OPERATOR,AND_OPERATOR,OR_OPERATOR};
short int follow_arthimeticExprWArr={2,BC_TOKEN,SQBC_TOKEN};
short int follow_leftFactored_arthimeticExprWArr={2,SQBC_TOKEN,BC_TOKEN};
short int follow_termWArr={4,PLUS_OPERATOR,MINUS_OPERATOR,SQBC_TOKEN,BC_TOKEN};
short int follow_leftFactoredWArr={4,SQBC_TOKEN,PLUS_OPERATOR,MINUS_OPERATOR,BC_TOKEN}; 
short int follow_signedFactorWArr={6,MUL_OPERATOR,DIV_OPERATOR,SQBC_TOKEN,PLUS_OPERATOR,MINUS_OPERATOR,BC_TOKEN};
short int follow_factorWArr={6,MUL_OPERATOR,DIV_OPERATOR,SQBC_TOKEN,PLUS_OPERATOR,MINUS_OPERATOR,BC_TOKEN};
short int follow_logicalOp={6,IDENTIFIER_TOKEN,BO_TOKEN,NUM_TOKEN,RNUM_TOKEN,TRUE_BOOL,FALSE_BOOL};
short int follow_relationalOp={4,IDENTIFIER_TOKEN,BO_TOKEN,NUM_TOKEN,RNUM_TOKEN};
short int follow_declareStmt={11,GET_VALUE_KEYWORD,PRINT_FUNCTION,IDENTIFIER_TOKEN,SQBO_TOKEN,USE_KEYWORD,DECLARE_KEYWORD,SWITCH_KEYWORD,FOR_KEYWORD,WHILE_KEYWORD,BREAK_KEYWORD,END_KEYWORD};
short int follow_conditionalStmt={11,GET_VALUE_KEYWORD,PRINT_FUNCTION,IDENTIFIER_TOKEN,SQBO_TOKEN,USE_KEYWORD,DECLARE_KEYWORD,SWITCH_KEYWORD,FOR_KEYWORD,WHILE_KEYWORD,BREAK_KEYWORD,END_KEYWORD};
short int follow_caseStmt={2,DEFAULT_KEYWORD,END_KEYWORD};
short int follow_leftFactored_caseStmt={2,DEFAULT_KEYWORD,END_KEYWORD};
short int follow_value={1,COLON_OPERATOR};
short int follow_default={1,END_KEYWORD};
short int follow_iterativeStmt = {11,GET_VALUE_KEYWORD,PRINT_FUNCTION,IDENTIFIER_TOKEN,SQBO_TOKEN,USE_KEYWORD,DECLARE_KEYWORD,SWITCH_KEYWORD,FOR_KEYWORD,WHILE_KEYWORD,BREAK_KEYWORD,END_KEYWORD};