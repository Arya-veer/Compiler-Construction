; section .text
;     default rel
;     extern printf
;     global main
; main:
;     ; Create a stack-frame, re-aligning the stack to 16-byte alignment before calls
;     push rbp

;     mov	rdi, fmt
;     mov	rsi, message
;     mov	rax, 0

;     ; Call printf
;     call printf wrt ..plt
    
;     pop	rbp		; Pop stack

;     mov	rax,0	; Exit code 0
;     ret			; Return
; section .data
;     message:  db        96
;     fmt:    db "%d", 10, 0


extern _printf
section .data
    DAT0: db 51
    DAT1: db "%d", 0

section .text 
    global main

main:
    mov r8, DAT0
    movzx ax, [r8]
    push rax
    push DAT1
    call _printf
    add esp, 8

    ret 0