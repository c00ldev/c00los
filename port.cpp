#include "port.h"

extern "C"
{

uint8_t read8(uint16_t number);
void write8(uint16_t number, uint8_t byte);
void write8slow(uint16_t number, uint8_t byte);

}

const port port::pic_master_command = 0x20;
const port port::pic_master_data = 0x21;
const port port::pic_slave_command = 0xA0;
const port port::pic_slave_data = 0xA1;
const port port::ps2[5] = { 0x60, 0x61, 0x62, 0x63, 0x64 };

port::port(uint16_t number)
	: number(number)
{
}

uint8_t port::read8() const
{
	return ::read8(number);
}

void port::write8(uint8_t byte) const
{
	::write8(number, byte);
}

void port::write8slow(uint8_t byte) const
{
	::write8slow(number, byte);
}
