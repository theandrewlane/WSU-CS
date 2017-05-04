TITLE CS2810 Assembler Template

; Student Name: Andrew Lane
; Assignment Due Date: 11-29-15

INCLUDE Irvine32.inc
.data
vSemester BYTE "CS2810 Fall Semester 2015",0
vAssembler BYTE "Assembler Assignment #3",0
vName BYTE "Andrew Lane", 0
vHexPrompt BYTE "Please enter an MP3 frame header in hex format: ",0
;--------- 
vMpeg25 BYTE "MPEG V2.5",0 
vMpeg20 BYTE "MPEG V2.0",0 
vMpeg10 BYTE "MPEG V1.0",0
vMpegRE BYTE "MPEG Reserved",0 
;--------- 
vLayer_RE BYTE "Layer Reserved",0
vLayer_III BYTE "Layer III",0
vLayer_II BYTE "Layer II",0
vLayer_I BYTE "Layer I",0
;--------- 
vSR_00 BYTE "Sample Rate - 44100 Hz ",0
vSR_01 BYTE "Sample Rate - 22050 Hz ",0
vSR_02 BYTE "Sample Rate - 11025 Hz ",0
vSR_10 BYTE "Sample Rate - 48000 Hz ",0
vSR_11 BYTE "Sample Rate - 24000 Hz ",0
vSR_12 BYTE "Sample Rate - 12000 Hz ",0
vSR_20 BYTE "Sample Rate - 32000 Hz ",0
vSR_21 BYTE "Sample Rate - 16000 Hz ",0
vSR_22 BYTE "Sample Rate - 8000 Hz ",0
vSR_30 BYTE "Sample Rate - Reserved ",0


.code
main PROC
call clrscr
call DispSemester
call DispAssignment
call DispName
call DispPrompt
call ReadMP3Header
call DispVersion
call DispLayer
call DispSamplingRate

DispSemester:
mov dh, 12
mov dl, 12
call Gotoxy 
mov edx, offset vSemester
call WriteString

ret

DispAssignment:	
mov dh, 13 
mov dl, 12
call Gotoxy
mov edx, offset vAssembler
call WriteString
ret

DispName:
mov dh, 14
mov dl, 12 
call Gotoxy 
mov edx, offset vName
call WriteString
ret

DispPrompt:
mov dh, 15
mov dl, 12
call Gotoxy
mov edx, offset vHexPrompt
call WriteString
mov dh, 16
mov dl, 12
call Gotoxy
ret

ReadMP3Header:
call ReadHex
mov ebx, eax
ret

DispVersion:
mov dh, 17 
mov dl, 12
call Gotoxy 
mov eax, ebx
and eax, 00000000000110000000000000000000b
shr eax, 19

cmp eax, 00b
jz dMpeg25

cmp eax, 01b
jz dMpegRE

cmp eax, 10b
jz dMpeg20

mov edx, offset vMpeg10
jmp DisplayString

dMpeg25:
mov edx, offset vMpeg25
jmp DisplayString

dMpegRE:
mov edx, offset VMpegRE
jmp DisplayString

dMpeg20:
mov edx, offset VMpeg20
jmp DisplayString

DisplayString:
mov ecx, eax
call WriteString

ret

DispLayer:
mov dh, 18 
mov dl, 12 
call Gotoxy

mov eax, ebx 
and eax, 00000000000001100000000000000000b
shr eax, 17

cmp eax, 00b
jz dLayer_RE

cmp eax, 01b
jz dLayer_III

cmp eax, 10b
jz dLayer_II

mov edx, offset vLayer_I
jmp DisplayDesc

dLayer_RE:
mov edx, offset vLayer_RE
jmp DisplayDesc

dLayer_III:
mov edx, offset vLayer_III
jmp DisplayDesc

dLayer_II:
mov edx, offset vLayer_II
jmp DisplayDesc

DisplayDesc:
call WriteString

ret

DispSamplingRate:

mov dh, 19
mov dl, 12
call gotoxy

mov eax, ebx
mov ecx, ebx
and eax, 00000000000000000000110000000000b
and ebx, 00000000000110000000000000000000b
shr ebx, 19
shr eax, 10

;The fix here avoid back to back cmp, which prevents register overwriting issues
cmp eax, 00b
jz dVSampleRate0

cmp eax, 01b
jz dVSampleRate1

cmp eax, 10b
jz dVSampleRate2

; jump if the above comparisons fail
jz dVSampleRate30

dVSampleRate0:
	cmp ebx, 11b
	jz dVSampleRate00

	cmp ebx, 10b
	jz dVSampleRate01

	cmp ebx, 00b
	jz dVSampleRate02

	cmp ebx, 01b
	jz dVSampleRate30

dVSampleRate1:
	cmp ebx, 11b
	jz dVSampleRate10

	cmp ebx, 10b
	jz dVSampleRate11

	cmp ebx, 00b
	jz dVSampleRate12

	cmp ebx, 01b
	jz dVSampleRate30

dVSampleRate2:
	cmp ebx, 11b
	jz dVSampleRate20

	cmp ebx, 10b
	jz dVSampleRate21

	cmp ebx, 00b
	jz dVSampleRate22

	cmp ebx, 01b
	jz dVSampleRate30

dVSampleRate00:
	mov edx, offset vSR_00
	JMP DispSamplingString

dVSampleRate01:
	mov edx, offset vSR_01
	jmp DispSamplingString

dVSampleRate02:
	mov edx, offset vSR_02
	jmp DispSamplingString

dVSampleRate10:
	mov edx, offset vSR_10
	jmp DispSamplingString

dVSampleRate11:
	mov edx, offset vSR_11
	jmp DispSamplingString

dVSampleRate12:
	mov edx, offset vSR_12
	jmp DispSamplingString

dVSampleRate20:
	mov edx, offset vSR_20
	jmp DispSamplingString

dVSampleRate21:
	mov edx, offset vSR_21
	jmp DispSamplingString

dVSampleRate22:
	mov edx, offset vSR_22
	jmp DispSamplingString

dVSampleRate30:
	mov edx, offset vSR_30
	jmp DispSamplingString

DispSamplingString:
	call WriteString

mov dh, 21
mov dl, 12
call gotoxy

xor ecx, ecx
call ReadChar
exit

main ENDP

END main