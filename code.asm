extern printf

global main

section .text
main:
    push printf_format
    call printf
    add rsp,4


    mov rax,60	; exit
    syscall


section .data
    printf_format: db '%x',10,0