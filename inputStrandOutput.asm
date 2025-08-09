.model small
.stack 100h
.data
    buffer db 50       ; maximum characters user can type
    buffer_len db ?    ; actual length of input
    buffer_str db 50 dup('$') ; space for string 
    prompt db "Enter a string: $"
    newline db 0Dh, 0Ah, "$"


.code
main:
    mov ax, @data
    mov ds, ax

    ; Prompt the user
    mov ah, 09h
    mov dx, offset prompt
    int 21h

    ; Read string from user
    mov ah, 0Ah         ; DOS buffered input
    mov dx, offset buffer
    int 21h

    ; Display newline
    mov ah, 09h
    mov dx, offset newline
    int 21h

    ; Print the entered string
    mov ah, 09h
    mov dx, offset buffer_str
    int 21h

    ; Exit
    mov ah, 4Ch
    int 21h


end main
