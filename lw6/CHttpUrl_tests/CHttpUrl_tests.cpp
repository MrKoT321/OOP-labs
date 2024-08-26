#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../CHttpUrl/CHttpUrl.h"

TEST_CASE("Create CHttpUrl on empty string")
{
	CHECK_THROWS_AS(CHttpUrl(""), CUrlParsingError);
}

TEST_CASE("Create CHttpUrl on common string")
{
	CHttpUrl httpUrl("https://abc:1000/example/image.png");
	CHECK(httpUrl.GetDocument() == "/example/image.png");
	CHECK(httpUrl.GetDomain() == "abc");
	CHECK(httpUrl.GetProtocol() == Protocol::HTTPS);
	CHECK(httpUrl.GetPort() == 1000);
}

TEST_CASE("Create CHttpUrl with invalid and boundary port")
{
	CHECK_THROWS_AS(CHttpUrl("http://localhost:65536"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http://localhost:0"), CUrlParsingError);
	CHECK_NOTHROW(CHttpUrl("http://localhost:65535"));
	CHECK_NOTHROW(CHttpUrl("http://localhost:1"));
	CHECK_NOTHROW(CHttpUrl("http://localhost"));
}

TEST_CASE("Create CHttpUrl with invalid url")
{
	CHECK_THROWS_AS(CHttpUrl("htt://localhost"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http:/localhost"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl(" http://localhost"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("localhost:8000"), CUrlParsingError);
	CHECK_NOTHROW(CHttpUrl("http://local???host"));

}

TEST_CASE("Create CHttpUrl without port")
{
	CHECK_NOTHROW(CHttpUrl("https://localhost/example/image.png"));
	CHttpUrl httpUrl("https://localhost/example/image.png");
	CHECK(httpUrl.GetPort() == 443);
	
	CHttpUrl httpUrl1("http://localhost/example/image.png");
	CHECK(httpUrl1.GetPort() == 80);
}

TEST_CASE("Create CHttpUrl and get url")
{
	std::string url = "https://localhost/example/image.png";
	CHttpUrl httpUrl(url);
	CHECK(httpUrl.GetURL() == url);

	std::string httpsUrlWithDefaultPort = "https://localhost:443/example/image.png";
	CHttpUrl httpUrl1(httpsUrlWithDefaultPort);
	CHECK(httpUrl1.GetURL() == url);

	std::string httpUrlWithDefaultPort = "http://localhost:80/example/image.png";
	CHttpUrl httpUrl2(httpUrlWithDefaultPort);
	CHECK(httpUrl2.GetURL() == "http://localhost/example/image.png");

	std::string httpsUrlWithUpperCase = "HTTPS://localhost:443/example/image.png";
	CHttpUrl httpUrl3(httpsUrlWithUpperCase);
	CHECK(httpUrl3.GetURL() == url);
}

TEST_CASE("Create CHttpUrl with custom constructor on empty fields")
{
	CHECK_THROWS_AS(CHttpUrl("", " "), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl(" ", ""), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl(" ", " "), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("", ""), std::invalid_argument);
}

TEST_CASE("Create CHttpUrl with custom constructor with invalid arguments")
{
	CHECK_THROWS_AS(CHttpUrl(" localhost ", " tt "), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("localhost", "tt", Protocol::HTTP, 0), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("localhost", "tt", Protocol::HTTP, 65536), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("localhost", "tt", Protocol::HTTPS, 0), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("localhost", "tt", Protocol::HTTPS, 65536), std::invalid_argument);
}

TEST_CASE("Create CHttpUrl with custom constructor with default fields")
{
	CHttpUrl httpUrl("localhost", "/image.png");
	CHECK(httpUrl.GetDocument() == "/image.png");
	CHECK(httpUrl.GetDomain() == "localhost");
	CHECK(httpUrl.GetPort() == 80);
	CHECK(httpUrl.GetStringProtocol() == "http");
	CHECK(httpUrl.GetURL() == "http://localhost/image.png");

	CHttpUrl httpUrl1("localhost", "image.png");
	CHECK(httpUrl1.GetDocument() == "/image.png");
	CHECK(httpUrl.GetURL() == "http://localhost/image.png");
}

TEST_CASE("Create CHttpUrl with custom constructor on boundary ports")
{
	CHECK_NOTHROW(CHttpUrl("localhost", "tt", Protocol::HTTP, 1));
	CHECK_NOTHROW(CHttpUrl("localhost", "tt", Protocol::HTTP, 65535));
	CHECK_NOTHROW(CHttpUrl("localhost", "tt", Protocol::HTTPS, 1));
	CHECK_NOTHROW(CHttpUrl("localhost", "tt", Protocol::HTTPS, 65535));
}

TEST_CASE("Create CHttpUrl with custom constructor")
{
	CHttpUrl httpUrl("localhost", "tt", Protocol::HTTPS, 10);
	CHECK(httpUrl.GetURL() == "https://localhost:10/tt");

	CHttpUrl httpUrl1("localhost", "tt", Protocol::HTTP, 10);
	CHECK(httpUrl1.GetURL() == "http://localhost:10/tt");
}

TEST_CASE("Create CHttpUrl with custom constructor with setting defaults ports")
{
	CHttpUrl httpUrl("localhost", "tt", Protocol::HTTPS, 443);
	CHECK(httpUrl.GetURL() == "https://localhost/tt");

	CHttpUrl httpUrl1("localhost", "tt", Protocol::HTTP, 80);
	CHECK(httpUrl1.GetURL() == "http://localhost/tt");
}
