        global _start
        global _flip

        section .data
        for_count_value dw 0
        scan_msg db "Enter your number :"
        buffer  db  6
        origin db 10

        section .text
        extern printf



        _flip:
        xor r9, r9
        xor r10, r10
        xor rax, rax
        mov r9, r8
        flip_loop:
        mov rax, r10
        mul rbx
        mov r10, rax
        mov rax, r9
        div rbx
        add r10, rdx
        mov r9, rax
        inc r11
        test rax, rax
        jnz flip_loop
        ret

        _stringify:
        xor rdx, rdx   
        div rbx   
        add rdx, '0'  
        mov [rdi], rdx    
        inc rdi   
        inc rcx   
        dec r11   
        test r11, r11   
        jnz _stringify    
        ret

        _start : 


        MOV AX,0
        MOV [origin + 0], AX


        MOV AX,0
        MOV [origin + 2], AX


        MOV AX,0
        MOV [origin + 4], AX


        MOV AX,0
        MOV [origin + 6], AX


        MOV AX,0
        MOV [origin + 8], AX


        MOV AX,0
        MOV [origin + 10], AX


        MOV AX, 5
        MOV [origin + 6], AX


        MOV AX, 9
        MOV [origin + 8], AX


        MOV AX, 2
        MOV [origin + 0], AX


        MOV AX, 3
        MOV [origin + 2], AX


        MOV AX,[origin + 2]
        MOV BX,[origin + 8]
        MUL BX
        MOV [origin + 12], AX

        MOV AX, [origin + 0]
        ADD AX, [origin + 12]
        MOV [origin + 14] , AX

        MOV AX, [origin + 6]
        SUB AX, [origin + 8]
        MOV [origin + 16] , AX

        MOV AX,[origin + 16]
        MOV BX,[origin + 2]
        MUL BX
        MOV [origin + 18], AX

        mov ax, [origin + 18]
 add ax,'12'
 mov [origin + 18], ax
 mov ebx, 1
 mov ecx, origin + 18
 mov edx, 2
 mov eax, 4
 int 0x80

        MOV AX, [origin + 14]
        ADD AX, [origin + 18]
        MOV [origin + 20] , AX


        MOV AX,[origin + 6]
        MOV AX,2
        MUL BX
        MOV [origin + 22], AX


        MOV AX, [origin + 20]
        ADD AX, [origin + 22]
        MOV [origin + 24] , AX


        MOV AX,[origin + 8]
        MOV BX,[origin + 0]
        MUL BX
        MOV [origin + 26], AX


        MOV AX, [origin + 24]
        SUB AX, [origin + 26]
        MOV [origin + 28] , AX


        MOV AX, [origin + 28]
        MOV [origin + 4], AX

mov ax, [origin + 16]
 add ax,'4'
 mov [origin + 16], ax
 mov ebx, 1
 mov ecx, origin + 16
 mov edx, 2
 mov eax, 4
 int 0x80
        

        MOV EAX, 1
        XOR EBX, EBX
        INT 0x80
