global	read8
read8:
	mov	dx, [esp + 4]
	in	al, dx

	ret

global	write8
write8:
	mov	dx, [esp + 4]
	mov	al, [esp + 8]
	out	dx, al

	ret

global	write8slow
write8slow:
	mov	dx, [esp + 4]
	mov	al, [esp + 8]
	out	dx, al
	jmp	.next
.next:	jmp	.next2
.next2:

	ret
