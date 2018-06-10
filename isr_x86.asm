extern	handle_interrupts
global	isr_ignore

isr_ignore:
	iret

%macro	SAVE_REGS	0
	pushad
	push ds
	push es
	push fs
	push gs
	push ebx
	mov bx,0x10
	mov ds,bx
	pop ebx
%endmacro

%macro RESTORE_REGS	0
	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
%endmacro

%macro	IRQ	1

global	irq%1
irq%1:
	SAVE_REGS
	push	esp
	push	(0x20 + %1)
	call	handle_interrupts
	mov	esp, eax
	RESTORE_REGS
	iret

%endmacro

IRQ	0
IRQ	1
