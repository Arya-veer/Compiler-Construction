#include "symbolTable.h"
#include "parserDef.h"

// // f_plus(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     fprintf(file, "ADD EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
// //     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// // }

// // f_sub(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     fprintf(file, "SUB EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
// //     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// // }

// // f_mul(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     fprintf(file, "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
// //     fprintf(file, "MUL EBX\n");
// //     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// // }

// // f_div(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     fprintf(file, "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
// //     fprintf(file, "DIV EBX\n");
// //     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// // }

// f_and(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "AND EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// f_OR(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "OR EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// f_LT(A, B, C)
// {
//     fprintf(file, "MOV %s, %s,", R1, A);
//     fprintf(file, "MOV %s, %s,", R2, B);
//     fprintf(file, "MOV %s, %s,", R3, C, );
//     fprintf(file, "ADD %s, %s %s,", R3, R2, R1);
// }

// f_GT(A, B, C)
// {
//     fprintf(file, "MOV %s, %s,", R1, A);
//     fprintf(file, "MOV %s, %s,", R2, B);
//     fprintf(file, "MOV %s, %s,", R3, C, );
//     fprintf(file, "ADD %s, %s %s,", R3, R2, R1);
// }

// f_LE(A, B, C)
// {
//     fprintf(file, "MOV %s, %s,", R1, A);
//     fprintf(file, "MOV %s, %s,", R2, B);
//     fprintf(file, "MOV %s, %s,", R3, C, );
//     fprintf(file, "ADD %s, %s %s,", R3, R2, R1);
// }

// f_GE(A, B, C)
// {
//     fprintf(file, "MOV %s, %s,", R1, A);
//     fprintf(file, "MOV %s, %s,", R2, B);
//     fprintf(file, "MOV %s, %s,", R3, C, );
//     fprintf(file, "ADD %s, %s %s,", R3, R2, R1);
// }

// f_NE(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "XOR EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// f_EQ(A, B, C)
// {
//     // IF XOR RETURNS ZERO, STORE 1
//     // IF XOR RETURNS NONZERO, STORE 0
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "XOR EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "XOR EAX, 255\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// // f_for_start(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     // A IS FOR START RANGE
//     // ECX IS FOR TOTAL RANGE
//     //
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "MOV ECX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
//     fprintf(file, "MOV EDX, EAX\n");

//     fprintf(file, "SUB ECX, EAX\n");

//     fprintf(file, "FOR_LABEL_%d:\n", for_index); /// HOW TO PRINT LABEL
//     fprintf(file, "DEC ECX\n");
//     fprintf(file, "ADD EDX, 1\n");
//     fprintf(file, "MOV [origin + %d], EDX\n", GetVarFromSymbolTable(table, C)->offset);
// }
// // THE STATEMENTS CAN NOW COME BELOW

// // f_for_end()
// // {
// //     fprintf(file, "CMP ECX, 0\n");
// //     // next time f_for_start is called, for_index is automatically updated
// //     fprintf(file, "JNZ FOR_LABEL_%d", for_index++);
// // }

// // f_while_start(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     // A IS FOR START RANGE
//     // ECX IS FOR TOTAL RANGE
//     //
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "CMP EAX, 0\n");

//     // if eax is not zero, then dont jump
//     // else jump
//     fprintf(file, "JNZ WHILE_LABEL_END%d", while_index);
//     fprintf(file, "WHILE_LABEL_%d:\n", while_index);
// }
// // THE STATEMENTS CAN NOW COME BELOW

// // f_while_end()
// // {
// //     // next time f_for_start is called, for_index is automatically updated
// //     fprintf(file, "JUMP WHILE_LABEL_%d", while_index);
// //     fprintf(file, "WHILE_LABEL_END%d:\n", while_index++);
// // }

// // f_switch_start(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// // }

// // f_case(A, B, C)
// {

//     fprintf(file, "CASE_LABEL_%d:\n", case_label);
//     // A is the value that the case is looking for
//     fprintf(file, "CMP EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

//     // next time this f_case is called, the case_label is incremented
//     fprintf(file, "JNE CASE_LABEL_%d\n", ++case_label);

//     // CASE STMTS KA CODE
// }

// // f_case_break()
// // {
// //     fprintf(file, "JUMP SWITCH_END_%s\n", switch_label);
// // }

// // f_default()
// // {
// //     fprintf(file, "CASE_LABEL_%d:\n", case_label);
// // CASE STMTS KA CODE
// // }

