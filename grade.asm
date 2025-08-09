.model small
.stack 100h
.data
    marks db 60
    msgAplus db 'Grade: A+$'
    msgA db 'Grade: A$'
    msgB db 'Grade: B$'
    msgC db 'Grade: C$'
.code
main:
    mov ax, @data
    mov ds, ax

    mov al, marks
    cmp al, 80
    jae ap
    cmp al, 70
    jae a
    cmp al, 60
    jae b
    jmp c

ap:
    lea dx, msgAplus
    jmp print
a:
    lea dx, msgA
    jmp print
b:
    lea dx, msgB
    jmp print
c:
    lea dx, msgC

print:
    mov ah, 09h
    int 21h

    mov ah, 4ch
    int 21h
end main
