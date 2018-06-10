#pragma once

#include "interrupt_manager.h"
#include "port.h"

namespace driver
{

class keyboard : public interrupt_handler
{
	static const port dataport;
	static const port commandport;
public:
	keyboard();
	uint32_t operator()(uint32_t esp) override;
};

}
