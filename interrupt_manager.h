#pragma once

#include <stdint.h>

class interrupt_handler
{
public:
	interrupt_handler();
	virtual uint32_t operator()(uint32_t esp);
};

class interrupt_manager
{
	interrupt_handler * handlers[0x100];
public:
	interrupt_manager();
	void set(uint8_t number, interrupt_handler * handler);
	interrupt_handler * operator[](uint8_t number);
};
