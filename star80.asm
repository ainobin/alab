 .model small 
.stack 100h 
.code 
main: 
    mov cx, 80       ; loop counter = 80 stars 
    mov ah, 02h        ; DOS print character function 
    mov dl, '*'      ; character to print 
 
print_loop: 
    int 21h          ; print '*' 
    loop print_loop  ; CX = CX - 1, repeat until CX = 0 
 
    mov ah, 4ch      ; exit program 
    int 21h 
end main