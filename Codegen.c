#include "symbolTable.h"
#include "parserDef.h"

f_plus(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "ADD EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
} 

f_sub(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "SUB EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
} 

f_mul(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MUL EBX\n");
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
} 

f_div(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "DIV EBX\n");
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
}  


f_and(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "AND EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
} 


f_OR(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "OR EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
} 

f_LT(A , B , C){
    fprintf(file , "MOV %s, %s,",R1,A);
    fprintf(file , "MOV %s, %s,",R2,B);
    fprintf(file , "MOV %s, %s,",R3,C,);
    fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
} 

f_GT(A , B , C){
    fprintf(file , "MOV %s, %s,",R1,A);
    fprintf(file , "MOV %s, %s,",R2,B);
    fprintf(file , "MOV %s, %s,",R3,C,);
    fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
} 

f_LE(A , B , C){
    fprintf(file , "MOV %s, %s,",R1,A);
    fprintf(file , "MOV %s, %s,",R2,B);
    fprintf(file , "MOV %s, %s,",R3,C,);
    fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
} 

f_GE(A , B , C){
    fprintf(file , "MOV %s, %s,",R1,A);
    fprintf(file , "MOV %s, %s,",R2,B);
    fprintf(file , "MOV %s, %s,",R3,C,);
    fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
} 

f_NE(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "XOR EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
}

f_EQ(A , B , C){
    // IF XOR RETURNS ZERO, STORE 1
    // IF XOR RETURNS NONZERO, STORE 0
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "XOR EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "XOR EAX, 255\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
} 

f_for_start(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    // A IS FOR START RANGE
    // ECX IS FOR TOTAL RANGE
    // 
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "MOV ECX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
    fprintf(file , "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
    fprintf(file , "MOV EDX, EAX\n");

    fprintf(file , "SUB ECX, EAX\n");    

    fprintf(file , "FOR_LABEL_%d:\n", for_index); /// HOW TO PRINT LABEL
    fprintf(file , "DEC ECX\n");
    fprintf(file , "ADD EDX, 1\n");
    fprintf(file , "MOV [origin + %d], EDX\n", GetVarFromSymbolTable(table, C)->offset);
    
}
    // THE STATEMENTS CAN NOW COME BELOW

f_for_end(){
    fprintf(file , "CMP ECX, 0\n");
    // next time f_for_start is called, for_index is automatically updated
    fprintf(file , "JNZ FOR_LABEL_%d", for_index++);
}

f_while_start(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    // A IS FOR START RANGE
    // ECX IS FOR TOTAL RANGE
    // 
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    fprintf(file , "CMP EAX, 0\n");

    // if eax is not zero, then dont jump
    // else jump
    fprintf(file , "JNZ WHILE_LABEL_END%d", while_index);
    fprintf(file , "WHILE_LABEL_%d:\n", while_index);   
}
    // THE STATEMENTS CAN NOW COME BELOW

f_while_end(){
    // next time f_for_start is called, for_index is automatically updated
    fprintf(file , "JUMP WHILE_LABEL_%d", while_index);
    fprintf(file , "WHILE_LABEL_END%d:\n", while_index++);     
}

f_declare(A , B , C){
    fprintf(file , "MOV %s, %s,",R1,A);
    fprintf(file , "MOV %s, %s,",R2,B);
    fprintf(file , "MOV %s, %s,",R3,C,);
    fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
} 

f_driverDef(A , B , C){
    fprintf(file , "MOV %s, %s,",R1,A);
    fprintf(file , "MOV %s, %s,",R2,B);
    fprintf(file , "MOV %s, %s,",R3,C,);
    fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
} 


// f_driverEndDef(A , B , C){
//     fprintf(file , "MOV %s, %s,",R1,A);
//     fprintf(file , "MOV %s, %s,",R2,B);
//     fprintf(file , "MOV %s, %s,",R3,C,);
//     fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
// } 

// f_elseif(A , B , C){
//     fprintf(file , "MOV %s, %s,",R1,A);
//     fprintf(file , "MOV %s, %s,",R2,B);
//     fprintf(file , "MOV %s, %s,",R3,C,);
//     fprintf(file , "ADD %s, %s %s,",R3,R2,R1);
// } 

f_switch_start(SYMBOLTABLE table, TREENODE A , TREENODE B , TREENODE C){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
    
}

f_case(A , B , C){
    
    fprintf(file , "CASE_LABEL_%d:\n", case_label);  
    // A is the value that the case is looking for
    fprintf(file , "CMP EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

    // next time this f_case is called, the case_label is incremented
    fprintf(file , "JNE CASE_LABEL_%d\n", ++case_label);  


    // CASE STMTS KA CODE

} 

f_case_break(){
    fprintf(file , "JUMP SWITCH_END_%s\n", switch_label);
}

f_default(){
    fprintf(file , "CASE_LABEL_%d:\n", case_label);  

    // CASE STMTS KA CODE

}

f_switch_end(){
    fprintf(file , "SWITCH_END_%d:\n", switch_label++);

}

f_function_start(){
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, returnVar)->offset);
    fprintf(file , "PUSH EAX \n");

    // only once
    // function_identifier must be added
    fprintf(file , "CALL %s \n", function_identifier);

}

f_function_end(){
    // loop over all the return variables
    fprintf(file , "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, returnVar)->offset);
    fprintf(file , "PUSH EAX \n");

    // only once
    fprintf(file , "RET \n");
}