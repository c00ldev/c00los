extern	start_ctors
extern	end_ctors
extern	start_dtors
extern	end_dtors

%macro	callrange	2
	mov	ebx, %1
	jmp	%%test
%%body:
	call	[ebx]
	add	ebx, 4
%%test:
	cmp	ebx, %2
	jb	%%body
%endmacro

MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
align	4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align	16
stack_bottom:
resb	16384 ; 16 KiB
stack_top:

section	.text
global	_start:function (_start.end - _start)
_start:

	push	ebx

	mov esp, stack_top

	callrange	start_ctors, end_ctors

	cli
	extern	main
	call	main

	callrange	start_dtors, end_dtors

	cli
.hang:	hlt
	jmp .hang

.end:
