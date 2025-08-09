.model small 
.stack 100h 
.code 
main: 
    mov ah, 1        ; DOS function: read character from keyboard 
read_loop: 
    int 21h          ; wait for key press ? result in AL 
    cmp al, ' '      ; is it a space? 
    je end_prog      ; if yes, jump to end 
    jmp read_loop    ; else, read next character 
 
end_prog: 
    mov ah, 4ch      ; exit program 
    int 21h 
end main