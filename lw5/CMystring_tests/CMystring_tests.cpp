#define CATCH_CONFIG_MAIN
#include "../CMyString/CMyString.h"
#include "../../catch2/catch.hpp"

void AssertCMyStringFields(
	CMyString const& str,
	std::string value,
	size_t length,
	size_t capacity
)
{
	CHECK(str.GetStringData() == value);
	CHECK(str.GetLength() == length);
	CHECK(str.GetCapacity() == capacity);
}

TEST_CASE("Create CMyString")
{
	AssertCMyStringFields(CMyString(), "", 0, 0);
	AssertCMyStringFields(CMyString(""), "", 0, 0);
	AssertCMyStringFields(CMyString("Qwe"), "Qwe", 3, 3);
	AssertCMyStringFields(CMyString("Qwe", 4), "Qwe", 4, 4);
	AssertCMyStringFields(CMyString("Qwerty", 4), "Qwer", 4, 4);
	AssertCMyStringFields(CMyString(CMyString("")), "", 0, 0);
	AssertCMyStringFields(CMyString(CMyString("Carting")), "Carting", 7, 7);
}

TEST_CASE("Clear CMyString")
{
	CMyString str("Dog", 3);
	AssertCMyStringFields(str, "Dog", 3, 3);
	str.Clear();
	AssertCMyStringFields(str, "", 0, 3);
}

TEST_CASE("Substring CMyString")
{
	CMyString str("Right Open Exit");
	AssertCMyStringFields(str.SubString(6), "Open Exit", 9, 9);
	AssertCMyStringFields(str.SubString(6, 4), "Open", 4, 4);
	AssertCMyStringFields(str.SubString(6, 100), "Open Exit", 9, 9);
	CHECK_THROWS_AS(str.SubString(100), std::out_of_range);
}

TEST_CASE("Operator copy CMyString") 
{
	CMyString str1("Home");
	CMyString str2 = str1;
	AssertCMyStringFields(str2, "Home", 4, 4);
	CMyString str3("Street");
	CHECK(str1 == "Home");
	CHECK(!(str1 != str2));
	CHECK(str2 != str3);
}

TEST_CASE("Operator[] CMyString")
{
	CMyString str1("String");
	const char ch = str1[0];
	const char ch1 = str1[1];
	const char ch2 = str1[5];
	CHECK(str1[0] == ch);
	CHECK(str1[0] == 'S');
	CHECK(str1[1] == ch1);
	CHECK(str1[5] == ch2);
	CHECK_THROWS_AS(str1[-1], std::out_of_range);
	CHECK_THROWS_AS(str1[6], std::out_of_range);
}

TEST_CASE("operator <<")
{
	std::ostringstream output;
	CMyString str;
	CMyString str1("Cat");
	output << str;
	CHECK(output.str() == "");
	output << str1;
	CHECK(output.str() == "Cat");
}

TEST_CASE("operator >>")
{
	std::istringstream emptyInput;
	std::istringstream input("Cat Dog");
	CMyString str;
	CMyString str1;

	emptyInput >> str;
	AssertCMyStringFields(str, "", 0, 0);

	input >> str1;
	AssertCMyStringFields(str1, "Cat", 3, 3);
}

TEST_CASE("Operator +")
{
	CMyString str1("gaga");
	CMyString str2("gugu");
	CMyString str3 = str1 + str2;
	AssertCMyStringFields(str3, "gagagugu", 8, 8);
}

TEST_CASE("Compare perators CMyString")
{
	CMyString str1("Home");
	CMyString str2("Home");
	CMyString str3("Cat");

	CHECK(str1 <= str2);
	CHECK(str1 <= "Homeplace");
	CHECK("Abc" <= str1);
	CHECK(!(str1 <= str3));

	CHECK(!(str1 < str2));
	CHECK(str1 < "Homeplace");
	CHECK("Abc" < str1);

	CHECK(str1 >= str2);
	CHECK(!(str1 >= "Homosapiens"));
	CHECK(!("Dog" >= str1));

	CHECK(!(str1 > str2));
	CHECK(str1 > "Cat");
	CHECK("Homosapiens" > str1);
}

TEST_CASE("Operator += CMyString")
{
	CMyString str1("Mashroom");
	CMyString str2(" Portabella");
	str1 += str2;
	AssertCMyStringFields(str1, "Mashroom Portabella", 19, 19);
}