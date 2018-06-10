#pragma once

#include <stdint.h>
#include <stddef.h>

class console
{
	static constexpr size_t width = 80;
	static constexpr size_t height = 25;
	struct symbol
	{
		int8_t c;
		uint8_t attr;
	} * vmem;
	size_t y;
	size_t x;
	uint8_t attr;
public:
	explicit console(bool clear = true);
	~console();

	static size_t pos(size_t y, size_t x);

	void update_cursor();

	console & write(char c);

	console & scroll();
private:
	void correct();
};

console & operator<<(console & con, char c);
console & operator<<(console & con, const char * s);

console & operator<<(console & con, size_t n);
