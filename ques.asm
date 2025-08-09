.model small 
.stack 100h 
.code 
main: 
    mov ah, 2        ; DOS print character function 
    mov dl, '?'      ; character to display 
    int 21h          ; call DOS interrupt 
 
    mov ah, 4ch      ; exit program 
    int 21h 
end main