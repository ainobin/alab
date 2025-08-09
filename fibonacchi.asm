.MODEL SMALL
.STACK 100H
.DATA
    MSG     DB      'FIBONACCI SERIES : ', '$'
    COMMA   DB      ', ','$'
    LIMIT   DW      24
    A       DW      0
    B       DW      1
    VAR     DW      ?
    OUTSTR  DB      10 DUP('$')

.CODE
PROC MAIN
; LOAD DATA
    MOV AX, @DATA
    MOV DS, AX

; PROMPT
    LEA DX, MSG
    MOV AH, 09H
    INT 21H
    
; PRINTING FIBONACCI SERIES
; SETUP
    MOV AX, A
    MOV BX, B
    MOV CX, LIMIT
; ACTUAL LOOP
LOOPBACK:
    MOV VAR, AX
    CALL CONVERT_VAR
    CALL PRINT_OUTSTR
    CMP CX, 0
    JE END
    CALL PRINT_COMMA
    
    ADD AX, BX
    XOR AX, BX
    XOR BX, AX
    XOR AX, BX
    LOOP LOOPBACK

END:
; EXIT
    MOV AH, 4CH
    INT 21H
MAIN ENDP

PRINT_COMMA:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX

    MOV AH, 09H
    LEA DX, COMMA
    INT 21H
    
    POP DX
    POP CX
    POP BX
    POP AX
    RET

PRINT_OUTSTR:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX

    MOV AH, 09H
    LEA DX, OUTSTR
    INT 21H
    
    POP DX
    POP CX
    POP BX
    POP AX
    RET

CONVERT_VAR:
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    
    MOV AX, VAR
    MOV DI, OFFSET OUTSTR
    XOR CX,CX
    
    CMP AX, 0
    JE ZERO
LOOPING:
    MOV BX, 10
    XOR DX,DX
    DIV BX
    ADD DL, '0'
    PUSH DX
    INC CX
    CMP AX, 0
    JNZ LOOPING

POPING:
    POP DX
    MOV [DI], DL
    INC DI
    LOOP POPING
    
    JMP STREND    

ZERO:
    MOV [DI], '0'
    INC DI

STREND:
    MOV [DI], '$'
    
; RETURN TIME    
    POP DX
    POP CX
    POP BX
    POP AX
    RET

END MAIN