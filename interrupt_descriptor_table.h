#pragma once

#include <stdint.h>
#include <stddef.h>

class interrupt_descriptor_table
{
public:
	class entry
	{
		uint16_t offset_l;
		uint16_t selector;
		uint8_t zero;
		union
		{
			uint8_t type_attr;
			struct
			{
				uint8_t type : 4;
				bool S : 1;
				uint8_t DPL : 2;
				bool Pr : 1;
			} __attribute__ ((packed));
		} __attribute__ ((packed));
		uint16_t offset_h;
	public:
		entry();
		union offset_t
		{
			uint32_t full;
			struct
			{
				uint16_t low;
				uint16_t high;
			} __attribute__ ((packed));
		public:
			offset_t(void (*offset)());
		} __attribute__ ((packed));
		entry(uint16_t selector, offset_t offset, uint8_t type_attr);
		entry & operator=(const entry & rhs);
	} __attribute__ ((packed));
private:
	entry table[256];
public:
	interrupt_descriptor_table();
	~interrupt_descriptor_table() = default;
	entry & operator[](uint8_t offset);
	const entry & operator[](uint8_t offset) const;
private:
	static const interrupt_descriptor_table * _idt;
public:
	static void use(const interrupt_descriptor_table & idt);
	static void enable_interrupts();
	static void disable_interrupts();
} __attribute__((packed));

extern "C"
{

//void set_idt(const interrupt_descriptor_table & idt, size_t size);
//void activate_idt();

}
