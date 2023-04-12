section .data
origin dd 1000

section .text
global _start

_start : 

MOV AX,0
MOV RBX, origin + 0 
MOV AX, [RBX]


MOV AX,0
MOV RBX , origin
MOV AX, [RBX]


MOV AX, 1
MOV AX, [origin + 2]


MOV RBX, origin + 2
MOV AX, [RBX]
MOV AX, [origin + 0]

MOV RBX, 1
MOV RCX,origin
MOV RDX, 50
MOV RAX, 4
int 0X80

MOV EBX, origin

MOV EAX ,1
INT 0x80

