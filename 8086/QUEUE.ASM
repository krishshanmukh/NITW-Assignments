TITLE Queue Implementation
;----------------------------
        .MODEL SMALL
        .STACK 256
        .DATA
        MSG1 DB '1.ENQUEUE   2.DEQUEUE   OTHER.EXIT $'
        MSG2 DB 'QUEUE IS FULL $'
        MSG3 DB 'QUEUE IS EMPTY $'
        ARRAY DB 10 DUP(?)
;----------------------------
        .CODE
MAIN PROC FAR

        MOV AX,@DATA
        MOV DS,AX


        LEA SI,ARRAY
        DEC SI
        MOV DI,SI
        LEA BX,ARRAY-1
        
   A10:
       ; MOV AH,02H
       ; MOV BH,00
       ; MOV DX,0010H
       ; INT 10H
       ; MOV AX,0600H
       ; MOV BH,30H
       ; MOV CX,0000
       ; MOV DX,0825
       ; INT 10H

        MOV AH,09H
        LEA DX,MSG1
        INT 21H
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

   A20: CALL ENQUEUE
        JMP A40

   A30: CALL DEQUEUE

   A40:
        JMP A10

   A50: MOV AX,4C00H
        INT 21H
MAIN ENDP

;--------------------------------

ENQUEUE PROC NEAR

        CMP SI,BX
        JNE E0
        INC SI
        INC DI
        JMP E10

     E0:
        CMP SI,DI
        JNE E10

        MOV AH,09H
        LEA DX,MSG2
        INT 21H
        JMP E20

     E10:   MOV AX,0000
        MOV AH,01H
        INT 21H

        INC DI
        MOV [DI],AL

     E20:     
               RET

ENQUEUE ENDP
                                    
;---------------------------------

DEQUEUE PROC NEAR

        CMP SI,DI
        JNE D10
        CMP SI,BX
        JNE D10
        MOV SI,BX
        MOV DI,BX
        MOV AH,09H
        LEA DX,MSG3
        INT 21H
        JMP D20


    D10:    MOV AH,02H
        MOV DL,0AH
        INT 21H

        MOV AL,[SI]
        INC SI

        MOV AH,02H
        MOV DL,AL
        INT 21H

     D20:   RET

DEQUEUE ENDP

;----------------------------------
END MAIN