// // f_switch_end()
// // {
// //     fprintf(file, "SWITCH_END_%d:\n", switch_label++);
// // }

// // f_function_start()
// // {
// //     fprintf(file, "%s : ", GetVarFromSymbolTable(table, A)->offset)
// //         fprintf(file, "PUSH rbp\n");
// //     fprintf(file, "MOV rbp,rsp\n");
// // }

// // f_param_list_in_func(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     if (size == 4)
// //     {
// //         fprintf(file, "POP EAX\n");
// //         fprintf(file, "MOV [origin + %d],EAX\n", GetVarFromSymbolTable(table, A)->offset);
// //     }
// //     if (size == 2)
// //     {
// //         fprintf(file, "POP AX\n");
// //         fprintf(file, "MOV [origin + %d],AX\n", GetVarFromSymbolTable(table, A)->offset);
// //     }
// //     if (size == 1)
// //     {
// //         fprintf(file, "POP AL\n");
// //         fprintf(file, "MOV [origin + %d],AL\n", GetVarFromSymbolTable(table, A)->offset);
// //     }
// // }

// // f_actualparam_list(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     // fprintf(file , "MOV EAX , [origin + %d] \n",  GetVarFromSymbolTable(table, A)->offset);
// //     if (size == 4)
// //     {
// //         fprintf(file, "PUSH DWORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     }
// //     if (size == 2)
// //     {
// //         fprintf(file, "PUSH WORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     }
// //     if (size == 1)
// //     {
// //         fprintf(file, "PUSH BYTE [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// //     }
// // }

// // f_output_param(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     if (size == 4)
//         fprintf(file, "PUSH DWORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

//     if (size == 2)
//         fprintf(file, "PUSH WORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

//     if (size == 1)
//         fprintf(file, "PUSH BYTE [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// }

// // f_funtion_end(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MOV rsp, rbp\n");
// //     fprintf(file, "POP rbp\n");
// //     fprintf(file, "ret\n");
// // }

// // f_function_call(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "CALL %s\n", GetVarFromSymbolTable(table, A)->offset);
// // }

// // f_print(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "mov ebx, 1\n");
// //     fprintf(file, "mov ecx, %s\n", GetVarFromSymbolTable(table, A)->offset);
// //     fprintf(file, "mov edx, %d\n", GetVarFromSymbolTable(table, width)->offset);
// //     fprintf(file, "mov eax, 4\n");
// //     fprintf(file, "int 0x80");
// // }

// f_print_array(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "Label%d , mov ecx , %d", case_label, GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, " DEC ECX ");
//     f_print(table, A, B, C);
//     fprintf(file, "CMP ECX, 0");
//     fprintf(file, "JNZ Label%d", GetVarFromSymbolTable(table, A)->offset);
// }

// // f_takeinput(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "mov ebx, 0\n");
// //     fprintf(file, "mov ecx, %s\n", GetVarFromSymbolTable(table, A)->offset);
// //     fprintf(file, "mov edx, %d\n", GetVarFromSymbolTable(table, width)->offset);
// //     fprintf(file, "mov eax, 3\n");
// //     fprintf(file, "int 0x80");
// // }

// // f_moduleDeclare(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "extern %s", GetVarFromSymbolTable(table, name)->offset);
// // }

// // f_driverModule(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// // {
// //     fprintf(file, "MAIN : ");
// // }

// f_drivermoduleEnd()
// {
//     fprinf(file, "END");
// }

