.model small
.stack 100h
.data
.code
main:
    mov ax, @data
    mov ds, ax
    
    mov ah, 01h
    int 21h
    
    cmp al, 'a'
    jb check_upper
    cmp al, 'z'
    ja check_upper
    sub al, 32 
    
    jmp print_it
    
    
    
check_upper:
    cmp al, 'A'
    jb end_prog
    cmp al, 'Z'
    ja end_prog
    add al, 32      ;upper to lower     

print_it:
    mov dl, al
    mov ah, 02h
    int 21h
    
    
    
end_prog:
    mov ah, 4ch
    int 21h
end main