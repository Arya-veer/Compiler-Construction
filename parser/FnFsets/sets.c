#include "../../utils/tokens/tokens.h"
    int rule1[] = {3,DECLARE_KEYWORD,DEF_OPERATOR,DRIVERDEF_OPERATOR}; 
    int rule2[] = {3,DECLARE_KEYWORD,DEF_OPERATOR,DRIVERDEF_OPERATOR}; 
    int rule3[] = {1,DECLARE_KEYWORD}; 
    int rule4[] = {2,DEF_OPERATOR,DRIVERDEF_OPERATOR}; 
    int rule5[] = {1,DECLARE_KEYWORD}; 
    int rule6[] = {1,DEF_OPERATOR}; 
    int rule7[] = {2,DRIVERDEF_OPERATOR,EOF_TOKEN}; 
    int rule8[] = {1,DRIVERDEF_OPERATOR}; 
    int rule9[] = {1,DEF_OPERATOR}; 
    int rule10[] = {1,RETURNS_KEYWORD}; 
    int rule11[] = {1,START_KEYWORD}; 
    int rule12[] = {1,IDENTIFIER_TOKEN}; 
    int rule13[] = {1,COMMA_OPERATOR}; 
    int rule14[] = {1,SQBC_TOKEN}; 
    int rule15[] = {1,IDENTIFIER_TOKEN}; 
    int rule16[] = {1,COMMA_OPERATOR}; 
    int rule17[] = {1,SQBC_TOKEN}; 
    int rule18[] = {1,INTEGER_TYPE}; 
    int rule19[] = {1,REAL_TYPE}; 
    int rule20[] = {1,BOOLEAN_TYPE}; 
    int rule21[] = {1,ARRAY_KEYWORD}; 
    int rule22[] = {4,PLUS_OPERATOR,MINUS_OPERATOR,IDENTIFIER_TOKEN,NUM_TOKEN}; 
    int rule23[] = {1,IDENTIFIER_TOKEN}; 
    int rule24[] = {1,NUM_TOKEN}; 
    int rule25[] = {2,PLUS_OPERATOR,MINUS_OPERATOR}; 
    int rule26[] = {4,IDENTIFIER_TOKEN,NUM_TOKEN,BO_TOKEN,RNUM_TOKEN}; 
    int rule27[] = {1,INTEGER_TYPE}; 
    int rule28[] = {1,REAL_TYPE}; 
    int rule29[] = {1,BOOLEAN_TYPE}; 
    int rule30[] = {1,START_KEYWORD}; 
    int rule31[] = {9,GET_VALUE_KEYWORD,PRINT_FUNCTION,IDENTIFIER_TOKEN,SQBO_TOKEN,USE_KEYWORD,DECLARE_KEYWORD,SWITCH_KEYWORD,FOR_KEYWORD,WHILE_KEYWORD}; 
    int rule32[] = {2,BREAK_KEYWORD,END_KEYWORD}; 
    int rule33[] = {2,GET_VALUE_KEYWORD,PRINT_FUNCTION}; 
    int rule34[] = {3,IDENTIFIER_TOKEN,SQBO_TOKEN,USE_KEYWORD}; 
    int rule35[] = {1,DECLARE_KEYWORD}; 
    int rule36[] = {1,SWITCH_KEYWORD}; 
    int rule37[] = {2,FOR_KEYWORD,WHILE_KEYWORD}; 
    int rule38[] = {1,GET_VALUE_KEYWORD}; 
    int rule39[] = {1,PRINT_FUNCTION}; 
    int rule40[] = {3,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule41[] = {2,TRUE_BOOL,FALSE_BOOL}; 
    int rule42[] = {1,TRUE_BOOL};  
    int rule43[] = {1,FALSE_BOOL}; 
    int rule44[] = {1,IDENTIFIER_TOKEN}; 
    int rule45[] = {1,NUM_TOKEN}; 
    int rule46[] = {1,RNUM_TOKEN}; 
    int rule47[] = {1,SQBO_TOKEN}; 
    int rule48[] = {14,BC_TOKEN,SEMICOL_OPERATOR,PLUS_OPERATOR,MINUS_OPERATOR,MUL_OPERATOR,DIV_OPERATOR,LT_OPERATOR,LE_OPERATOR,GT_OPERATOR,GE_OPERATOR,EQ_OPERATOR,NE_OPERATOR,AND_OPERATOR,OR_OPERATOR}; 
    int rule49[] = {1,IDENTIFIER_TOKEN}; 
    int rule50[] = {1,NUM_TOKEN}; 
    int rule51[] = {1,IDENTIFIER_TOKEN}; 
    int rule52[] = {2,SQBO_TOKEN,USE_KEYWORD}; 
    int rule53[] = {1,IDENTIFIER_TOKEN}; 
    int rule54[] = {1,ASSIGNOP_OPERATOR}; 
    int rule55[] = {1,SQBO_TOKEN}; 
    int rule56[] = {1,ASSIGNOP_OPERATOR}; 
    int rule57[] = {1,SQBO_TOKEN}; 
    int rule58[] = {2,SQBO_TOKEN,USE_KEYWORD}; 
    int rule59[] = {1,SQBO_TOKEN}; 
    int rule60[] = {3,SQBC_TOKEN,COLON_OPERATOR,SEMICOL_OPERATOR}; 
    int rule61[] = {1,IDENTIFIER_TOKEN}; 
    int rule62[] = {1,COMMA_OPERATOR}; 
    int rule63[] = {3,SEMICOL_OPERATOR,SQBC_TOKEN,COLON_OPERATOR}; 
    int rule64[] = {6,IDENTIFIER_TOKEN,BO_TOKEN,NUM_TOKEN,RNUM_TOKEN,TRUE_BOOL,FALSE_BOOL}; 
    int rule65[] = {2,PLUS_OPERATOR,MINUS_OPERATOR}; 
    int rule66[] = {2,PLUS_OPERATOR,MINUS_OPERATOR}; 
    int rule67[] = {4,BO_TOKEN}; 
    int rule68[] = {4,IDENTIFIER_TOKEN}; 
    int rule69[] = {4,NUM_TOKEN}; 
    int rule70[] = {4,RNUM_TOKEN}; 
    int rule71[] = {4,IDENTIFIER_TOKEN,BO_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule72[] = {2,TRUE_BOOL,FALSE_BOOL}; 
    int rule73[] = {2,AND_OPERATOR,OR_OPERATOR}; 
    int rule74[] = {2,SEMICOL_OPERATOR,BC_TOKEN}; 
    int rule75[] = {6,LT_OPERATOR,LE_OPERATOR,GT_OPERATOR,GE_OPERATOR,EQ_OPERATOR,NE_OPERATOR}; 
    int rule76[] = {4,AND_OPERATOR,OR_OPERATOR,SEMICOL_OPERATOR,BC_TOKEN}; 
    int rule77[] = {4,IDENTIFIER_TOKEN,BO_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule78[] = {2,PLUS_OPERATOR,MINUS_OPERATOR}; 
    int rule79[] = {10,BC_TOKEN,LT_OPERATOR,LE_OPERATOR,GE_OPERATOR,GT_OPERATOR,EQ_OPERATOR,NE_OPERATOR,AND_OPERATOR,OR_OPERATOR,SEMICOL_OPERATOR}; 
    int rule80[] = {1,PLUS_OPERATOR}; 
    int rule81[] = {1,MINUS_OPERATOR}; 
    int rule82[] = {1,MUL_OPERATOR}; 
    int rule83[] = {1,DIV_OPERATOR}; 
    int rule84[] = {4,IDENTIFIER_TOKEN,BO_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule85[] = {2,MUL_OPERATOR,DIV_OPERATOR}; 
    int rule86[] = {12,PLUS_OPERATOR,MINUS_OPERATOR,SEMICOL_OPERATOR,BC_TOKEN,LT_OPERATOR,LE_OPERATOR,GT_OPERATOR,GE_OPERATOR,EQ_OPERATOR,NE_OPERATOR,AND_OPERATOR,OR_OPERATOR}; 
    int rule87[] = {1,BO_TOKEN}; 
    int rule88[] = {3,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule89[] = {6,PLUS_OPERATOR,MINUS_OPERATOR,BO_TOKEN,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule90[] = {2,PLUS_OPERATOR,MINUS_OPERATOR}; 
    int rule91[] = {2,SQBC_TOKEN,BC_TOKEN}; 
    int rule92[] = {6,PLUS_OPERATOR,MINUS_OPERATOR,BO_TOKEN,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule93[] = {2,MUL_OPERATOR,DIV_OPERATOR}; 
    int rule94[] = {4,SQBC_TOKEN,PLUS_OPERATOR,MINUS_OPERATOR,BC_TOKEN}; 
    int rule95[] = {6,PLUS_OPERATOR,MINUS_OPERATOR,BO_TOKEN,IDENTIFIER_TOKEN,NUM_TOKEN,RNUM_TOKEN}; 
    int rule96[] = {1,BO_TOKEN}; 
    int rule97[] = {1,IDENTIFIER_TOKEN}; 
    int rule98[] = {1,NUM_TOKEN}; 
    int rule99[] = {1,RNUM_TOKEN}; 
    int rule100[] = {1,AND_OPERATOR}; 
    int rule101[] = {1,OR_OPERATOR}; 
    int rule102[] = {1,LT_OPERATOR}; 
    int rule103[] = {1,LE_OPERATOR}; 
    int rule104[] = {1,GT_OPERATOR}; 
    int rule105[] = {1,GE_OPERATOR}; 
    int rule106[] = {1,EQ_OPERATOR}; 
    int rule107[] = {1,NE_OPERATOR}; 
    int rule108[] = {1,DECLARE_KEYWORD}; 
    int rule109[] = {1,SWITCH_KEYWORD}; 
    int rule110[] = {1,CASE_KEYWORD}; 
    int rule111[] = {1,CASE_KEYWORD}; 
    int rule112[] = {2,DEFAULT_KEYWORD,END_KEYWORD}; 
    int rule113[] = {1,NUM_TOKEN}; 
    int rule114[] = {1,TRUE_BOOL}; 
    int rule115[] = {1,FALSE_BOOL}; 
    int rule116[] = {1,DEFAULT_KEYWORD}; 
    int rule117[] = {1,END_KEYWORD}; 
    int rule118[] = {1,FOR_KEYWORD}; 
    int rule119[] = {1,WHILE_KEYWORD};

int *firstFollowSet[] = {
    rule1,
    rule2,
    rule3,
    rule4,
    rule5,
    rule6,
    rule7,
    rule8,
    rule9,
    rule10,
    rule11,
    rule12,
    rule13,
    rule14,
    rule15,
    rule16,
    rule17,
    rule18,
    rule19,
    rule20,
    rule21,
    rule22,
    rule23,
    rule24,
    rule25,
    rule26,
    rule27,
    rule28,
    rule29,
    rule30,
    rule31,
    rule32,
    rule33,
    rule34,
    rule35,
    rule36,
    rule37,
    rule38,
    rule39,
    rule40,
    rule41,
    rule42,
    rule43,
    rule44,
    rule45,
    rule46,
    rule47,
    rule48,
    rule49,
    rule50,
    rule51,
    rule52,
    rule53,
    rule54,
    rule55,
    rule56,
    rule57,
    rule58,
    rule59,
    rule60,
    rule61,
    rule62,
    rule63,
    rule64,
    rule65,
    rule66,
    rule67,
    rule68,
    rule69,
    rule70,
    rule71,
    rule72,
    rule73,
    rule74,
    rule75,
    rule76,
    rule77,
    rule78,
    rule79,
    rule80,
    rule81,
    rule82,
    rule83,
    rule84,
    rule85,
    rule86,
    rule87,
    rule88,
    rule89,
    rule90,
    rule91,
    rule92,
    rule93,
    rule94,
    rule95,
    rule96,
    rule97,
    rule98,
    rule99,
    rule100,
    rule101,
    rule102,
    rule103,
    rule104,
    rule105,
    rule106,
    rule107,
    rule108,
    rule109,
    rule110,
    rule111,
    rule112,
    rule113,
    rule114,
    rule115,
    rule116,
    rule117,
    rule118,
    rule119
};