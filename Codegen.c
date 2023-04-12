#include <stdio.h>
#include <stdlib.h>

#include "Codegen.h"

// f_plus(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "ADD EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// f_sub(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "SUB EAX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// f_mul(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "MUL EBX\n");
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

// f_div(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "MOV EBX, [origin + %d]\n", GetVarFromSymbolTable(table, B)->offset);
//     fprintf(file, "DIV EBX\n");
//     fprintf(file, "MOV [origin + %d], EAX\n", GetVarFromSymbolTable(table, C)->offset);
// }

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

// f_for_start(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
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

// f_for_end()
// {
//     fprintf(file, "CMP ECX, 0\n");
//     // next time f_for_start is called, for_index is automatically updated
//     fprintf(file, "JNZ FOR_LABEL_%d", for_index++);
// }

// f_while_start(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
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

// f_while_end()
// {
//     // next time f_for_start is called, for_index is automatically updated
//     fprintf(file, "JUMP WHILE_LABEL_%d", while_index);
//     fprintf(file, "WHILE_LABEL_END%d:\n", while_index++);
// }

// f_switch_start(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// }

// f_case(A, B, C)
// {

//     fprintf(file, "CASE_LABEL_%d:\n", case_label);
//     // A is the value that the case is looking for
//     fprintf(file, "CMP EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

//     // next time this f_case is called, the case_label is incremented
//     fprintf(file, "JNE CASE_LABEL_%d\n", ++case_label);

//     // CASE STMTS KA CODE
// }

// f_case_break()
// {
//     fprintf(file, "JUMP SWITCH_END_%s\n", switch_label);
// }

// f_default()
// {
//     fprintf(file, "CASE_LABEL_%d:\n", case_label);
// CASE STMTS KA CODE
// }

// f_switch_end()
// {
//     fprintf(file, "SWITCH_END_%d:\n", switch_label++);
// }

// // f_function_start()
// // {
// //     fprintf(file, "%s : ", GetVarFromSymbolTable(table, A)->offset)
// //         fprintf(file, "PUSH rbp\n");
// //     fprintf(file, "MOV rbp,rsp\n");
// // }

// f_param_list_in_func(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     if (size == 4)
//     {
//         fprintf(file, "POP EAX\n");
//         fprintf(file, "MOV [origin + %d],EAX\n", GetVarFromSymbolTable(table, A)->offset);
//     }
//     if (size == 2)
//     {
//         fprintf(file, "POP AX\n");
//         fprintf(file, "MOV [origin + %d],AX\n", GetVarFromSymbolTable(table, A)->offset);
//     }
//     if (size == 1)
//     {
//         fprintf(file, "POP AL\n");
//         fprintf(file, "MOV [origin + %d],AL\n", GetVarFromSymbolTable(table, A)->offset);
//     }
// }

// f_actualparam_list(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     // fprintf(file , "MOV EAX , [origin + %d] \n",  GetVarFromSymbolTable(table, A)->offset);
//     if (size == 4)
//     {
//         fprintf(file, "PUSH DWORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     }
//     if (size == 2)
//     {
//         fprintf(file, "PUSH WORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     }
//     if (size == 1)
//     {
//         fprintf(file, "PUSH BYTE [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
//     }
// }

// f_output_param(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     if (size == 4)
//         fprintf(file, "PUSH DWORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

//     if (size == 2)
//         fprintf(file, "PUSH WORD [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);

//     if (size == 1)
//         fprintf(file, "PUSH BYTE [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
// }

// f_funtion_end(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MOV rsp, rbp\n");
//     fprintf(file, "POP rbp\n");
//     fprintf(file, "ret\n");
// }

// f_function_call(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "CALL %s\n", GetVarFromSymbolTable(table, A)->offset);
// }

