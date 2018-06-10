section	.text
global	memcpy
memcpy:
	push	ebp
	mov	ebp, esp

	mov	edi, [ebp + 8]
	mov	ecx, [ebp + 16]
	test	ecx, ecx
	jz	.end
	mov	esi, [ebp + 16]
	std
	rep
	movsb
.end:
	mov	eax, edi
	pop	ebp
	ret
