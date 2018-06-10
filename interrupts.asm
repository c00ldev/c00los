global	nmi_enable
global	nmi_disable

global	irq_enable
global	irq_disable

nmi_enable:
	in	al, 0x70
	and	al, 0x7F
	out	0x70, al
	ret

nmi_disable:
	in	al, 0x70
	or	al, 0x80
	out	0x70, al
	ret

irq_enable:
	sti
	ret

irq_disable:
	cli
	ret
