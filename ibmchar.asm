.model small 
.stack 100h 
 
.data 
; (You can define data here if needed, or leave empty) 
 
.code 
main: 
    mov ax, @data 
    mov ds, ax 
 
    mov cx, 256     ; total 256 characters 
    mov bl, 0       ; starting ASCII code 
 
print_loop: 
    mov dl, bl      ; put character in DL 
    mov ah, 2 
    int 21h         ; print character 
 
    inc bl 
    loop print_loop 
 
    mov ah, 4Ch 
    int 21h 
end main