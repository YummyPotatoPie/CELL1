NULL equ 0
STD_OUTPUT_HANDLE equ -11

extern GetStdhandle
extern WriteFile
extern ExitProcess

section .data
	cell db 0

section .bss
	StdHandle resd 1
	Written resd 1

section .text
global Start
mod:
	cmp ebx, 0
	jl lower
	ret
lower:
	add ebx, 128
	mov [cell], ebx
	ret

Start
	push STD_OUTPUT_HANDLE
	call GetStdHandle
	mov dword [StdHandle], eax

	push NULL
	call ExitProcess