while (1)
{

    swtich

        Case 0: // MODULE_DECLARATION,
    {
        fprintf(file, "extern %s", GetVarFromSymbolTable(table, name)->offset);
        break;
    }

    Case 1: // DRIVER_MODULE,
    {
        fprintf(file, "MAIN : ");
        break;
    }

    Case 2: // MODULE_DEFINITION,
    {
        fprintf(file, "%s : ", GetVarFromSymbolTable(table, A)->offset)
        fprintf(file, "PUSH rbp\n");
        fprintf(file, "MOV rbp,rsp\n");
        break;
    }

    Case 3: // FORMAL_INPUT_PARAMS,
    {
        if (size == 4)
        {
            fprintf(file, "POP EAX\n");
            fprintf(file, "MOV [origin + %d],EAX\n", GetVarFromSymbolTable(table, A)->offset);
        }
        if (size == 2)
        {
            fprintf(file, "POP AX\n");
            fprintf(file, "MOV [origin + %d],AX\n", GetVarFromSymbolTable(table, A)->offset);
        }
        if (size == 1)
        {
            fprintf(file, "POP AL\n");
            fprintf(file, "MOV [origin + %d],AL\n", GetVarFromSymbolTable(table, A)->offset);
        }
        break;
    }

    Case 4: // FORMAL_OUTPUT_PARAMS,
    {
        if (size == 4)
            fprintf(file, "PUSH DWORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

        if (size == 2)
            fprintf(file, "PUSH WORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

        if (size == 1)
            fprintf(file, "PUSH BYTE [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        break;
    }

    Case 5: // MODULE_REUSE,
    {
        fprintf(file, "CALL %s\n", GetVarFromSymbolTable(table, A)->offset);
        break;
    }

    Case 6: // MODULE_END,
    {
        fprintf(file, "MOV rsp, rbp\n");
        fprintf(file, "POP rbp\n");
        fprintf(file, "ret\n");
        break;
    }

    Case 7:
    { // declare variable
        break;
    }

    Case 8:
    { // get value
        fprintf(file, "mov ebx, 0\n");
        fprintf(file, "mov ecx, %s\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "mov edx, %d\n", GetVarFromSymbolTable(table, width)->offset);
        fprintf(file, "mov eax, 3\n");
        fprintf(file, "int 0x80");
        break;
    }

    Case 9:
    { // print_value

        fprintf(file, "mov ebx, 1\n");
        fprintf(file, "mov ecx, %s\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "mov edx, %d\n", GetVarFromSymbolTable(table, width)->offset);
        fprintf(file, "mov eax, 4\n");
        fprintf(file, "int 0x80");
        break;
    }

    Case 10: // pass_param
    {
        if (size == 4)
        {
            fprintf(file, "PUSH DWORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        }
        if (size == 2)
        {
            fprintf(file, "PUSH WORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        }
        if (size == 1)
        {
            fprintf(file, "PUSH BYTE [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        }
        break;
    }

    Case 11:
    { // get_return
        break;
    }

    Case 12: // for_start
    {
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "MOV ECX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
        fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
        fprintf(file, "MOV EDX, EAX\n");

        fprintf(file, "SUB ECX, EAX\n");

        fprintf(file, "FOR_LABEL_%d:\n", for_index); /// HOW TO PRINT LABEL
        fprintf(file, "DEC ECX\n");
        fprintf(file, "ADD EDX, 1\n");
        fprintf(file, "MOV [origin + %d], EDX\n", GetVarFromSymbolTable(table, C)->offset);
        break;
    }

    Case 13: // for_end
    {
        fprintf(file, "CMP ECX, 0\n");
        fprintf(file, "JNZ FOR_LABEL_%d", for_index++);
        break;
    }

    Case 14: // swtich_start
    {
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        break;
    }

    Case 15: // switch_end
    {
        fprintf(file, "SWITCH_END_%d:\n", switch_label++);
        break;
    }

    Case 16: // case_start
    {
        fprintf(file, "CASE_LABEL_%d:\n", case_label);
        fprintf(file, "CMP EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "JNE CASE_LABEL_%d\n", ++case_label);
        break;
    }

    Case 17: // case_break
    {
        fprintf(file, "JUMP SWITCH_END_%s\n", switch_label);
        break;
    }

    Case 18:
    { // default_start
        fprintf(file, "CASE_LABEL_%d:\n", case_label);
        break;
    }

    Case 19:
    { // while_start
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "CMP EAX, 0\n");
        fprintf(file, "JNZ WHILE_LABEL_END%d", while_index);
        fprintf(file, "WHILE_LABEL_%d:\n", while_index);
        break;
    }

    Case 20:
    { // while_end
        fprintf(file, "JUMP WHILE_LABEL_%d", while_index);
        fprintf(file, "WHILE_LABEL_END%d:\n", while_index++);
        break;
    }

    Case 21:
    { // assign
    }

    Case 22:
    { // addition
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "ADD EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
        fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
        break;
    }

    Case 23:
    { // subtraction
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "SUB EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
        fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
        break;
    }

    Case 24:
    { // multiply
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
        fprintf(file, "MUL EBX\n");
        fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
        break;
    }

    Case 25:
    { // division
        fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        fprintf(file, "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
        fprintf(file, "DIV EBX\n");
        fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
        break;
    }

    Case 26:
    {
        break;
    }
    Case 27:
    {
        break;
    }
    Case 28:
    {
        break;
    }
    Case 29:
    {
        break;
    }
    Case 30:
    {
        break;
    }
}