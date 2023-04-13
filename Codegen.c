//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#include <stdio.h>
#include <stdlib.h>

#include "Codegen.h"

int bool_count = 0;

void CodeGeneration(char* fname)
{
    FILE *file = fopen(fname, "w");
    if (file == NULL)
    {
        printf("CAN NOT OPEN FILE\n\n");
        return;
    }

    fprintf(file, "global _start\n");
    fprintf(file, "global _flip\n\n");

    fprintf(file, "section .data\n");
    fprintf(file, "for_count_value dw 0\nscan_msg db \"Enter your number :\"\nbuffer  db  6\norigin db 10\n\n");

    fprintf(file, "section .text\n");
    fprintf(file, "extern printf\n\n");

    int bool_count = 0;
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

            fprintf(file, "_start : \n");
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
                int size = getWidth(ip, 1);
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
            int size = getWidth(op, 0);
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
                int size = getWidth(ip, 0);
                if (size == 4)
                {
                    fprintf(file, "MOV EAX,0\n");
                    fprintf(file, "MOV [origin + %d], EAX\n", ip->offset);
                }
                if (size == 2)
                {
                    fprintf(file, "MOV AX,0\n");
                    fprintf(file, "MOV [origin + %d], AX\n", ip->offset);
                }
                if (size == 1)
                {
                    fprintf(file, "MOV AL,0\n");
                    fprintf(file, "MOV [origin + %d], AL\n", ip->offset);
                }
            }

            else
            {
                printf("HELLO\n\n");
            }
            break;
        }

        case 8:
        { // getr_value
                SYMBOLTABLEROW ip = GetVarFromSymbolTable(table,qr->left);
                if(ip->isDynamic == -1){
                    fprintf(file, "mov ebx,1\n");
                    fprintf(file, "mov ecx,scan_msg\n");
                    fprintf(file, "mov edx,19\n");
                    fprintf(file, "mov eax,4\n");
                    fprintf(file, "int 0x80\n");
                   
                    fprintf(file, "mov rbx, 0\n");
                    fprintf(file, "mov rcx, origin + %d\n", ip->offset);
                    fprintf(file, "mov rdx, %d\n", getWidth(ip,0));
                    fprintf(file, "mov rax, 3\n");
                    fprintf(file, "int 0x80\n\n");

                    fprintf(file, "mov ax, [origin + %d]\n",ip->offset);
                    fprintf(file,"sub ax,'0'\n");
                    fprintf(file, "mov [origin + %d],ax \n",ip->offset);
            }

            break;
        }

        case 9: // print
        {
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table, qr->left);
            if (ip->isDynamic == -1)
            {
                fprintf(file, "MOV AX, [origin + %d]\n",ip->offset );
                fprintf(file, "ADD AX , '0'\n");
                fprintf(file, "MOV [origin + %d] , AX\n",ip->offset);
                fprintf(file, "mov ebx,1\n");
                
                fprintf(file, "mov ecx, origin + %d\n",ip->offset);
                fprintf(file, "mov edx,2\n");
                fprintf(file, "mov eax,4\n");
                fprintf(file, "int 0x80\n");
                break;
            }

        case 10: // pass_param
        {
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table, qr->left);
            if (ip->isDynamic == -1)
            {
                int size = getWidth(ip, 1);
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
            int for_count = qr->data;

            int lowRange = qr->op1->TREENODEDATA->terminal->lexemedata->intData;
            printf("\nlolol\n");
            int highRange = qr->op2->TREENODEDATA->terminal->lexemedata->intData;
            // printf("\nlolol\n");
            SYMBOLTABLEROW i = GetVarFromSymbolTable(qr->ST, qr->left);
            if (i == NULL)
            {
                printf("\n\nBT\n\n");
            }
            fprintf(file, "MOV AX, %d\n", lowRange);
            fprintf(file, "MOV CX, %d\n", highRange);
            fprintf(file, "MOV [origin + %d], AX\n", i->offset);
            fprintf(file, "MOV DX, AX\n");

            fprintf(file, "SUB CX, AX\n");
            fprintf(file, "INC CX\n");

            fprintf(file, "FOR_LABEL_%d:\n", for_count); /// HOW TO PRINT LABEL
            fprintf(file, "DEC CX\n");
            fprintf(file, "MOV [for_count_value],CX\n");
            fprintf(file, "ADD DX, 1\n");
            fprintf(file, "MOV [origin + %d], DX\n", i->offset);
            break;
        }

        case 13: // for_end
        {
            int for_count = qr->data;
            fprintf(file, "MOV CX,[for_count_value]\n");
            fprintf(file, "CMP CX, 0\n");
            fprintf(file, "JNZ FOR_LABEL_%d", for_count);
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
            int switch_label = qr->data;
            fprintf(file, "SWITCH_END_%d:\n", switch_label);
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
            int while_count = qr->data;
            SYMBOLTABLEROW ip = GetVarFromSymbolTable(table, qr->left);
            fprintf(file, "MOV EAX, [origin + %d]\n", ip->offset);
            fprintf(file, "CMP EAX, 0\n");
            fprintf(file, "JNZ WHILE_LABEL_END%d", while_count);
            fprintf(file, "WHILE_LABEL_%d:\n", while_count);
            break;
        }

        case 20:
        { // while_end
            int while_count = qr->data;
            fprintf(file, "JUMP WHILE_LABEL_%d", while_count);
            fprintf(file, "WHILE_LABEL_END%d:\n", while_count++);
            break;
        }

        case 21:
        { // assign
            SYMBOLTABLEROW a = GetVarFromSymbolTable(qr->ST, qr->left);
            if (a->isDynamic == -1)
            {
                if (a->type == TYPE_BOOLEAN)
                {
                    if (qr->op1->TREENODEDATA->terminal->token == TRUE_BOOL)
                    {
                        fprintf(file, "MOV AL, '1'\n");
                        fprintf(file, "MOV [origin + %d] , AL\n", a->offset);
                    }
                    else if (qr->op1->TREENODEDATA->terminal->token == FALSE_BOOL)
                    {
                        fprintf(file, "MOV AL, '0'\n");
                        fprintf(file, "MOV [origin + %d] , AL\n", a->offset);
                    }
                    else
                    {
                        SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST, qr->op1);
                        fprintf(file, "MOV AL, [origin + %d]\n", b->offset);
                        fprintf(file, "MOV [origin + %d] ,AL\n", a->offset);
                    }
                }
                else if (a->type == TYPE_INTEGER)
                {
                    if (qr->op1->TREENODEDATA->terminal->token == NUM_TOKEN)
                    {
                        fprintf(file, "MOV AX, %d\n", qr->op1->TREENODEDATA->terminal->lexemedata->intData);
                        fprintf(file, "MOV [origin + %d], AX\n", a->offset);
                    }
                    else
                    {
                        SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST, qr->op1);
                        fprintf(file, "MOV AX, [origin + %d]\n", b->offset);
                        fprintf(file, "MOV [origin + %d], AX\n", a->offset);
                    }
                }
                else if (a->type == TYPE_REAL)
                {
                    if (qr->op1->TREENODEDATA->terminal->token == RNUM_TOKEN)
                    {
                        fprintf(file, "MOV EAX, %f\n", qr->op1->TREENODEDATA->terminal->lexemedata->floatData);
                        fprintf(file, "MOV [origin + %d], EAX\n", a->offset);
                    }
                    else
                    {
                        SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST, qr->op1);
                        fprintf(file, "MOV EAX, [origin + %d]\n", b->offset);
                        fprintf(file, "MOV [origin + %d] , EAX\n", a->offset);
                    }
                }
            }
            break;
        }

        case 22:
        { // addition
            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);

            if (C->type == TYPE_REAL)
            {
                fprintf(file, "MOV EAX, [origin + %d]\n", A->offset);
                fprintf(file, "ADD EAX, [origin + %d]\n", B->offset);
                fprintf(file, "MOV [origin + %d] , EAX\n", C->offset);
            }
            else
            {
                fprintf(file, "MOV AX, [origin + %d]\n", A->offset);
                fprintf(file, "ADD AX, [origin + %d]\n", B->offset);
                fprintf(file, "MOV [origin + %d] , AX\n", C->offset);
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
            if(qr->op1->TREENODEDATA->terminal->token == NUM_TOKEN){
                fprintf(file, "MOV AX,%d\n", qr->op1->TREENODEDATA->terminal->lexemedata->intData);
            }
            else if(qr->op1->TREENODEDATA->terminal->token == RNUM_TOKEN){
                printf("NOT IMPLEMENTED\n\n");
            }
            else{
                SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
                fprintf(file, "MOV AX,[origin + %d]\n", A->offset);
            }
            if(qr->op2->TREENODEDATA->terminal->token == NUM_TOKEN){
                fprintf(file, "MOV BX,%d\n", qr->op2->TREENODEDATA->terminal->lexemedata->intData);
            }
            else if(qr->op1->TREENODEDATA->terminal->token == RNUM_TOKEN){
                printf("NOT IMPLEMENTED\n\n");
            }
            else{
                SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);
                fprintf(file, "MOV BX,[origin + %d]\n", B->offset);
            }
            if (C->type == TYPE_REAL)
            {
                fprintf(file, "MUL EBX\n");
                fprintf(file, "MOV [origin + %d], EAX\n", C->offset);
            }
            else
            {
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

        case 26: // unary_minus
        {
            break;
        }

        case 27: // array_access
        {
            break;
        }

        case 28: // array_assignment
        {
            // SYMBOLTABLEROW a = GetVarFromSymbolTable(qr->ST,qr->left);
            // // fprintf(file, "Label%d , mov ecx , %d", case_label, numberofelementsinarray);
            // fprintf(file, " DEC ECX ");

            // if (a->isDynamic == -1)
            // {
            //     if (a->type == TYPE_BOOLEAN)
            //     {
            //         if (qr->op1->TREENODEDATA->terminal->token == TRUE_BOOL)
            //         {
            //             fprintf(file, "MOV AL, '1'\n");
            //             fprintf(file, "MOV [origin + %d] , AL\n", a->offset);
            //         }
            //         else if (qr->op1->TREENODEDATA->terminal->token == FALSE_BOOL)
            //         {
            //             fprintf(file, "MOV AL, '0'\n");
            //             fprintf(file, "MOV [origin + %d] , AL\n", a->offset);
            //         }
            //         else
            //         {
            //             SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST, qr->op1);
            //             fprintf(file, "MOV AL, [origin + %d]\n", b->offset);
            //             fprintf(file, "MOV [origin + %d] ,AL\n", a->offset);
            //         }
            //     }
            //     else if (a->type == TYPE_INTEGER)
            //     {
            //         if (qr->op1->TREENODEDATA->terminal->token == NUM_TOKEN)
            //         {
            //             fprintf(file, "MOV AX, %d\n", qr->op1->TREENODEDATA->terminal->lexemedata->intData);
            //             fprintf(file, "MOV [origin + %d + %d - ECX*2], AX\n", a->offset , width);
            //         }
            //         else
            //         {
            //             SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST, qr->op1);
            //             fprintf(file, "MOV AX, [origin + %d]\n", b->offset);
            //             fprintf(file, "MOV [origin + %d], AX\n", a->offset);
            //         }
            //     }
            //     else if (a->type == TYPE_REAL)
            //     {
            //         if (qr->op1->TREENODEDATA->terminal->token == RNUM_TOKEN)
            //         {
            //             fprintf(file, "MOV EAX, %f\n", qr->op1->TREENODEDATA->terminal->lexemedata->floatData);
            //             fprintf(file, "MOV [origin + %d], EAX\n", a->offset);
            //         }
            //         else
            //         {
            //             SYMBOLTABLEROW b = GetVarFromSymbolTable(qr->ST, qr->op1);
            //             fprintf(file, "MOV EAX, [origin + %d]\n", b->offset);
            //             fprintf(file, "MOV [origin + %d] , EAX\n", a->offset);
            //         }
            //     }
            // }

            // fprintf(file, "CMP ECX, 0");
            // fprintf(file, "JNZ Label%d", case_label);

            break;
        }

        case 29: // driver module end
        {
            fprintf(file, "MOV EAX, 1\nXOR EBX, EBX\nINT 0x80\n");
            // fprintf(file, "section .data\n");
            // fprintf(file, "\t\tinteger_printf_format: db \"%%d\" ,10,0\n");
            // fprintf(file, "\t\treal_printf_format: db \"%%f\" ,25,0\n");
            return;
        }

        case 30: // lessthan
        {
            SYMBOLTABLEROW c = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW a = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW b = GetVarFromSymbolTable(table, qr->op2);

            if (a->type == TYPE_INTEGER)
            {
                fprintf(file, "mov ax, [origin + %d]\n", a->offset);
                fprintf(file, "mov bx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp ax, bx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jl bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_REAL)
            {
                fprintf(file, "mov eax, [origin + %d]\n", a->offset);
                fprintf(file, "mov ebx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp eax, ebx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jl bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_BOOLEAN)
            {
                fprintf(file, "mov al, [origin + %d]\n", a->offset);
                fprintf(file, "mov bl, [origin + %d]\n", b->offset);
                fprintf(file, "cmp al, bl\n");
                fprintf(file, "mov cl,1\n");
                fprintf(file, "mov dl,0\n");
                fprintf(file, "mov [origin+%d], cl", c->offset);
                fprintf(file, "jl bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , dl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }
            break;
        }

        case 31: // lessthanequalto
        {
            SYMBOLTABLEROW c = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW a = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW b = GetVarFromSymbolTable(table, qr->op2);

            if (a->type == TYPE_INTEGER)
            {
                fprintf(file, "mov ax, [origin + %d]\n", a->offset);
                fprintf(file, "mov bx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp ax, bx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jle bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_REAL)
            {
                fprintf(file, "mov eax, [origin + %d]\n", a->offset);
                fprintf(file, "mov ebx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp eax, ebx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jle bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_BOOLEAN)
            {
                fprintf(file, "mov al, [origin + %d]\n", a->offset);
                fprintf(file, "mov bl, [origin + %d]\n", b->offset);
                fprintf(file, "cmp al, bl\n");
                fprintf(file, "mov cl,1\n");
                fprintf(file, "mov dl,0\n");
                fprintf(file, "mov [origin+%d], cl", c->offset);
                fprintf(file, "jle bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , dl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }
            break;
        }

        case 32: // greaterthan
        {
            SYMBOLTABLEROW c = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW a = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW b = GetVarFromSymbolTable(table, qr->op2);

            if (a->type == TYPE_INTEGER)
            {
                fprintf(file, "mov ax, [origin + %d]\n", a->offset);
                fprintf(file, "mov bx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp ax, bx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jg bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_REAL)
            {
                fprintf(file, "mov eax, [origin + %d]\n", a->offset);
                fprintf(file, "mov ebx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp eax, ebx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jg bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_BOOLEAN)
            {
                fprintf(file, "mov al, [origin + %d]\n", a->offset);
                fprintf(file, "mov bl, [origin + %d]\n", b->offset);
                fprintf(file, "cmp al, bl\n");
                fprintf(file, "mov cl,1\n");
                fprintf(file, "mov dl,0\n");
                fprintf(file, "mov [origin+%d], cl", c->offset);
                fprintf(file, "jg bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , dl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }
            break;
        }

        case 33: // greaterthanequal
        {
            SYMBOLTABLEROW c = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW a = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW b = GetVarFromSymbolTable(table, qr->op2);

            if (a->type == TYPE_INTEGER)
            {
                fprintf(file, "mov ax, [origin + %d]\n", a->offset);
                fprintf(file, "mov bx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp ax, bx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jge bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_REAL)
            {
                fprintf(file, "mov eax, [origin + %d]\n", a->offset);
                fprintf(file, "mov ebx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp eax, ebx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jge bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_BOOLEAN)
            {
                fprintf(file, "mov al, [origin + %d]\n", a->offset);
                fprintf(file, "mov bl, [origin + %d]\n", b->offset);
                fprintf(file, "cmp al, bl\n");
                fprintf(file, "mov cl,1\n");
                fprintf(file, "mov dl,0\n");
                fprintf(file, "mov [origin+%d], cl", c->offset);
                fprintf(file, "jge bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , dl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }
            break;
        }

        case 34: // equal
        {
            SYMBOLTABLEROW c = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW a = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW b = GetVarFromSymbolTable(table, qr->op2);

            if (a->type == TYPE_INTEGER)
            {
                fprintf(file, "mov ax, [origin + %d]\n", a->offset);
                fprintf(file, "mov bx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp ax, bx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "je bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_REAL)
            {
                fprintf(file, "mov eax, [origin + %d]\n", a->offset);
                fprintf(file, "mov ebx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp eax, ebx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "je bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_BOOLEAN)
            {
                fprintf(file, "mov al, [origin + %d]\n", a->offset);
                fprintf(file, "mov bl, [origin + %d]\n", b->offset);
                fprintf(file, "cmp al, bl\n");
                fprintf(file, "mov cl,1\n");
                fprintf(file, "mov dl,0\n");
                fprintf(file, "mov [origin+%d], cl", c->offset);
                fprintf(file, "je bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , dl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }
            break;
        }

        case 35: // notequal
        {
            SYMBOLTABLEROW c = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW a = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW b = GetVarFromSymbolTable(table, qr->op2);

            if (a->type == TYPE_INTEGER)
            {
                fprintf(file, "mov ax, [origin + %d]\n", a->offset);
                fprintf(file, "mov bx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp ax, bx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jne bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_REAL)
            {
                fprintf(file, "mov eax, [origin + %d]\n", a->offset);
                fprintf(file, "mov ebx, [origin + %d]\n", b->offset);
                fprintf(file, "cmp eax, ebx\n");
                fprintf(file, "mov al,1\n");
                fprintf(file, "mov bl,0\n");
                fprintf(file, "mov [origin+%d], al", c->offset);
                fprintf(file, "jne bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , bl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }

            if (a->type == TYPE_BOOLEAN)
            {
                fprintf(file, "mov al, [origin + %d]\n", a->offset);
                fprintf(file, "mov bl, [origin + %d]\n", b->offset);
                fprintf(file, "cmp al, bl\n");
                fprintf(file, "mov cl,1\n");
                fprintf(file, "mov dl,0\n");
                fprintf(file, "mov [origin+%d], cl", c->offset);
                fprintf(file, "jne bool_%d", bool_count);
                fprintf(file, "mov [origin + %d] , dl", c->offset);
                fprintf(file, "bool_%d", bool_count);
            }
            break;
        }

        case 36: // and
        {
            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);

            fprintf(file, "MOV AL, [origin + %d]\n", A->offset);
            fprintf(file, "AND AL, [origin + %d]\n", B->offset);
            fprintf(file, "MOV [origin + %d] , AL\n", C->offset);
            break;
        }

        case 37: // or
        {
            SYMBOLTABLEROW C = GetVarFromSymbolTable(table, qr->left);
            SYMBOLTABLEROW A = GetVarFromSymbolTable(table, qr->op1);
            SYMBOLTABLEROW B = GetVarFromSymbolTable(table, qr->op2);

            fprintf(file, "MOV AL, [origin + %d]\n", A->offset);
            fprintf(file, "OR AL, [origin + %d]\n", B->offset);
            fprintf(file, "MOV [origin + %d] , AL\n", C->offset);
            break;
        }
        }
        }

        // fprintf(file, "MOV EAX 1\n\nXOR EBX EBX\n\nINT 0x80\n\n");
    }
}

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
