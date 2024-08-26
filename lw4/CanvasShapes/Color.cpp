#include "Color.h"
#include <iomanip>
#include <sstream>

std::string GetHexStrFromUint32(uint32_t const& uint32)
{
    const int COLOR_LEN = 6;
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(COLOR_LEN) << std::hex << uint32;
    return stream.str();
}

uint32_t GetUInt32ColorFromString(std::string const& str)
{
	const int COLOR_RADIX = 16;
	int color;
	try
	{
		color = std::stoi(str, 0, COLOR_RADIX);
	}
	catch (std::exception const&)
	{
		throw std::runtime_error("Invalid color format");
	}
	if (color < 0 || color > UINT32_MAX)
	{
		throw std::runtime_error("Invalid color format");
	}
	return uint32_t(color);
}
