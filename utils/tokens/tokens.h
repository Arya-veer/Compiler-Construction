#ifndef UTILS_TOKENS_TOKENS_H
#define UTILS_TOKENS_TOKENS_H
  
    typedef enum  {
        INTEGER_TYPE,
        REAL_TYPE,
        BOOLEAN_TYPE,
        OF_KEYWORD,
        ARRAY_KEYWORD,
        START_KEYWORD,
        END_KEYWORD,
        DECLARE_KEYWORD,
        MODULE_KEYWORD,
        DRIVER_KEYWORD,
        PROGRAM_KEYWORD,
        GET_VALUE_KEYWORD,
        PRINT_FUNCTION,
        USE_KEYWORD,
        WITH_KEYWORD,
        PARAMETERS_KEYWORD,
        TAKES_KEYWORD,
        INPUT_KEYWORD,
        RETURNS_KEYWORD,
        FOR_KEYWORD,
        IN_KEYWORD,
        SWITCH_KEYWORD,
        CASE_KEYWORD,
        BREAK_KEYWORD,
        DEFAULT_KEYWORD,
        WHILE_KEYWORD,
        AND_OPERATOR,
        OR_OPERATOR,
        TRUE_BOOL,
        FALSE_BOOL,
        PLUS_OPERATOR,
        MINUS_OPERATOR,
        MUL_OPERATOR,
        DIV_OPERATOR,
        LT_OPERATOR,
        LE_OPERATOR,
        GE_OPERATOR,
        GT_OPERATOR,
        EQ_OPERATOR,
        NE_OPERATOR,
        DEF_OPERATOR,
        ENDDEF_OPERATOR,
        DRIVERDEF_OPERATOR,
        DRIVERENDDEF_OPERATOR,
        COLON_OPERATOR,
        RANGEOP_OPERATOR,
        SEMICOL_OPERATOR,
        COMMA_OPERATOR,
        ASSIGNOP_OPERATOR,
        SQBO_TOKEN,
        SQBC_TOKEN,
        BO_TOKEN,
        BC_TOKEN,
        EOF_TOKEN,
        IDENTIFIER_TOKEN,
        NUM_TOKEN,
        RNUM_TOKEN
    } TOKENS;

     char* TOKENS_STRING[54];

#endif 