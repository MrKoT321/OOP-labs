#pragma once
#include "Protocol.h"
#include "CUrlParsingError.h"
#include "Common.h"
#include <map>

class CHttpUrl
{
public:
    CHttpUrl(std::string const& url);
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP
    );
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        int port
    );
    std::string GetURL() const;
    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    std::string GetStringProtocol() const;
    unsigned short GetPort() const;

private:
    static inline const std::map<std::string, Protocol> STRING_PROTOCOL_MAP = {
        { "http", Protocol::HTTP },
        { "https", Protocol::HTTPS },
    };
    static inline const std::map<Protocol, unsigned short> PROTOCOL_PORT_MAP = {
        {Protocol::HTTP, 80},
        {Protocol::HTTPS, 443},
    };
    static inline const unsigned short PORT_MAX_VALUE = 65535;
    static inline const unsigned short PORT_MIN_VALUE = 1;

    void ParseUrl(std::string const& url);
    void SetPort(std::string const& stringPort);
    void SetDefaultPort();
    void ValidatePassedFields(std::string const& domain, std::string const& document) const;

    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned short m_port;
};