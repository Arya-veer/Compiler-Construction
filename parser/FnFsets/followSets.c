#include "followSets.h"
short int follow_finalProgram[] = {2, EOF_TOKEN, SEMICOL_OPERATOR};
short int follow_program[] = {2, EOF_TOKEN, SEMICOL_OPERATOR};
short int follow_moduleDeclarations[] = {3, DEF_OPERATOR, DRIVERDEF_OPERATOR, SEMICOL_OPERATOR};
short int follow_moduleDeclaration[] = {4, DECLARE_KEYWORD, DEF_OPERATOR, DRIVERDEF_OPERATOR, SEMICOL_OPERATOR};
short int follow_otherModules[] = {3, DRIVERDEF_OPERATOR, EOF_TOKEN, SEMICOL_OPERATOR};
short int follow_driverModule[] = {4, DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN, SEMICOL_OPERATOR};
short int follow_module[] = {4, DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN, SEMICOL_OPERATOR};
short int follow_ret[] = {2, START_KEYWORD, SEMICOL_OPERATOR};
short int follow_input_plist[] = {2, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_leftFactored_input_plist[] = {2, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_output_plist[] = {2, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_leftFactored_output_plist[] = {2, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_dataType[] = {3, COMMA_OPERATOR, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_arrRange[] = {2, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_leftFactored_arrRange[] = {2, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_sign[] = {5, IDENTIFIER_TOKEN, NUM_TOKEN, BO_TOKEN, RNUM_TOKEN, SEMICOL_OPERATOR};
short int follow_type[] = {3, COMMA_OPERATOR, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_moduleDef[] = {4, DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN, SEMICOL_OPERATOR};
short int follow_statements[] = {3, END_KEYWORD, BREAK_KEYWORD, SEMICOL_OPERATOR};
short int follow_statement[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_ioStmt[] = {12, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD, SEMICOL_OPERATOR};
short int follow_leftFactored_ioStmt[] = {12, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD, SEMICOL_OPERATOR};
short int follow_boolValues[] = {4, SEMICOL_OPERATOR, BC_TOKEN, AND_OPERATOR, OR_OPERATOR};
short int follow_var[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_whichId[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_leftFactored_whichId[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_simpleStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_assignmentStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_whichStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_lvalueIDStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_lvalueARRStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_moduleReuseStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_optional[] = {2, USE_KEYWORD, SEMICOL_OPERATOR};
short int follow_idList[] = {3, SQBC_TOKEN, COLON_OPERATOR, SEMICOL_OPERATOR};
short int follow_leftFactored_idList[] = {3, SEMICOL_OPERATOR, SQBC_TOKEN, COLON_OPERATOR};
short int follow_expression[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_unaryTerm[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_arithmeticFactor[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_arithmeticBooleanExpr[] = {4, SEMICOL_OPERATOR, BC_TOKEN, AND_OPERATOR, OR_OPERATOR};
short int follow_logicalTerm[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_relationalTerm[] = {4, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_arithmeticExpr[] = {4, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_leftFactored_arithmeticExpr[] = {4, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_pm[] = {7, PLUS_OPERATOR, MINUS_OPERATOR, NUM_TOKEN, IDENTIFIER_TOKEN, BO_TOKEN, RNUM_TOKEN, SEMICOL_OPERATOR};
short int follow_md[] = {6, PLUS_OPERATOR, MINUS_OPERATOR, BO_TOKEN, IDENTIFIER_TOKEN, NUM_TOKEN, RNUM_TOKEN, SEMICOL_OPERATOR};
short int follow_term[] = {12, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GE_OPERATOR, GT_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR};
short int follow_leftFactored_term[] = {12, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GE_OPERATOR, GT_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR};
short int follow_factor[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_arithmeticExprWArr[] = {3, BC_TOKEN, SQBC_TOKEN, SEMICOL_OPERATOR};
short int follow_leftFactored_arithmeticExprWArr[] = {3, SQBC_TOKEN, BC_TOKEN, SEMICOL_OPERATOR};
short int follow_termWArr[] = {5, PLUS_OPERATOR, MINUS_OPERATOR, SQBC_TOKEN, BC_TOKEN, SEMICOL_OPERATOR};
short int follow_leftFactored_termWArr[] = {5, SQBC_TOKEN, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN, SEMICOL_OPERATOR};
short int follow_signedFactorWArr[] = {7, MUL_OPERATOR, DIV_OPERATOR, SQBC_TOKEN, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN, SEMICOL_OPERATOR};
short int follow_factorWArr[] = {7, MUL_OPERATOR, DIV_OPERATOR, SQBC_TOKEN, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN, SEMICOL_OPERATOR};
short int follow_logicalOp[] = {7, IDENTIFIER_TOKEN, BO_TOKEN, NUM_TOKEN, RNUM_TOKEN, TRUE_BOOL, FALSE_BOOL, SEMICOL_OPERATOR};
short int follow_relationalOp[] = {5, IDENTIFIER_TOKEN, BO_TOKEN, NUM_TOKEN, RNUM_TOKEN, SEMICOL_OPERATOR};
short int follow_declareStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_conditionalStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_caseStmt[] = {3, DEFAULT_KEYWORD, END_KEYWORD, SEMICOL_OPERATOR};
short int follow_leftFactored_caseStmt[] = {3, DEFAULT_KEYWORD, END_KEYWORD, SEMICOL_OPERATOR};
short int follow_value[] = {2, COLON_OPERATOR, SEMICOL_OPERATOR};
short int follow_dfault[] = {2, END_KEYWORD, SEMICOL_OPERATOR};
short int follow_iterativeStmt[] = {12, END_KEYWORD, BREAK_KEYWORD, GET_VALUE_KEYWORD,PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN,USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD,FOR_KEYWORD, WHILE_KEYWORD, SEMICOL_OPERATOR};
short int follow_param[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_arrID[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_paramList[] = {1,SEMICOL_OPERATOR};
short int follow_leftFactored_paramList[] = {1,SEMICOL_OPERATOR};
short int follow_signedParam[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_anyTerm[] = {4,SEMICOL_OPERATOR, AND_OPERATOR, OR_OPERATOR, BC_TOKEN};
short int follow_idNum[] = {3,SEMICOL_OPERATOR, RANGEOP_OPERATOR, SQBC_TOKEN};


short int *followSets[] = {
    follow_finalProgram,
    follow_program,
    follow_moduleDeclarations,
    follow_moduleDeclaration,
    follow_otherModules,
    follow_driverModule,
    follow_module,
    follow_ret,
    follow_input_plist,
    follow_leftFactored_input_plist,
    follow_output_plist,
    follow_leftFactored_output_plist,
    follow_dataType,
    follow_arrRange,
    follow_leftFactored_arrRange,
    follow_sign,
    follow_type,
    follow_moduleDef,
    follow_statements,
    follow_statement,
    follow_ioStmt,
    follow_leftFactored_ioStmt,
    follow_boolValues,
    follow_var,
    follow_whichId,
    follow_leftFactored_whichId,
    follow_simpleStmt,
    follow_assignmentStmt,
    follow_whichStmt,
    follow_lvalueIDStmt,
    follow_lvalueARRStmt,
    follow_moduleReuseStmt,
    follow_optional,
    follow_idList,
    follow_leftFactored_idList,
    follow_expression,
    follow_unaryTerm,
    follow_arithmeticFactor,
    follow_arithmeticBooleanExpr,
    follow_logicalTerm,
    follow_relationalTerm,
    follow_arithmeticExpr,
    follow_leftFactored_arithmeticExpr,
    follow_pm,
    follow_md,
    follow_term,
    follow_leftFactored_term,
    follow_factor,
    follow_arithmeticExprWArr,
    follow_leftFactored_arithmeticExprWArr,
    follow_termWArr,
    follow_leftFactored_termWArr,
    follow_signedFactorWArr,
    follow_factorWArr,
    follow_logicalOp,
    follow_relationalOp,
    follow_declareStmt,
    follow_conditionalStmt,
    follow_caseStmt,
    follow_leftFactored_caseStmt,
    follow_value,
    follow_dfault,
    follow_iterativeStmt,
    follow_param,
    follow_arrID,
    follow_paramList,
    follow_leftFactored_paramList,
    follow_signedParam,
    follow_anyTerm,
    follow_idNum

};

int inFollowSets(int terminal,int nonterminal){
    int n = followSets[nonterminal][0];
    for(int j = 1;j<=n;j++){
        if(terminal == followSets[nonterminal][j]){
            return 1;
        }
    }
    return 0;
}