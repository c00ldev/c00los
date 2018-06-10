#pragma once

#include <stdint.h>
#include <stddef.h>

class segment_descriptor_table
{
public:
	class entry
	{
		uint16_t limit_l;
		uint16_t base_l;
		uint8_t base_m;
		union
		{
			uint8_t access_byte;
			struct
			{
				bool Ac : 1;
				bool RW : 1;
				bool DC : 1;
				bool Ex : 1;
				bool S : 1;
				uint8_t Privl : 2;
				bool Pr : 1;
			} __attribute__ ((packed));
		} __attribute__ ((packed));
		uint8_t limit_h : 4;
		bool Av : 1;
		bool unused1 : 1;
		bool Sz : 1;
		bool Gr : 1;
		uint8_t base_h;
	public:
		entry();
		union base_t
		{
			uint32_t full;
			struct
			{
				uint16_t low;
				uint8_t middle;
				uint8_t high;
			} __attribute__ ((packed));
		public:
			base_t(uint32_t base);
		} __attribute__ ((packed));
		union limit_t
		{
			uint32_t full;
			struct
			{
				uint16_t low;
				uint8_t high : 4;
			} __attribute__ ((packed));
		public:
			limit_t(uint32_t limit);
		} __attribute__ ((packed));
		entry(base_t base, limit_t limit, uint8_t access);
		entry & operator=(const entry & rhs);
	} __attribute__ ((packed));
private:
	entry table[4];
public:
	segment_descriptor_table();
	~segment_descriptor_table() = default;
	entry & operator[](uint16_t offset);
	const entry & operator[](uint16_t offset) const;
} __attribute__((packed));

using global_descriptor_table = segment_descriptor_table;
using local_descriptor_table = segment_descriptor_table;

extern "C"
{

	void set_gdt(const global_descriptor_table & gdt, size_t size);
	void seg_reload();

}
