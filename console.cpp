#include "console.h"

extern "C" void pos_cur(size_t pos);

console::console(bool clear)
	: vmem((symbol *)0xB8000)
	, y(0)
	, x(0)
	, attr(0)
{
	if (clear)
		for (size_t i = 0; i < width * height; ++i)
			vmem[pos(i / width, i % width)].c = ' ';
	update_cursor();
}

console::~console()
{
}

size_t console::pos(size_t y, size_t x)
{
	return x + y * width;
}


void console::update_cursor()
{
	pos_cur(pos(y, x));
}

console & console::write(char c)
{
	if ((c >= 32 && c < 127) || c < 0)  // Printable
	{
		vmem[pos(y, x++)].c = c;
		correct();
		return *this;
	}
	switch (c)
	{
	case 0x00:  // NUL
		break;
	case 0x01:  // SOH
		break;
	case 0x02:  // STX
		break;
	case 0x03:  // ETX
		break;
	case 0x04:  // EOT
		break;
	case 0x05:  // ENQ
		break;
	case 0x06:  // ACK
		break;
	case 0x07:  // BEL
		break;
	case 0x08:  // BS
		break;
	case 0x09:  // TAB
		break;
	case 0x0A:  // LF
		++y;
		x = 0;
		break;
	case 0x0B:  // VT
		break;
	case 0x0C:  // FF
		break;
	case 0x0D:  // CR
		x = 0;
		break;
	case 0x0E:  // SO
		break;
	case 0x0F:  // SI
		break;
	case 0x10:  // DLE
		break;
	case 0x11:  // DC1
		break;
	case 0x12:  // DC2
		break;
	case 0x13:  // DC3
		break;
	case 0x14:  // DC4
		break;
	case 0x15:  // NAK
		break;
	case 0x16:  // SYN
		break;
	case 0x17:  // ETB
		break;
	case 0x18:  // CAN
		break;
	case 0x19:  // EM
		break;
	case 0x1A:  // SUB
		break;
	case 0x1B:  // ESC
		break;
	case 0x1C:  // FS
		break;
	case 0x1D:  // GS
		break;
	case 0x1E:  // RS
		break;
	case 0x1F:  // US
		break;
	case 0x7F:  // DEL
		break;
	default:    // Printable
		vmem[pos(y, x++)].c = c;
		break;
	}
	correct();
	return *this;
}

console & console::scroll()
{
	for (size_t i = 1; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
			vmem[pos(i - 1, j)] = vmem[pos(i, j)];
	for (size_t j = 0; j < width; ++j)
		vmem[pos(height - 1, j)].c = ' ';
	--y;
	update_cursor();
	return *this;
}

void console::correct()
{
	y += x / width;
	x %= width;
	while (y >= height)
		scroll();
	update_cursor();
}

console & operator<<(console & con, char c)
{
	return con.write(c);
}

console & operator<<(console & con, const char * s)
{
	for (; *s; ++s)
		con << *s;
	return con;
}

console & operator<<(console & con, size_t n)
{
	char arr[21] = {};
	size_t i = 0;
	do
	{
		arr[i++] = (char)(n % 10) + '0';
		n /= 10;
	} while (n);
	for (size_t j = 0; j < i; ++j)
		con << arr[i - j - 1];
	return con;
}
