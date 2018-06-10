#pragma once

#include <stdint.h>
#include <stddef.h>

class port
{
	uint16_t number;
public:
	port(uint16_t number);

	uint8_t read8() const;
	void write8(uint8_t byte) const;
	void write8slow(uint8_t byte) const;
public:
	static const port pic_master_command;
	static const port pic_master_data;
	static const port pic_slave_command;
	static const port pic_slave_data;
	static const port ps2[5];
};
