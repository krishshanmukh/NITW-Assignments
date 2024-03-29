.MODEL SMALL
.STACK 64
VIDEO_SEG SEGMENT AT 0B800H
VID_AREA DB 1000H DUP(?)
VIDEO_SEG ENDS
.286
.CODE
A10MAIN PROC FAR
MOV AX,VIDEO_SEG
MOV ES,AX
ASSUME ES:VIDEO_SEG
MOV AH,0FH
INT 10H
PUSH AX
PUSH BX
MOV AX,0003H
INT 10H
MOV AX,0500H
INT 10H
CALL B10DISPLAY
MOV AH,10H
INT 16H
MOV AH,05H
POP BX
MOV AL,BH
INT 10H
POP AX
MOV AH,00H
INT 10H
MOV AX,4C00H
INT 21H
A10MAIN ENDP

B10DISPLAY PROC NEAR
PUSHA
MOV AL,41H
MOV AH,0A8H
MOV DI,820
B20: MOV CX,60
B30: MOV ES:WORD PTR[DI],AX
ADD DI,2
LOOP B30
INC AH
INC AL
ADD DI,40
CMP AL,51H
JNE B20
POPA
RET
B10DISPLAY ENDP
END A10MAIN