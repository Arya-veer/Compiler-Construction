section .data

section .text
global driver



driver : 

MOV AX,0
MOV BX , origin + 0
MOV AX, [BX]


MOV AX,0
MOV BX , origin + 2
MOV AX, [BX]


MOV AX, 10
MOV AX, [origin + 2]


MOV BX, origin + 2
MOV AX, [BX]
MOV AX, [origin + 0]


MOV EAX, 1

XOR EBX, EBX

INT 0x80

