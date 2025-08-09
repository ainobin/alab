ORG 100h

MOV CX, 5      ; sum 1 to 5
MOV AX, 0
MOV BX, 1

SUM_LOOP:
    ADD AX, BX
    INC BX
    LOOP SUM_LOOP

MOV BX, 10
MOV CX, 0

CONVERT_LOOP:
    MOV DX, 0
    DIV BX
    PUSH DX
    INC CX
    CMP AX, 0
    JNE CONVERT_LOOP

DISPLAY_LOOP:
    POP DX
    ADD DL, 30h
    MOV AH, 02h
    INT 21h
    LOOP DISPLAY_LOOP

MOV AH, 4Ch
INT 21h

END
