TITLE CS2650 Assembler Assignment #4 Template
; Student Name: Andrew Lane
; Assignment Due Date: Dec 6th, 2015
INCLUDE Irvine32.inc
.data
;--------- Enter Data Here
vSemester BYTE "CS2810 Fall Semester 2015",0
vAssembler BYTE "Assembler Assignment #4",0
vName BYTE "Andrew Lane", 0
vUserPrompt BYTE "Please Enter a FAT16 file date:",0
        vArray			BYTE "January ",0,"   "
                        BYTE "February ",0,"  "
                        BYTE "March ",0,"     "
                        BYTE "April ",0,"     "
                        BYTE "May ",0,"       "
                        BYTE "June ",0,"      "
                        BYTE "July ",0,"      "
                        BYTE "August ",0,"    "
                        BYTE "September ",0," "
                        BYTE "October ",0,"   "
                        BYTE "November ",0,"  "
                        BYTE "December ",0,"  "
vTh BYTE "th, ",0
vSt BYTE "st, ",0
vNd BYTE "nd, ",0
vRd BYTE "rd, ",0

vDay BYTE "--",0
vYear BYTE "----",0
.code
main PROC
;--------- Enter Code Below Here
	call clrscr
	call DispSemester
	call DispAssignment
	call DispName
	call DispPrompt
	call ReadInput
	call DispMonth
	call DispDay
	call DispYear

DispSemester:
	mov dh, 4
	mov dl, 33
	call Gotoxy 
	mov edx, offset vSemester
	call WriteString
	ret

DispAssignment:	
	mov dh, 5 
	mov dl, 33
	call Gotoxy
	mov edx, offset vAssembler
	call WriteString
	ret

DispName:
	mov dh, 6
	mov dl, 33 
	call Gotoxy 
	mov edx, offset vName
	call WriteString
	ret

DispPrompt:
	mov dh, 8
	mov dl, 33
	call Gotoxy
	mov edx, offset vUserPrompt
	call WriteString
	mov dh, 9
	mov dl, 33
	call Gotoxy
	ret

ReadInput:
    call ReadHex
    ror ax, 8
    mov ebx, eax
	mov edi, ebx
	mov dh, 10
	mov dl, 33
	call Gotoxy
	ret

DispMonth:
    mov eax, edi
	and ax, 0000000111100000b
    shr ax, 5 
	sub eax, 1
    
	mov edx, offset [vArray]
    mov bl, 12
    mul bl
	   
    add edx, eax
    call WriteString
	ret

DispDay:
    mov eax, edi
    and ax, 0000000000011111b
    mov ch, 10
    div ch
    add ax, 3030h
    mov word ptr [vDay], ax
   
    mov edx, OFFSET vDay
    call WriteString
      
    cmp eax, 0
	jz Quit ;------ Not here!

    cmp eax, 1
    jz dSt

    cmp eax, 2
    jz dNd

    cmp eax, 3
	  jz dRd


    cmp eax, 21
    jz dSt

    cmp eax, 22
    jz dNd

    cmp eax, 23
    jz dRd

    cmp eax, 31
    jz dSt 

    mov edx, offset [vTh]
    jmp Display

    dSt:
        mov edx, offset [vSt]
        jmp Display

    dNd:
        mov edx, offset [vNd]
        jmp Display

    dRd:
        mov edx, offset [vRd]
        jmp Display

    Display:
        call WriteString

	ret
		
DispYear:
    mov eax, edi
	and ax, 1111111000000000b
	shr ax, 9
	add ax, 1980
	
	cmp eax, 0
	jz Quit ;----- Not here!

	xor dx, dx
	mov bx, 1000
	div bx
	add al, 30h
	
	mov byte ptr [vYear], al
	mov ax, dx
	xor dx, dx
	mov bx, 100
	div bx
	add al, 30h
	mov byte ptr [vYear+1], al
	mov ax, dx
	xor dx, dx
	mov bl, 10
	div bl
	add ax, 3030h
	mov word ptr [vYear+2], ax
	mov edx, offset [vYear]
	call WriteString
    
	xor ecx, ecx
    call ReadChar

Quit:
    exit

main ENDP
END main
