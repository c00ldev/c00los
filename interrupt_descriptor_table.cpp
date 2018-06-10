#include "interrupt_descriptor_table.h"

#include "isr.h"
#include "port.h"
#include "interrupts.h"

extern "C"
{

	void set_idt(const interrupt_descriptor_table & idt, size_t size);

}

interrupt_descriptor_table::entry::offset_t::offset_t(void (*offset)())
	: full((uint32_t)offset)
{
}

interrupt_descriptor_table::entry::entry()
	: entry(0x08, isr_ignore, 0x8E)
{
}

interrupt_descriptor_table::entry::entry(uint16_t selector, offset_t offset, uint8_t type_attr)
	: offset_l(offset.low)
	, selector(selector)
	, zero(0x00u)
	, type_attr(type_attr)
	, offset_h(offset.high)
{
}

interrupt_descriptor_table::entry & interrupt_descriptor_table::entry::operator=(
	const interrupt_descriptor_table::entry & rhs)
{
	if (&rhs == this)
		return *this;

	offset_l = rhs.offset_l;
	selector = rhs.selector;
	zero = rhs.zero;
	type_attr = rhs.type_attr;
	offset_h = rhs.offset_h;

	return *this;
}

const interrupt_descriptor_table * interrupt_descriptor_table::_idt = nullptr;

interrupt_descriptor_table::interrupt_descriptor_table()
	: table{}
{
}

interrupt_descriptor_table::entry & interrupt_descriptor_table::operator[](uint8_t offset)
{
	return table[offset];
}

const interrupt_descriptor_table::entry & interrupt_descriptor_table::operator[](uint8_t offset) const
{
	return table[offset];
}

void interrupt_descriptor_table::use(const interrupt_descriptor_table & idt)
{
	if (_idt == &idt)
		return;
	set_idt(idt, sizeof(idt));

	port::pic_master_command.write8slow(0x11);
	port::pic_slave_command.write8slow(0x11);

	port::pic_master_data.write8slow(0x20);
	port::pic_slave_data.write8slow(0x28);

	port::pic_master_data.write8slow(0x04);
	port::pic_slave_data.write8slow(0x02);

	port::pic_master_data.write8slow(0x01);
	port::pic_slave_data.write8slow(0x01);

	port::pic_master_data.write8slow(0x00);
	port::pic_slave_data.write8slow(0x00);

	_idt = &idt;
}

void interrupt_descriptor_table::enable_interrupts()
{
	if (!_idt)
		return;
	nmi_enable();
	irq_enable();
}

void interrupt_descriptor_table::disable_interrupts()
{
	irq_disable();
	nmi_disable();
}
