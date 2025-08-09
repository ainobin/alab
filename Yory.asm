.model small 
.stack 100h 
.code 
main: 
    mov ah, 1       ; read char 
    int 21h 
    cmp al, 'Y' 
    je print 
    cmp al, 'y' 
    jne exit 
print: 
    mov dl, al 
    mov ah, 2 
    int 21h 
exit: 
    mov ah, 4Ch 
int 21h 
end main