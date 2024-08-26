#include "UrlParser.h"

#include <algorithm>
#include <map>
#include <regex>

namespace UrlParser
{
	std::map<std::string, Protocol> protocolFromStringMap = {
		{"http", Protocol::HTTP},
		{"https", Protocol::HTTPS},
		{"ftp", Protocol::FTP}
	};

	std::map<Protocol, int> protocolPortMap = {
		{Protocol::HTTP, 80},
		{Protocol::HTTPS, 443},
		{Protocol::FTP, 21}
	};

	const int PORT_MAX_VALUE = 65535;
	const int PORT_MIN_VALUE = 1;
}

std::string StrToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return std::tolower(c); }
	);

	return str;
}

bool SetProtocol(Protocol& protocol, std::string const& value)
{
	if (!UrlParser::protocolFromStringMap.contains(value))
	{
		return false;
	}

	protocol = UrlParser::protocolFromStringMap[value];
	return true;
}

bool SetDefaultPort(int& port, Protocol const& protocol)
{
	if (!UrlParser::protocolPortMap.contains(protocol))
	{
		return false;
	}

	port = UrlParser::protocolPortMap[protocol];
	return true;
}

// ситуация порт выходит за предел int
bool SetPort(int& port, std::string const& value, Protocol const& protocol)
{
	if (value.empty())
	{
		return SetDefaultPort(port, protocol);
	}
	if (port = stoi(value))
	{
		return port >= UrlParser::PORT_MIN_VALUE && port <= UrlParser::PORT_MAX_VALUE;
	}

	return false;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	// http://abc/  not working
	const std::regex reg(R"((http|https|ftp)://([\w.]+)(:(\d+))?(/([^\s]+)?)?)", std::regex_constants::icase);
	std::smatch matchResutl;

	if (!std::regex_match(url, matchResutl, reg))
	{
		return false;
	}

	if (!SetProtocol(protocol, StrToLower(matchResutl[1])))
	{
		return false;
	}

	if (!SetPort(port, matchResutl[4], protocol))
	{
		return false;
	}

	host = matchResutl[2];
	document = matchResutl[6];

	return true;
}