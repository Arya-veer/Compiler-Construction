#ifndef UTILS_NONTERMINALS_NONTERMINALS_H
#define UTILS_NONTERMINALS_NONTERMINALS_H
  
    typedef enum  {
        finalProgram,
        program,
        moduleDeclarations,
        otherModules,
        driverModule,
        module,
        ret,
        input_plist,
        leftFactored_input_plist,
        output_plist,
        leftFactored_output_plist,
        dataType,
        arrRange,
        leftFactored_arrRange,
        sign,
        type,
        moduleDef,
        statements,
        statement,
        ioStmt,
        leftFactored_ioStmt,
        boolValues,
        var,
        whichId,
        leftFactored_whichId,
        simpleStmt,
        assignmentStmt,
        whichStmt,
        lvalueIDStmt,
        lvalueARRStmt,
        moduleReuseStmt,
        optional,
        idList,
        leftFactored_idList,
        expression,
        unaryTerm,
        arithmeticFactor,
        arithmeticBooleanExpr,
        logicalTerm,
        relationalTerm,
        arithmeticExpr,
        leftFactored_arithmeticExpr,
        pm,
        md,
        term,
        leftFactored_term,
        factor,
        arithmeticExprWArr,
        leftFactored_arithmeticExprWArr,
        termWArr,
        leftFactored_termWArr,
        signedFactorWArr,
        factorWArr,
        logicalOp,
        relationalOp,
        declareStmt,
        conditionalStmt,
        caseStmt,
        leftFactored_caseStmt,
        value,
        dfault,
        iterativeStmt

    } NONTERMINALS;

     char* NONTERMINALS_STRING[54];

#endif 