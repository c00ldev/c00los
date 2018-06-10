#include "interrupt_manager.h"

#include "console.h"
#include "interrupt_manager.h"
#include "port.h"

#include <stddef.h>

extern console con;
extern interrupt_manager iman;

interrupt_handler::interrupt_handler()
{
}

uint32_t interrupt_handler::operator()(uint32_t esp)
{
	return esp;
}

interrupt_manager::interrupt_manager()
	: handlers{}
{
}

interrupt_handler * interrupt_manager::operator[](uint8_t number)
{
	return handlers[number];
}

void interrupt_manager::set(uint8_t number, interrupt_handler * handler)
{
	handlers[number] = handler;
}

extern "C"
{

uint32_t handle_interrupts(uint8_t number, uint32_t esp)
{
	if (number != 0x20)
		con << (size_t)number << "\n";
	if (iman[number])
		esp = (*iman[number])(esp);
	if (0x20 <= number && number < 0x30)
	{
		port::pic_master_command.write8slow(0x20);
		if (0x28 <= number)
			port::pic_slave_command.write8slow(0x20);
	}
	return esp;
}

}
