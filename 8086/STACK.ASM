TITLE Stack Implementation
;----------------------------
        .MODEL SMALL
        .STACK 256
        .DATA
        MSG1 DB '1.PUSH 2.POP OTHER.EXIT $'
        MSG2 DB 'UNDERFLOW $'
        MSG3 DB 'OVERFLOW $'
        ARRAY DB 10 DUP(?)
;----------------------------
        .CODE
MAIN PROC FAR

        MOV AX,@DATA
        MOV DS,AX


        LEA SI,ARRAY
        DEC SI
        
   A10:
       ; MOV AH,02H
       ; MOV BH,00
       ; MOV DX,0010H
       ; INT 10H
        MOV AH,09H
        LEA DX,MSG1
        INT 21H
       ; MOV AX,0600H
       ; MOV BH,30H
       ; MOV CX,0000
       ; MOV DX,0825
       ; INT 10H


        MOV AH,02H
        MOV DL,0AH
        INT 21H
        

        MOV AH,01H
        INT 21H

        CMP AL,31H
        JE A20

        CMP AL,32H
        JE A30

        JMP A50

   A20: CALL INSERT
        JMP A40

   A30: CALL DELET

   A40:
        JMP A10

   A50: MOV AX,4C00H
        INT 21H
MAIN ENDP

;--------------------------------

INSERT PROC NEAR

        LEA DI,ARRAY+9
        CMP SI,DI
        JNE I10

        MOV AH,09H
        LEA DX,MSG3
        INT 21H
        JMP I20

   I10: MOV AH,02H
        MOV DL,0AH
        INT 21H

        MOV AX,0000
        MOV AH,01H
        INT 21H

        INC SI
        MOV [SI],AL
        

   I20: RET

INSERT ENDP
                                    
;---------------------------------

DELET PROC NEAR


        LEA DI,ARRAY-1
        CMP DI,SI
        JNE D10

        MOV AH,09H
        LEA DX,MSG2
        INT 21H
        JMP D20

   D10: MOV AL,[SI]
        DEC SI

        MOV AH,02H
        MOV DL,AL
        INT 21H

   D20: RET

DELET ENDP

;----------------------------------
END MAIN
