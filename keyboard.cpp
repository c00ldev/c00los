#include "keyboard.h"

#include "console.h"

extern console con;

namespace driver
{

const port keyboard::dataport = port::ps2[0];
const port keyboard::commandport = port::ps2[4];

keyboard::keyboard()
{
	while (commandport.read8() & 0x1u)
		dataport.read8();
	commandport.write8(0xAE);
	commandport.write8(0x20);
	uint8_t status = (dataport.read8() | 1u) & ~0x10u;
	commandport.write8(status);
	dataport.write8(0xF4);
}

uint32_t keyboard::operator()(uint32_t esp)
{
	uint8_t key = dataport.read8();
	char hex[] = "0123456789ABCDEF";
	con << "KB " << "0x" << hex[(key >> 4u) & 0xFu] << hex[key & 0xFu] << "\n";
	return esp;
}

}
