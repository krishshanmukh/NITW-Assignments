        TITLE ADD

        .MODEL SMALL
        .STACK 64
        .DATA
        FNUM DB '2136'
        SNUM DB '6985'
        RES DB 5 DUP('0'),'$'

        .CODE

MAIN PROC FAR
        MOV AX,@DATA
        MOV DX,AX

        LEA SI,FNUM
        LEA DI,SNUM
        ADD SI,4
        ADD DI,4
        LEA BX,RES
        ADD BX,5
        MOV CX,04
        MOV AH,00

   A10: MOV AL,[SI]
        ADD AL,[DI]
        ADD AL,AH
        AAA
        ADD AL,30H
        MOV [BX],AL
        DEC SI
        DEC DI
        DEC BX
        LOOP A10

        ADD AH,30H
        MOV [BX],AH

        MOV AH,09H
        MOV DX,BX
        INT 21H

        MOV AH,4CH
        INT 21H

MAIN ENDP
        END MAIN
