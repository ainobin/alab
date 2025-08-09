.model small
.stack 100h
.data
    num1 db 45
    num2 db 87
    num3 db 62
    msg  db 'Largest: $'

.code
main:
    mov ax, @data
    mov ds, ax

    ; Find largest among num1, num2, num3
    mov al, num1
    mov bl, num2
    cmp al, bl
    jge next1
    mov al, bl         ; al = max(num1, num2)

next1:
    mov bl, num3
    cmp al, bl
    jge done
    mov al, bl         ; al = max(al, num3)

done:
    ; Print message
    lea dx, msg
    mov ah, 09h
    int 21h

    ; Print number in AL (two-digit)
    mov bl, 10         ; divisor
    mov ah, 0
    div bl             ; AL / 10 -> AL=quotient, AH=remainder

    add al, 30h        ; tens digit to ASCII
    mov dl, al
    mov ah, 02h
    int 21h

    mov al, ah         ; remainder
    add al, 30h        ; ones digit to ASCII
    mov dl, al
    mov ah, 02h
    int 21h

    ; Exit program
    mov ah, 4Ch
    int 21h
end main
