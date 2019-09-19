PAGE 80,132
TITLE Add Two Numbers
;---------------------------------------------------------------------------
.MODEL SMALL
.STACK 64
.DATA
NUM1 DW 3731H , '$'
;---------------------------------------------------------------------------
.CODE
MAIN PROC FAR

MOV AX,@DATA
MOV DS,AX



MOV AH,09H
LEA DX,NUM1
INT 21H
      
MOV AX,4C00H
INT 21H
MAIN ENDP
END MAIN
