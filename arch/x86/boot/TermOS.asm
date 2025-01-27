[BITS 16]
[ORG 0x7c00]

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
; Зануляем регистры

jmp ReadDisk


GDT_Start:
	null_descriptor:
		dd 0
		dd 0
	code_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 10011010b
		db 11001111b
		db 0
	data_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 10010010b
		db 11001111b
		db 0
GDT_End:
GDT_Descriptor:
	dw GDT_End - GDT_Start - 1
	dd GDT_Start

CODESEG equ code_descriptor - GDT_Start
DATASEG equ data_descriptor - GDT_Start



ReadDisk:
	mov ah, 0x02
	mov al, 100 ; Декрементировать и обратно выполнять
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	mov dl, 0x80
	mov bx, 0x7e00


.ReadLoop:
	int 0x13
	jc .ReadDec

	mov ax, 0x0003
	int 0x10

	cli

	in al, 0x92
	or al, 2
	out 0x92, al
	
	lgdt [GDT_Descriptor]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp CODESEG:PM_OS

.ReadDec:
	cmp al, 0x00
	je .ReadError
	dec al
	jmp .ReadLoop
.ReadError:
	mov ah, 0x0e
	mov al, '['
	int 0x10
	mov al, 'p'
	int 0x10
	mov al, 'a'
	int 0x10
	mov al, 'n'
	int 0x10
	mov al, 'i'
	int 0x10
	mov al, 'c'
	int 0x10
	mov al, ']'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'R'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, 'a'
	int 0x10
	mov al, 'd'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, 'r'
	int 0x10
	int 0x10
	mov al, 'o'
	int 0x10
	mov al, 'r'
	int 0x10
	mov al, '!'
	int 0x10
	jmp $

	

times 510 - ($ - $$) db 0
dw 0xaa55

PM_OS:
[BITS 32]
	mov eax, cr0
	and eax, 01111111111111111111111111111111b
	mov cr0, eax

	mov edi, 0x1000
	mov cr3, edi
	xor eax, eax
	mov ecx, 4096
	rep stosd
	mov edi, cr3

	mov DWORD [edi], 0x2003
	add edi, 0x1000
	mov DWORD [edi], 0x3003
	add edi, 0x1000
	mov DWORD [edi], 0x4003
	add edi, 0x1000

	mov ebx, 0x00000003
	mov ecx, 512

.SetEntry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .SetEntry

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

[BITS 64]
	mov byte [0xb8000], 'x'
	mov byte [0xb8001], 0x07
	mov byte [0xb8002], '6'
	mov byte [0xb8003], 0x07
	mov byte [0xb8004], '4'
	mov byte [0xb8005], 0x07

	mov rax, 0xb8000
	add rax, 80*2
	
	add rax,2

	mov byte [rax], 'L'
	mov byte [rax+1], 0x07
	mov byte [rax+2], 'o'
	mov byte [rax+3], 0x07
	mov byte [rax+4], 'n'
	mov byte [rax+5], 0x07
	mov byte [rax+6], 'g'
	mov byte [rax+7], 0x07

	mov rcx, kernel64
	call Execute

	mov rax, 0xb8000
	add rax, (80*2)*3
	add rax, 2

	mov byte [rax], 'R'
	mov byte [rax+1], 0x07
	mov byte [rax+2], 'E'
	mov byte [rax+3], 0x07
	mov byte [rax+4], 'T'
	mov byte [rax+5], 0x07
	
	
	jmp $

%include "./lib/ELF.asm"

kernel64: