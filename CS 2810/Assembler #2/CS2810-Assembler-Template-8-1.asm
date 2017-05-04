TITLE CS2810 Assembler Assignment Template
 
; Student Name: Andrew Lane
; Assignment Due Date: 11/22/15
 
INCLUDE Irvine32.inc
.data       
        vSemester BYTE "CS2810 Fall Semester 2015", 0
        vAssignment2 BYTE "Assembler Assignment #2" ,0
        vMyName BYTE "Andrew Bryan Lane", 0
        vFAT16Prompt BYTE "Please enter FAT16 file time in hex format below: " ,0
        vTimeFormat BYTE "--:--:--" ,0
.code
main PROC
 ;------------------------- #1&2

        call Clrscr
        mov dh, 7
        mov dl, 0
        call Gotoxy
        mov edx, OFFSET vSemester
        call WriteString

;------------------------- #3
        mov dh, 8
        mov dl, 0
        call Gotoxy
        mov edx, OFFSET vAssignment2
        call WriteString

;------------------------- #4
 
        mov dh, 9
        mov dl, 0
        call Gotoxy
        mov edx, OFFSET vMyName
        call WriteString
 
;------------------------- #5
 
        mov dh, 10
        mov dl, 0
        call Gotoxy
        mov edx, OFFSET vFAT16Prompt
        call WriteString
		 
        mov dh, 11
        mov dl, 0
        call Gotoxy

;------------------------- #6
 ;-------- Hours

        call ReadHex
        ror ax, 8
        mov ecx, eax
        and ax, 1111100000000000b
		
        shr ax, 11
        mov bh, 10
        div bh
        add ax, 3030h
		
;-------- Minutes - Now using the correct AND gate...

		mov word ptr [vTimeFormat+0], ax
        mov eax, ecx
        and ax, 0000011111100000b
        shr ax, 5
        mov bh, 10
        div bh
        add ax, 3030h

;-------- Seconds

	    mov word ptr [vTimeFormat+3], ax
		mov eax, ecx
        and ax, 0000000000011111b
		shl ax, 1
        mov bh, 10
        div bh
        add ax, 3030h
        mov word ptr [vTimeFormat+6], ax

;------------------------- #7

        mov edx, offset vTimeFormat
        call Writestring
        xor ecx, ecx
        call ReadString
        exit

main ENDP
 
END main