// f_print(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "mov ebx, 1\n");
//     fprintf(file, "mov ecx, %s\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "mov edx, %d\n", GetVarFromSymbolTable(table, width)->offset);
//     fprintf(file, "mov eax, 4\n");
//     fprintf(file, "int 0x80");
// }

// f_print_array(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "Label%d , mov ecx , %d", case_label, GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, " DEC ECX ");
//     f_print(table, A, B, C);
//     fprintf(file, "CMP ECX, 0");
//     fprintf(file, "JNZ Label%d", GetVarFromSymbolTable(table, A)->offset);
// }

// f_takeinput(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "mov ebx, 0\n");
//     fprintf(file, "mov ecx, %s\n", GetVarFromSymbolTable(table, A)->offset);
//     fprintf(file, "mov edx, %d\n", GetVarFromSymbolTable(table, width)->offset);
//     fprintf(file, "mov eax, 3\n");
//     fprintf(file, "int 0x80");
// }

// f_moduleDeclare(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "extern %s", GetVarFromSymbolTable(table, name)->offset);
// }

// f_driverModule(SYMBOLTABLE table, TREENODE A, TREENODE B, TREENODE C)
// {
//     fprintf(file, "MAIN : ");
// }

// f_drivermoduleEnd()
// {
//     fprinf(file, "END");
// }

