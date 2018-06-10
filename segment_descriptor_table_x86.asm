%include	"interrupts.inc"

section	.data
dt_inf:	DW	0
	DD	0

section	.text
global	set_gdt
set_gdt:
	;cli
	call	nmi_disable
	mov	eax, [esp + 4]
	mov	[dt_inf + 2], eax
	mov	ax, [esp + 8]
	dec	ax
	mov	[dt_inf], ax
	lgdt	[dt_inf]
	call	nmi_enable
	;sti

	ret

global	seg_reload
seg_reload:
	;cli
	call	nmi_disable
	jmp	0x08:reload_CS
reload_CS:
	mov	ax, 0x10
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	call	nmi_enable
	;sti

	ret
