.MODEL SMALL
.STACK 100H
.DATA
    num1 DW 123
    num2 DW 456 ; bigger
    buffer DB 5 DUP('$')    ; For printing numbers
.CODE
MAIN:
    MOV AX, @DATA
    MOV DS, AX

    ; --- Print "Sum: " ---
    MOV AX, num1
    ADD AX, num2
    CALL PrintNum

    ; Newline
    MOV DL, 10
    MOV AH, 02H
    INT 21H
    MOV DL, 13
    INT 21H

    ; --- Print "Diff: " ---
    MOV AX, num2
    SUB AX, num1
    CALL PrintNum

    ; Exit
    MOV AH, 4CH
    INT 21H

; === Procedure to print number in AX ===
PrintNum PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV CX, 0
    MOV BX, 10
    LEA SI, buffer+4
NEXT:
    XOR DX, DX
    DIV BX
    ADD DL, '0'
    MOV [SI], DL
    DEC SI
    INC CX
    CMP AX, 0
    JNZ NEXT
    INC SI
PRINT:
    MOV DL, [SI]
    MOV AH, 02H
    INT 21H
    INC SI
    LOOP PRINT
    POP DX
    POP CX
    POP BX
    POP AX
    RET
PrintNum ENDP

END MAIN
