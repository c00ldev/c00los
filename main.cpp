#include "console.h"
#include "interrupt_descriptor_table.h"
#include "segment_desriptor_table.h"
#include "interrupt_manager.h"
#include "isr.h"
#include "keyboard.h"

extern "C"
{
	void halt();
}

//interrupt_descriptor_table __attribute__((section(".tables"))) idt;
//global_descriptor_table __attribute__((section(".tables"))) gdt;
interrupt_descriptor_table idt;
global_descriptor_table gdt;
interrupt_manager iman;

driver::keyboard kb;

console con;

int main()
{

//	for (size_t i = 0; i < 30; ++i)
//	{
//		con << i << "\n";
//	}

	con << "Constructing GDT\n";
	gdt[0] = { 0, 0, 0 };
	gdt[1] = { 0, 0xffffffffu, 0x9A };
	gdt[2] = { 0, 0xffffffffu, 0x92 };
	con << "GDT created\n";
	set_gdt(gdt, sizeof(gdt));
	seg_reload();
	con << "GDT loaded\n";

	con << "Constructing IDT\n";
	idt[0x20] = { 0x08, irq0, 0x8E };
	idt[0x21] = { 0x08, irq1, 0x8E };
	con << "IDT created\n";
	interrupt_descriptor_table::use(idt);
	interrupt_descriptor_table::enable_interrupts();
	con << "IDT loaded\n";

	con << "Creating interrupt handlers\n";
	iman.set(0x21, &kb);
	con << "Interrupt handlers created\n";

	halt();

	return 0;
}
