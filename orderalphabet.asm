.model small 
.stack 100h 
.code 
main: 
    mov ah, 1        ; DOS read character 
    int 21h          ; read first char ? AL 
    mov bl, al       ; store in BL 
 
    mov ah, 1 
    int 21h          ; read second char ? AL 
    mov bh, al       ; store in BH 
 
    cmp bl, bh       ; compare first with second 
    jbe print_order  ; if BL <= BH, already in order 
 
    ; swap if needed 
    xchg bl, bh 
 
print_order: 
    mov ah, 2 
    mov dl, bl       ; print first letter 
    int 21h 
 
    mov dl, bh       ; print second letter 
    int 21h 
 
    mov ah, 4Ch      ; exit 
    int 21h 
end main