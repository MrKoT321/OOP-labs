#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HtmlDecode/HtmlDecode.h"

TEST_CASE("HTML Decode on empty string")
{
	std::string_view input = "";
	std::string expected = "";
	CHECK(HtmlDecode(input) == expected);
}

TEST_CASE("HTML Decode on not encoded text")
{
	std::string_view input = "&lt &gt &quot &amp &apos &aps; apos; &; ;;; && ";
	std::string expected = "&lt &gt &quot &amp &apos &aps; apos; &; ;;; && ";
	CHECK(HtmlDecode(input) == expected);
}

TEST_CASE("HTML Decode on encoded values")
{
	std::string_view input = "&lt; &gt; &quot; &amp; &apos;";
	std::string expected = "< > \" & '";
	CHECK(HtmlDecode(input) == expected);
}

TEST_CASE("HTML Decode on average encoded text")
{
	std::string_view input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string expected = "Cat <says> \"Meow\". M&M's";
	CHECK(HtmlDecode(input) == expected);
}