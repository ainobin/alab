.model small
.stack 100h

.data
    msg db 'hello world','$'

.code
main:
    mov ax, @data
    mov ds, ax
    
    lea dx, msg
    mov ah, 09h
    int 21h
       
end main 