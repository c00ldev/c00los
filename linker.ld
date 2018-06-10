ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

		.data BLOCK(4K) : ALIGN(4K)
		{
			start_ctors = .;
			*(.ctor*)
			end_ctors = .;
			start_dtors = .;
			*(.dtor*)
			end_dtors = .;
			*(.data)
		}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

}
