.model small
.stack 100h
.data
buffer db 20,?,20 dup('$')
msg db 13,10,'Reversed: $'
.code
main:
    mov ax, @data
    mov ds, ax

    lea dx, buffer
    mov ah, 0Ah
    int 21h

    lea dx, msg
    mov ah, 09h
    int 21h

    mov si, offset buffer + 2
    mov cl, buffer+1
    mov ch, 0
    add si, cx
    dec si

print_loop:
    mov dl, [si]
    mov ah, 02h
    int 21h
    dec si
    loop print_loop

    mov ah, 4ch
    int 21h
end main
