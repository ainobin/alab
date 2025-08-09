.model small 
.stack 100h 
.data 
  seq db 'NOBIN$'   ; sequence of characters, $ ends string 
 
.code 
main: 
  mov ax, @data 
  mov ds, ax 
 
  mov dl, seq       ; load first character into DL 
  mov ah, 02h         ; DOS function to print character 
  int 21h 
 
  mov ah, 4ch       ; exit 
  int 21h 
end main