void CodeGeneration(){
    FILE *file = fopen("finalCode.asm", "w");
    if (file == NULL)
    {
        printf("CAN NOT OPEN FILE\n\n");
        return;
    }

    fprintf(file,"global main\n");
    fprintf(file,"extern printf\n\n");

    fprintf(file, "section .data\n");
    fprintf(file,"\t\torigin db 10\n\n");

    fprintf(file,"section .text\n");
    

    int for_label = 0;
    int while_label = 0;
    int case_label = 0;
    int switch_label = 0;


    while (1)
    {
        QUADRUPLEROW qr = getRowFromQuadruple();
        // printQuadRupleRow(qr);
        // printf("\n\n");
        // printQuadRupleRow(qr);

        int CONSTRUCT = qr->operator;
        SYMBOLTABLE table = qr->ST;
        fprintf(file, "\n\n");
        switch (CONSTRUCT)
        {
        case 0: // MODULE_DECLARATION,
        {
            TREENODE name = qr->left;
            fprintf(file, "extern %s", GetFuncFromSymbolTable(GST, name)->id->lexemedata->data);
            break;
        }

        case 1: // DRIVER_MODULE,
        {
            fprintf(file, "main : ");
            break;
        }

        case 2: // MODULE_DEFINITION,
        {
            TREENODE name = qr->left;
            printASTNODE(name);
            fprintf(file, "%s : ", GetFuncFromSymbolTable(GST, name)->id->lexemedata->data);
            fprintf(file, "PUSH rbp\n");
            fprintf(file, "MOV rbp,rsp\n");
            break;
        }

        case 3: // FORMAL_INPUT_PARAMS,
        {
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table, qr->left);

            if (ip->isDynamic == -1)
            {
                int size = getWidth(ip);
                printf("%d\n\n", size);
                if (size == 4)
                {
                    fprintf(file, "POP EAX\n");
                    fprintf(file, "MOV EAX , [origin + %d]\n", ip->offset);
                }
                if (size == 2)
                {
                    fprintf(file, "POP AX\n");
                    fprintf(file, "MOV AX , [origin + %d]\n", ip->offset);
                }
                if (size == 1)
                {
                    fprintf(file, "POP AL\n");
                    fprintf(file, "MOV AL , [origin + %d]\n", ip->offset);
                }
            }
            else
            {
                printf("HELLO\n\n");
            }

            break;
        }

        case 4: // FORMAL_OUTPUT_PARAMS,
        {
            SYMBOLTABLEROW op = GetVarFromSymbolTable(table, qr->left);
            int size = getWidth(op);
            if (size == 4)
                fprintf(file, "PUSH DWORD [origin + %d]\n", op->offset);

            if (size == 2)
                fprintf(file, "PUSH WORD [origin + %d]\n", op->offset);

            if (size == 1)
                fprintf(file, "PUSH BYTE [origin + %d]\n", op->offset);
            break;
        }

        case 5: // MODULE_REUSE,
        {

            fprintf(file, "CALL %s\n", GetFuncFromSymbolTable(table, qr->left)->id->lexemedata->data);
            break;
        }

        case 6: // MODULE_END,
        {
            fprintf(file, "MOV rsp, rbp\n");
            fprintf(file, "POP rbp\n");
            fprintf(file, "ret\n");
            break;
        }

        case 7:
        { // declare variable
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table, qr->left);
            if (ip->isDynamic == -1)
            {
                int size = getWidth(ip);
                if (size == 4)
                {
                    fprintf(file, "MOV EAX,0\n");
                    fprintf(file, "MOV EAX , [origin + %d]\n", ip->offset);
                }
                if (size == 2)
                {
                    fprintf(file, "MOV AX,0\n");
                    fprintf(file, "MOV AX , [origin + %d]\n", ip->offset);
                }
                printf("%d\n",ip->offset);
                if (size == 1)
                {
                    fprintf(file, "MOV AL,0\n");
                    fprintf(file, "MOV AL , [origin + %d]\n", ip->offset);
                }
            }

            else
            {
                printf("HELLO\n\n");
            }
            break;
        }

        case 8:{
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table,qr->left);
            if(ip->isDynamic == -1){
                fprintf(file, "mov ebx, 0\n");
                fprintf(file, "mov ecx, %d\n", ip->offset);
                fprintf(file, "mov edx, %d\n", getWidth(ip));
                fprintf(file, "mov eax, 3\n");
                fprintf(file, "int 0x80");
        }

            break;
        }

        case 9:
        { 
        SYMBOLTABLEROW ip = GetVarFromSymbolTable(table,qr->left);
        if(ip->isDynamic == -1){
            if(ip->type == TYPE_INTEGER){
                    fprintf(file,"mov rdi,integer_printf_format\n\n");
                    fprintf(file,"mov rsi,[origin + %d]\n\n",ip->offset);
                    fprintf(file,"xor rax,rax\n\n");
                    fprintf(file,"call printf WRT ..plt\n\n");
                    // fprintf(file,"mov rax,60\nsyscall\n");
            }
            else{
                printf("fkdslg\n\n");
            }
        }

            break;
        }

        case 10: // pass_param
        {
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table, qr->left);
            if (ip->isDynamic == -1)
            {
                int size = getWidth(ip);
                if (size == 4)
                {
                    fprintf(file, "PUSH DWORD [origin + %d]\n", ip->offset);
                }
                if (size == 2)
                {
                    fprintf(file, "PUSH WORD [origin + %d]\n", ip->offset);
                }
                if (size == 1)
                {
                    fprintf(file, "PUSH BYTE [origin + %d]\n", ip->offset);
                }
            }
            else
            {
                printf("HEMLLPO\n\n\n");
            }

            break;
        }

        case 11:
        { // get_return
            break;
        }

        case 12: // for_start
        {

            int lowRange = qr->op1->TREENODEDATA->terminal->lexemedata->intData;
            int highRange = qr->op2->TREENODEDATA->terminal->lexemedata->intData;
            SYMBOLTABLEROW i = GetVarFromSymbolTable(qr->ST, qr->left);
            if (i == NULL)
            {
                printf("\n\nBT\n\n");
            }
            fprintf(file, "MOV AX, %d\n", lowRange);
            fprintf(file, "MOV CX, %d\n", highRange);
            fprintf(file, "MOV AX, [origin + %d]\n", i->offset);
            fprintf(file, "MOV DX, AX\n");

            fprintf(file, "SUB CX, AX\n");
            fprintf(file, "INC CX\n");

            fprintf(file, "FOR_LABEL_%d:\n", for_label++); /// HOW TO PRINT LABEL
            fprintf(file, "DEC CX\n");
            fprintf(file, "ADD DX, 1\n");
            fprintf(file, "MOV DX, [origin + %d]\n", i->offset);
            break;
        }

        case 13: // for_end
        {
            fprintf(file, "CMP CX, 0\n");
            fprintf(file, "JNZ FOR_LABEL_%d", for_label++);
            break;
        }

        case 14: // swtich_start
        {
            SYMBOLTABLEROW i = GetVarFromSymbolTable(qr->ST, qr->left);
            fprintf(file, "MOV [origin + %d],AX\n", i->offset);
            if (i->type == TYPE_BOOLEAN)
            {
                fprintf(file, "MOV AH, 0\n");
            }
            break;
        }

        case 15: // switch_end
        {
            fprintf(file, "SWITCH_END_%d:\n", switch_label++);
            break;
        }

        case 16: // case_start
        {

            fprintf(file, "CASE_LABEL_%d: ", case_label);
            fprintf(file, "CMP AX, %d\n", qr->left->TREENODEDATA->terminal->lexemedata->intData);
            fprintf(file, "JNE CASE_LABEL_%d\n", ++case_label);
            break;
        }

        case 17: // case_break
        {
            fprintf(file, "JUMP SWITCH_END_%d\n", switch_label);
            break;
        }

        case 18:
        { // default_start
            fprintf(file, "CASE_LABEL_%d:\n", case_label);
            break;
        }

        case 19:
        { // while_start
        // fprintf(file, "MOV EAX, [origin + %d]\n", GetVarFromSymbolTable(table, A)->offset);
        // fprintf(file, "CMP EAX, 0\n");
        // fprintf(file, "JNZ WHILE_LABEL_END%d", while_index);
        // fprintf(file, "WHILE_LABEL_%d:\n", while_index);
        // break;
        }

        case 20:
        { // while_end
        // fprintf(file, "JUMP WHILE_LABEL_%d", while_index);
        // fprintf(file, "WHILE_LABEL_END%d:\n", while_index++);
        // break;
        }

        case 21:
        { // assign
            SYMBOLTABLEROW a = GetVarFromSymbolTable(qr->ST,qr->left);
            if(a->isDynamic == -1){
                if(a->type == TYPE_BOOLEAN){
                    if(qr->op1->TREENODEDATA->terminal->token == TRUE_BOOL){
                        fprintf(file,"MOV AL, '1'\n");
                        fprintf(file,"MOV [origin + %d] , AL\n",a->offset);
                    }
                    else if(qr->op1->TREENODEDATA->terminal->token == FALSE_BOOL){
                        fprintf(file,"MOV AL, '0'\n");
                        fprintf(file,"MOV [origin + %d] , AL\n",a->offset);
                    }
                    else{
                        SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST,qr->op1);
                        fprintf(file,"MOV AL, [origin + %d]\n",b->offset);
                        fprintf(file,"MOV [origin + %d] ,AL\n",a->offset);
                    }
                    

                }
                else if(a->type == TYPE_INTEGER){
                    if(qr->op1->TREENODEDATA->terminal->token == NUM_TOKEN){
                        fprintf(file,"MOV AX, %d\n",qr->op1->TREENODEDATA->terminal->lexemedata->intData);
                        fprintf(file,"MOV [origin + %d], AX\n",a->offset);
                    }
                    else{
                        SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST,qr->op1);
                        fprintf(file,"MOV AX, [origin + %d]\n",b->offset);
                        fprintf(file,"MOV [origin + %d], AX\n",a->offset);
                    }
                    

                }
                else if(a->type == TYPE_REAL){
                    if(qr->op1->TREENODEDATA->terminal->token == RNUM_TOKEN){
                        fprintf(file,"MOV EAX, %f\n",qr->op1->TREENODEDATA->terminal->lexemedata->floatData);
                        fprintf(file,"MOV [origin + %d], EAX\n",a->offset);
                    }
                    else{
                        SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST,qr->op1);
                        fprintf(file,"MOV EAX, [origin + %d]\n",b->offset);
                        fprintf(file,"MOV [origin + %d] , EAX\n",a->offset);
                    }

                }
                
            }
            else{
                printf("ARRAY AAYA HAI\n\n\n");
            }
            break;
            
        }

        case 22:
        { // addition
            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);
            printf("%d\n",C->offset);

            if (C->type == TYPE_REAL)
            {
                fprintf(file, "MOV EAX, [origin + %d]\n", A->offset);
                fprintf(file, "ADD EAX, [origin + %d]\n", B->offset);
                fprintf(file, "MOV [origin + %d] , EAX\n", C->offset);
            }
            else
            {
                fprintf(file, "MOV AX, [origin + %d]\n", A->offset);
                fprintf(file,  "ADD AX, [origin + %d]\n", B->offset);
                fprintf(file,  "MOV [origin + %d] , AX\n", C->offset);
            }
            break;
        }

        case 23:
        { // subtraction
            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);

            if (C->type == TYPE_REAL)
            {
                fprintf(file, "MOV EAX, [origin + %d]\n", A->offset);
                fprintf(file, "SUB EAX, [origin + %d]\n", B->offset);
                fprintf(file, "MOV [origin + %d] , EAX\n", C->offset);
            }
            else
            {
                fprintf(file, "MOV AX, [origin + %d]\n", A->offset);
                fprintf(file, "SUB AX, [origin + %d]\n", B->offset);
                fprintf(file, "MOV [origin + %d] , AX\n", C->offset);
            }
            
            break;
        }

        case 24:
        { // multiply

            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);

            if (C->type == TYPE_REAL)
            {
                fprintf(file, "MOV EAX,[origin + %d]\n", A->offset);
                fprintf(file, "MOV EBX,[origin + %d]\n", B->offset);
                fprintf(file, "MUL EBX\n");
                fprintf(file, "MOV [origin + %d], EAX\n", C->offset);
            }
            else
            {
            fprintf(file, "MOV AX,[origin + %d]\n", A->offset);
                fprintf(file, "MOV BX,[origin + %d]\n", B->offset);
                fprintf(file, "MUL BX\n");
                fprintf(file, "MOV [origin + %d], AX\n", C->offset);
            }
            break;
        }

        case 25:
        { // division
            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);
            fprintf(file, "MOV EAX,[origin + %d]\n", A->offset);
            fprintf(file, "MOV EBX,[origin + %d]\n", B->offset);

            if (A->type == TYPE_INTEGER)
            {
                fprintf(file, "AND EAX, 0000FFFFh\n");
            }
            if (B->type == TYPE_INTEGER)
            {
                fprintf(file, "AND EBX, 0000FFFFh\n");
            }
            fprintf(file, "DIV EBX\n");
            fprintf(file, "MOV [origin + %d], EAX\n", C->offset);
            break;
        }

        case 26: //lessthan
        {
        fprintf(file, "mov eax, [var1]\n");     ; move the value of var1 into eax
        fprintf(file, "cmp eax, [var2]\n");     ; compare eax with the value of var2
        jl less_than 
            break;
        }
        case 27:
        {
            break;
        }
        case 28:
        {
            break;
        }
        case 29:
        {
            fprintf(file, "MOV EAX, 1\nXOR EBX, EBX\nINT 0x80\n");
                fprintf(file, "section .data\n");
                fprintf(file,"\t\tinteger_printf_format: db \"%%d\" ,10,0\n");
                fprintf(file,"\t\treal_printf_format: db \"%%f\" ,25,0\n");
            return;
            break;
        }
        case 30:
        {
            break;
        }
        }
    }

        // fprintf(file, "MOV EAX 1\n\nXOR EBX EBX\n\nINT 0x80\n\n");
}

