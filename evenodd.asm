.model small
.stack 100h
.data
    prompt db "number: $"
    even_msg db "Even.$"
    odd_msg  db "Odd.$"

.code
main proc
    mov ax, @data
    mov ds, ax

    mov dx, offset prompt
    mov ah, 09h      
    int 21h

    mov ah, 01h       
    int 21h          
    
    sub al, 30h  

    test al, 1        
    jz  EVEN          

ODD:
    mov dx, offset odd_msg
    mov ah, 09h
    int 21h
    jmp EXIT

EVEN:
    mov dx, offset even_msg
    mov ah, 09h
    int 21h

EXIT:
    mov ah, 4ch
    int 21h
main endp
end main
