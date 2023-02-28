#include <sets.h>
short int follow_finalProgram[] = {1, EOF_TOKEN};
short int follow_program[] = {1, EOF_TOKEN};
short int follow_moduleDeclarations[] = {2, DEF_OPERATOR, DRIVERDEF_OPERATOR};
short int follow_moduleDeclaration[] = {3, DECLARE_KEYWORD, DEF_OPERATOR, DRIVERDEF_OPERATOR};
short int follow_otherModules[] = {2, DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_driverModule[] = {3, DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_module[] = {3, DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_ret[] = {1, START_KEYWORD};
short int follow_input_plist[] = {1, SQBC_TOKEN};
short int follow_leftFactored_input_plist[] = {1, SQBC_TOKEN};
short int follow_output_plist[] = {1, SQBC_TOKEN};
short int follow_leftFactored_output_plist[] = {1, SQBC_TOKEN};
short int follow_dataType[] = {2, COMMA_OPERATOR, SQBC_TOKEN};
short int follow_arrRange[] = {1, SQBC_TOKEN};
short int follow_leftFactored_arrRange[] = {1, SQBC_TOKEN};
short int follow_sign[] = {4, IDENTIFIER_TOKEN, NUM_TOKEN, BO_TOKEN, RNUM_TOKEN};
short int follow_type[] = {2, COMMA_OPERATOR, SQBC_TOKEN};
short int follow_moduleDef[] = {3, DEF_OPERATOR, DRIVERDEF_OPERATOR, EOF_TOKEN};
short int follow_statements[] = {2, END_KEYWORD, BREAK_KEYWORD};
short int follow_statement[] = {2, END_KEYWORD, BREAK_KEYWORD};
short int follow_ioStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_leftFactored_ioStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_boolValues[] = {4, SEMICOL_OPERATOR, BC_TOKEN, AND_OPERATOR, OR_OPERATOR};
short int follow_var[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_whichId[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_leftFactored_whichId[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_simpleStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_assignmentStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_whichStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_lvalueIDStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_lvalueARRStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_moduleReuseStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_optional[] = {4, SQBC_TOKEN, COLON_OPERATOR, SEMICOL_OPERATOR, USE_KEYWORD};
short int follow_idList[] = {3, SQBC_TOKEN, COLON_OPERATOR, SEMICOL_OPERATOR};
short int follow_leftFactored_idList[] = {3, SEMICOL_OPERATOR, SQBC_TOKEN, COLON_OPERATOR};
short int follow_expression[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_unaryTerm[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_arithmeticFactor[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_arithmeticBooleanExpr[] = {4, SEMICOL_OPERATOR, BC_TOKEN, AND_OPERATOR, OR_OPERATOR};
short int follow_logicalTerm[] = {2, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_relationalTerm[] = {4, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_arithmeticExpr[] = {4, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN};
short int follow_leftFactored_arithmeticExpr[] = {10, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GE_OPERATOR, GT_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR};
short int follow_pm[] = {6, PLUS_OPERATOR, MINUS_OPERATOR, NUM_TOKEN, IDENTIFIER_TOKEN, BO_TOKEN, RNUM_TOKEN};
short int follow_md[] = {5, PLUS_OPERATOR, MINUS_OPERATOR, BO_TOKEN, IDENTIFIER_TOKEN, NUM_TOKEN, RNUM_TOKEN};
short int follow_term[] = {12, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GE_OPERATOR, GT_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR, SEMICOL_OPERATOR};
short int follow_leftFactored_term[] = {2, MUL_OPERATOR, DIV_OPERATOR};
short int follow_factor[] = {14, MUL_OPERATOR, DIV_OPERATOR, PLUS_OPERATOR, MINUS_OPERATOR, SEMICOL_OPERATOR, BC_TOKEN, LT_OPERATOR, LE_OPERATOR, GT_OPERATOR, GE_OPERATOR, EQ_OPERATOR, NE_OPERATOR, AND_OPERATOR, OR_OPERATOR};
short int follow_arithmeticExprWArr[] = {2, BC_TOKEN, SQBC_TOKEN};
short int follow_leftFactored_arithmeticExprWArr[] = {2, SQBC_TOKEN, BC_TOKEN};
short int follow_termWArr[] = {4, PLUS_OPERATOR, MINUS_OPERATOR, SQBC_TOKEN, BC_TOKEN};
short int follow_leftFactored_termWArr[] = {4, SQBC_TOKEN, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN};
short int follow_signedFactorWArr[] = {6, MUL_OPERATOR, DIV_OPERATOR, SQBC_TOKEN, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN};
short int follow_factorWArr[] = {6, MUL_OPERATOR, DIV_OPERATOR, SQBC_TOKEN, PLUS_OPERATOR, MINUS_OPERATOR, BC_TOKEN};
short int follow_logicalOp[] = {6, IDENTIFIER_TOKEN, BO_TOKEN, NUM_TOKEN, RNUM_TOKEN, TRUE_BOOL, FALSE_BOOL};
short int follow_relationalOp[] = {4, IDENTIFIER_TOKEN, BO_TOKEN, NUM_TOKEN, RNUM_TOKEN};
short int follow_declareStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_conditionalStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};
short int follow_caseStmt[] = {2, DEFAULT_KEYWORD, END_KEYWORD};
short int follow_leftFactored_caseStmt[] = {2, DEFAULT_KEYWORD, END_KEYWORD};
short int follow_value[] = {1, COLON_OPERATOR};
short int follow_dfault[] = {1, END_KEYWORD};
short int follow_iterativeStmt[] = {11, GET_VALUE_KEYWORD, PRINT_FUNCTION, IDENTIFIER_TOKEN, SQBO_TOKEN, USE_KEYWORD, DECLARE_KEYWORD, SWITCH_KEYWORD, FOR_KEYWORD, WHILE_KEYWORD, BREAK_KEYWORD, END_KEYWORD};


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
    follow_iterativeStmt
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