TITLE SCREENSAVER
.MODEL SMALL
.STACK 64
.DATA

MM DB ?
SE DB ?
HH DB ?
TEMP DB 00
MSG DB 'HI','$'

.CODE

MAIN PROC FAR
	MOV AX,@DATA
	MOV DX,AX
	M20:
	MOV AH,2CH
	INT 21H
	MOV HH,CH
	MOV MM,CL
	ADD DH,05
	MOV AH,00
	MOV AL,DH
	MOV DL,60D
	DIV DL
	MOV SE,AH
	M10:
	MOV AH,2CH
	INT 21H
	CMP DH,SE
	JNE M10
	CALL SCREENSAVER
	JMP M20
MAIN ENDP

SCREENSAVER PROC NEAR
	MOV AH,02H
	MOV DL,TEMP
	ADD DL,30H
	INT 21H
	MOV AL,TEMP
	CMP AL,00
	JNZ S20
	INC TEMP
	MOV BH,31H
	JMP S10
	S20:
	DEC TEMP 
	MOV BH,61H
	S10:
	MOV AX,0600H
	MOV CX,0000H
	MOV DX,184FH
	INT 10H
	RET
SCREENSAVER ENDP

END MAIN