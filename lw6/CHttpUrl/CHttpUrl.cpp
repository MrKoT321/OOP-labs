#include "CHttpUrl.h"
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	try 
	{
		ParseUrl(url);
	}
	catch (std::exception const& e)
	{
		throw CUrlParsingError(e.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
{
	ValidatePassedFields(domain, document);

	SetDefaultPort();
	m_domain = domain;
	m_document = document[0] == '/' ? document : '/' + document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, int port)
	: CHttpUrl(domain, document, protocol)
{
	if (port < PORT_MIN_VALUE || port > PORT_MAX_VALUE)
	{
		throw std::invalid_argument("Invalid port passed");
	}
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	auto iter = PROTOCOL_PORT_MAP.find(m_protocol);
	if (iter->second == m_port)
	{
		// url separators in const
		return GetStringProtocol() + "://" + m_domain + m_document;
	}
	return GetStringProtocol() + "://" + m_domain + ":" + std::to_string(m_port) + m_document;

}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetStringProtocol() const
{
	for (auto& [strProtocol, protocol] : STRING_PROTOCOL_MAP)
	{
		if (protocol == m_protocol)
		{
			return strProtocol;
		}
	}
	return "";
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(std::string const& url)
{
	// const urlRegex
	const std::regex reg(R"((http|https)://([\w.]+)(:(\d+))?(/([^\s]+)?)?)", std::regex_constants::icase);
	std::smatch matchResult;

	if (!std::regex_match(url, matchResult, reg))
	{
		throw std::invalid_argument("Invalid url passed");
	}
	
	// indexes in consts
	auto iter = STRING_PROTOCOL_MAP.find(StrToLower(matchResult[1]));
	m_protocol = iter != STRING_PROTOCOL_MAP.end() ? iter->second : throw std::invalid_argument("Invalid protocol passed");
	
	// stoi exeception
	SetPort(matchResult[4]);
	m_domain = matchResult[2];
	m_document = matchResult[5];
}

void CHttpUrl::SetPort(std::string const& stringPort)
{
	if (stringPort.empty())
	{
		SetDefaultPort();
		return;
	}

	auto port = stoi(stringPort);
	if (port < PORT_MIN_VALUE || port > PORT_MAX_VALUE)
	{
		throw std::invalid_argument("Invalid port passed");
	}
	m_port = port;
}

void CHttpUrl::SetDefaultPort()
{
	auto iter = PROTOCOL_PORT_MAP.find(m_protocol);
	m_port = iter != PROTOCOL_PORT_MAP.end()
		? iter->second
		: throw std::invalid_argument("No default port for this protocol");
}

void CHttpUrl::ValidatePassedFields(std::string const& domain, std::string const& document) const
{
	const std::regex regDomain(R"([\w.]+)", std::regex_constants::icase);
	std::smatch matchResultDomain;

	if (!std::regex_match(domain, matchResultDomain, regDomain))
	{
		throw std::invalid_argument("Invalid domain passed");
	}

	const std::regex regDocument(R"(\/?[^\s]+)", std::regex_constants::icase);
	std::smatch matchResultDocument;

	if (!std::regex_match(document, matchResultDocument, regDocument))
	{
		throw std::invalid_argument("Invalid document passed");
	}
}
