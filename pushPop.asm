.model small
.stack 100h
.data
msg db 'Value after pop: $'
.code
main:
    mov ax, @data
    mov ds, ax

    mov ax, 456
    push ax
    xor ax, ax
    pop ax

    lea dx, msg
    mov ah, 09h
    int 21h

    call PrintNum

    mov ah, 4ch
    int 21h

PrintNum proc
    push ax
    push bx
    push cx
    push dx

    xor cx, cx
    mov bx, 10
print_loop:
    xor dx, dx
    div bx
    push dx
    inc cx
    test ax, ax
    jnz print_loop

print_digits:
    pop dx
    add dl, '0'
    mov ah, 02h
    int 21h
    loop print_digits

    pop dx
    pop cx
    pop bx
    pop ax
    ret
PrintNum endp

