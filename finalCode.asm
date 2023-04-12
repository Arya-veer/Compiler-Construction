global main
extern printf

section .data
		origin db 10

section .text


main : 

MOV AX,0
MOV AX , [origin + 0]


MOV AX,0
MOV AX , [origin + 2]


MOV AX, 7
MOV [origin + 2], AX


MOV AX, [origin + 2]
MOV [origin + 0], AX


MOV AX,0
MOV AX , [origin + 4]


MOV AX, [origin + 0]
ADD AX, [origin + 2]
MOV [origin + 6] , AX


MOV AX, [origin + 6]
MOV [origin + 4], AX


mov rdi,integer_printf_format

mov rsi,100

xor rax,rax

call printf WRT ..plt

    mov rax,60	; exit
    syscall

mov rdi,integer_printf_format

mov rsi,100

xor rax,rax

call printf WRT ..plt

    mov rax,60	; exit
    syscall

mov rdi,integer_printf_format

mov rsi,200

xor rax,rax

call printf WRT ..plt

    mov rax,60	; exit
    syscall

MOV EAX, 1
XOR EBX, EBX
INT 0x80
section .data
		integer_printf_format: db '%d' ,10,0
		real_printf_format: db '%f' ,25,0
