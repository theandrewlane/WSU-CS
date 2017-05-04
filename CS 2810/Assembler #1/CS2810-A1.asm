TITLE CS2650 Assembler Assignment #2 Template

; Andrew Lane:
; 11/15/15:

INCLUDE Irvine32.inc
.data
	;--------- Enter Data Here
	vClass byte "CS2810 Fall Semester 2014", 0
	vAssn byte "Assembler Assignment #1", 0
	vName byte "Andrew Bryan Lane", 0
	
.code
main PROC
	;--------- Enter Code Below Here
	call clrscr 	;--------- #1 - Clear Display
	mov dh, 2
	mov dl, 12
	call gotoxy
	mov edx, offset vClass
	call WriteString 	;--------- #2 Display String
	
	mov dh, 3
	mov dl, 12
	call gotoxy
	mov edx, offset vAssn
	call WriteString 	;--------- #3 Display String
	
	mov dh, 4
	mov dl, 12
	call gotoxy
	mov edx, offset vName
	call WriteString 	;--------- #4 Display String
	
	xor ecx, ecx 
	call readChar
	exit
main ENDP

END main