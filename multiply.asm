.model small
.stack 100h
.data
    num1 dw 100
    num2 dw 20
    result dw ?

.code
main proc
    mov ax, @data
    mov ds, ax

    ; --- Multiply ---
    mov ax, num1
    mov bx, num2
    mul bx        ; AX = num1 * num2
    mov result, ax

    ; --- Print result ---
    mov ax, result
    call PrintNumber

    ; Exit
    mov ah, 4Ch
    int 21h
main endp

; --------------------------------
; Prints number in AX
; --------------------------------
PrintNumber proc
    push ax
    push bx
    push cx
    push dx
    mov cx, 0
    mov bx, 10
NextDigit:
    xor dx, dx
    div bx
    push dx
    inc cx
    cmp ax, 0
    jne NextDigit
PrintLoop:
    pop dx
    add dl, 30h
    mov ah, 2
    int 21h
    loop PrintLoop
    pop dx
    pop cx
    pop bx
    pop ax
    ret
PrintNumber endp
end main
