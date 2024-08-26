#include "Common.h"
#include <algorithm>

std::string StrToLower(std::string const& str)
{
	auto strCopy = str;
	std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(),
		[](unsigned char c) { return std::tolower(c); }
	);
	return strCopy;
}
