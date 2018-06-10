section .text

global	pos_cur
pos_cur:
	push	ebp
	mov	ebp, esp

	mov	ecx, [ebp + 8]

	mov	al, 0xf
	mov	dx, 0x3d4
	out	dx, al

	mov	al, cl
	mov	dx, 0x3d5
	out	dx, al

	mov	al, 0xe
	mov	dx, 0x3d4
	out	dx, al

	mov	al, ch
	mov	dx, 0x3d5
	out	dx, al

	pop	ebp

	ret
