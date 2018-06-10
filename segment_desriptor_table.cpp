#include "segment_desriptor_table.h"

segment_descriptor_table::entry::base_t::base_t(uint32_t base)
	: full(base)
{
}

segment_descriptor_table::entry::limit_t::limit_t(uint32_t limit)
	: full(limit)
{
}

segment_descriptor_table::entry::entry()
	: limit_l(0x0000u)
	, base_l(0x0000u)
	, base_m(0x00u)
	, access_byte(0x00u)
	, limit_h(0x0u)
	, Av(false)
	, unused1(false)
	, Sz(false)
	, Gr(false)
	, base_h(0x00u)
{
}

segment_descriptor_table::entry::entry(base_t base, limit_t limit, uint8_t access)
	: limit_l(limit.low)
	, base_l(base.low)
	, base_m(base.middle)
	, access_byte(access)
	, limit_h(limit.high)
	, Av(true)
	, unused1(false)
	, Sz(true)
	, Gr(false)
	, base_h(base.high)
{
	if (limit.full > 0xFFFFu && (limit.full & 0xFFFu) == 0xFFFu)
	{
		limit.full >>= 12;
		limit_l = limit.low;
		limit_h = limit.high;
		Gr = true;
	}
}

segment_descriptor_table::entry & segment_descriptor_table::entry::operator=(
	const segment_descriptor_table::entry & rhs)
{
	if (&rhs == this)
		return *this;

	limit_l = rhs.limit_l;
	base_l = rhs.base_l;
	base_m = rhs.base_m;
	access_byte = rhs.access_byte;
	limit_h = rhs.limit_h;
	Av = rhs.Av;
	unused1 = rhs.unused1;
	Sz = rhs.Sz;
	Gr = rhs.Gr;
	base_h = rhs.base_h;

	return *this;
}

segment_descriptor_table::segment_descriptor_table()
	: table{}
{
}

segment_descriptor_table::entry & segment_descriptor_table::operator[](uint16_t offset)
{
	return table[offset];
}

const segment_descriptor_table::entry & segment_descriptor_table::operator[](uint16_t offset) const
{
	return table[offset];
}
