%include	"interrupts.inc"

section	.data
dt_inf:	DW	0
	DD	0

global	set_idt
set_idt:
	call	nmi_disable
	mov	eax, [esp + 4]
	mov	[dt_inf + 2], eax
	mov	ax, [esp + 8]
	dec	ax
	mov	[dt_inf], ax
	lidt	[dt_inf]
	call	nmi_enable

	ret

;global	activate_idt
;activate_idt:
;	mov	al, 0x11
;	out	0x20, al
;	out	0xA0, al
;
;	mov	al, 0x20
;	out	0x21, al
;	mov	al, 0x28
;	out	0xA1, al
;
;	mov	al, 0x04
;	out	0x21, al
;	mov	al, 0x02
;	out	0xA1, al
;
;	mov	al, 0x01
;	out	0x21, al
;	out	0xA1, al
;
;	xor	al, al
;	out	0x21, al
;       out	0xA1, al
;
;	ret
