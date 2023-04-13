section .data
    buffer  db  6           ; buffer to hold the string

section .text
global _start
global _flip

_start:
    mov r8, 12345          ; integer to convert
    mov rbx, 10             ; divisor for conversion
    xor rcx, rcx            ; initialize loop counter
    mov rdi, buffer         ; point to the beginning of the buffer
    call _flip
    mov rax, r10
    call _stringify

    mov rdx, rcx            ; set length of string
    mov rcx, buffer         ; point to the beginning of the buffer
    mov rax, 4              ; write system call
    mov rbx, 1              ; file descriptor (stdout)
    int 0x80                 ; call system call

    mov rax, 1            ; exit system call
    int 0x80                 ; call system call

; flips whatever is in r8 and stores it in r10
_flip:
    ; use the r9 register to store temporary vals
    ; use the r10 register to construct the number
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
        test rax, rax
        jnz flip_loop
        ret

; converts whatever is in rax to string (in reverse form)
_stringify:
    xor rdx, rdx            ; clear rdx for division
    div rbx                 ; divide eax by ebx
    add rdx, '0'             ; convert remainder to ASCII character
    mov [rdi], rdx           ; store character in buffer
    inc rdi                 ; move to next position in buffer
    inc rcx                 ; increment loop counter
    test rax, rax           ; check if eax is zero
    jnz convert_loop        ; if not, continue looping
    ret
