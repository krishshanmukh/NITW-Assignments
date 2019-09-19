TITLE Priority Queue

        .MODEL SMALL
        .STACK 64
        .DATA
        TEMP DW 0000
        ARRAY DB 10 DUP('0'),'$'
        MSG DB '1.ENQUEUE 2.DEQUEUE OTHER.EXIT$'

        .CODE

MAIN PROC FAR

        MOV AX,@DATA
        MOV DS,AX
        MOV DI,0000
        MOV SI,0000

        A10 : CALL NEWLINE
        MOV AH,09H
        LEA DX,MSG
        INT 21H
        CALL NEWLINE

        MOV AH,01H
        INT 21H

        CMP AL,31H
        JE A20

        CMP AL,32H
        JE A30

        JMP A40

        A20: CALL ENQUEUE
        JMP A10

        A30: CALL DEQUEUE
        JMP A10

        A40: MOV AH,4CH
        INT 21H

MAIN ENDP

ENQUEUE PROC NEAR

        CALL NEWLINE

        MOV AH,01H
        INT 21H

        MOV ARRAY[SI],AL
        INC SI
        PUSH SI
        CALL HEAPIFY
        POP SI
        RET

ENQUEUE ENDP

NEWLINE PROC NEAR

        MOV AH,02H
        MOV DL,0AH
        INT 21H

        RET

NEWLINE ENDP

DEQUEUE PROC NEAR

        CALL NEWLINE

        MOV AH,02H
        MOV DL,ARRAY[0]
        INT 21H
        DEC SI

        MOV AL,ARRAY[SI]
        MOV ARRAY[0],AL
        MOV AL,30H
        MOV ARRAY[SI],AL
        DEC SI

        PUSH SI
        MOV TEMP,SI
        CALL DELHEAPIFY
        POP SI
        INC SI


        RET

DEQUEUE ENDP

HEAPIFY PROC NEAR

        DEC SI

        H10:
        CMP SI,0000
        JE H50
        DEC SI
        MOV AX,0000
        MOV AX,SI
        MOV DL,02
        DIV DL
        MOV AH,00
        MOV DI,AX
        INC SI
        MOV BL,ARRAY[DI]
        CMP BL,ARRAY[SI]
        JB H20
        XCHG BL,ARRAY[SI]
        MOV ARRAY[DI],BL

        H20: MOV SI,DI
        CMP AL,00H
        JNE H10

  H50:  
        CALL NEWLINE   
        MOV AH,09H
        LEA DX,ARRAY
        INT 21H
        RET

HEAPIFY ENDP

DELHEAPIFY PROC NEAR

        MOV DI,0000
        D10: MOV AX,0000
        MOV BL,02
        MOV AX,DI
        MUL BL
        MOV SI,AX
        INC SI
        CMP SI,TEMP
        JA D20
        CMP SI,TEMP
        JE D50
        MOV BL,ARRAY[SI]
        CMP BL,ARRAY[SI+1]
        JB D30
        INC SI
        CMP SI,TEMP
        JBE D50
        DEC SI
        JMP D30
        D50:
        MOV BL,ARRAY[SI]
        D30: 
        CMP BL,ARRAY[DI]
        JA D20
        XCHG BL,ARRAY[DI]
        XCHG BL,ARRAY[SI]

        D40: MOV DI,SI
        JMP D10

        D20: 
        CALL NEWLINE
        MOV AH,09H
        LEA DX,ARRAY
        INT 21H

        RET
DELHEAPIFY ENDP

END MAIN