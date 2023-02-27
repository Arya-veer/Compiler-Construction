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
short int follow_iterativeStmt = {}