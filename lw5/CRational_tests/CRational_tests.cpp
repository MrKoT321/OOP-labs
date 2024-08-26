#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../CRational/CRational.h"


TEST_CASE("Assert equals CRationals with diffrent representation")
{
	CRational r = CRational(1, 2);
	CHECK(r == CRational(1, 2));
	CHECK(r == CRational(2, 4));
	CHECK(r == CRational(-1, -2));
	CHECK(!(r == CRational(1, -2)));
}

TEST_CASE("Assert not equals CRationals with diffrent representation")
{
	CRational r = CRational(1, 2);
	CHECK(!(r != CRational(1, 2)));
	CHECK(r != CRational(1, 3));
	CHECK(1 != r);
	CHECK(r != 1);
}

TEST_CASE("Assert compare operations")
{
	CRational r = CRational(1, 2);
	CHECK(r > CRational(1, 3));
	CHECK(!(r <= CRational(1, 3)));
	CHECK(r < CRational(2, 3));
	CHECK(!(r >= CRational(2, 3)));
	CHECK(r >= CRational(1, 3));
	CHECK(!(r < CRational(1, 3)));
	CHECK(r <= CRational(2, 3));
	CHECK(!(r > CRational(2, 3)));
}

TEST_CASE("Test create CRational")
{
	CRational r1 = CRational();
	CRational r2 = CRational(2, 1);
	CRational r3 = CRational(2);
	CHECK(r1 == 0);
	CHECK(0 == r1);
	CHECK(r2 == 2);
	CHECK(r2 == r3);
}

TEST_CASE("Test unar operations")
{
	CRational r = CRational(-2);
	CHECK(-r == 2);
	CHECK(+r == -2);
}

TEST_CASE("Test binary operations")
{
	CRational r = CRational(1, 2);
	CHECK(r + 1 == CRational(3, 2));
	CHECK(2 + r == CRational(5, 2));
	CHECK(r + CRational(1, 3) == CRational(5, 6));

	CHECK((r - 1) == CRational(-1, 2));
	CHECK(2 - r == CRational(3, 2));
	CHECK(CRational(5, 6) - r == CRational(1, 3));

	CHECK(r * 2 == 1);
	CHECK(3 * r == CRational(3, 2));
	CHECK(r * CRational(8, 5) == CRational(8, 10));

	CHECK(r / 2 == CRational(1, 4));
	CHECK(2 / r == 4);
	CHECK(r / CRational(8, 5) == CRational(5, 16));
}

TEST_CASE("CRational to compound fraction")
{
	CRational r = CRational(10, 8);
	auto [intPart, fracPart] = r.ToCompoundFraction();
	CHECK(intPart == 1);
	CHECK(fracPart == CRational(1, 4));

	CRational r1 = CRational(10, 10);
	auto [intPart1, fracPart1] = r1.ToCompoundFraction();
	CHECK(intPart1 == 1);
	CHECK(fracPart1 == CRational(0));

	CRational r2 = CRational(1, 10);
	auto [intPart2, fracPart2] = r2.ToCompoundFraction();
	CHECK(intPart2 == 0);
	CHECK(fracPart2 == CRational(1, 10));

	CRational r3 = CRational(-9, 4);
	auto [intPart3, fracPart3] = r3.ToCompoundFraction();
	CHECK(intPart3 == -2);
	CHECK(fracPart3 == CRational(-1, 4));
}