#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../UrlParser/UrlParser.h"

namespace
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
}

TEST_CASE("The url with invalid protocol")
{
	CHECK(!ParseURL("htt://localhost:80/cat", protocol, port, host, document));
	CHECK(!ParseURL("localhost:80/cat", protocol, port, host, document));
	CHECK(!ParseURL("https:///localhost:80/cat", protocol, port, host, document));
	CHECK(!ParseURL("https:/localhost:80/cat", protocol, port, host, document));

	REQUIRE_THROWS_AS(ParseURL("https://localhost:999999999999999", protocol, port, host, document), std::out_of_range);
}

TEST_CASE("Test the url value and spelling")
{
	CHECK(!ParseURL("https://localhost:/cat", protocol, port, host, document));
	CHECK(!ParseURL("https://localhost:0/cat", protocol, port, host, document));
	CHECK(!ParseURL("https://localhost:65536/cat", protocol, port, host, document));
	
	CHECK(ParseURL("https://abc/", protocol, port, host, document));
	CHECK(ParseURL("https://localhost:80/", protocol, port, host, document));
	CHECK(ParseURL("https://localhost:1/cat", protocol, port, host, document));
	CHECK(ParseURL("https://localhost:65535/cat", protocol, port, host, document));
}

TEST_CASE("Common url")
{
	CHECK(ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document));
	CHECK(port == 80);
	CHECK(host == "www.mysite.com");
	CHECK(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("The url can be written in uppercase")
{
	CHECK(ParseURL("HTTPS://localhost:80/cat", protocol, port, host, document));
	CHECK(ParseURL("https://LOCALHOST:80/cat", protocol, port, host, document));
}

TEST_CASE("The url port default port values")
{
	CHECK(ParseURL("https://localhost/cat", protocol, port, host, document));
	CHECK(port == 443);

	CHECK(ParseURL("http://localhost/cat", protocol, port, host, document));
	CHECK(port == 80);

	CHECK(ParseURL("ftp://localhost/cat", protocol, port, host, document));
	CHECK(port == 21);
}