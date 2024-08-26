#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../PrimeNumbersGenerator/PrimeNumbersGenerator.h"
#include "boost/timer.hpp"

TEST_CASE("Generate prime numbers up to zero")
{
	CHECK_THROWS_WITH(GeneratePrimeNumbersSet(0), "Failed to generate prime numbers. Try to use another \"upperBound\" from 2 to 100000000");
}

TEST_CASE("Generate prime numbers up to negative number")
{
	CHECK_THROWS_WITH(GeneratePrimeNumbersSet(-1), "Failed to generate prime numbers. Try to use another \"upperBound\" from 2 to 100000000");
}

TEST_CASE("Generate prime numbers beyond the lower limit")
{
	CHECK_THROWS_WITH(GeneratePrimeNumbersSet(1), "Failed to generate prime numbers. Try to use another \"upperBound\" from 2 to 100000000");
}

TEST_CASE("Generate prime numbers beyond the upper limit")
{
	CHECK_THROWS_WITH(GeneratePrimeNumbersSet(100000001), "Failed to generate prime numbers. Try to use another \"upperBound\" from 2 to 100000000");
}

TEST_CASE("Generate prime numbers up to lower limit")
{
	std::set<int> expectedPrimeNumbers{ 2 };
	CHECK(GeneratePrimeNumbersSet(2) == expectedPrimeNumbers);
}

TEST_CASE("Generate prime numbers up to 12")
{
	std::set<int> expectedPrimeNumbers{ 2, 3, 5, 7, 11 };
	CHECK(GeneratePrimeNumbersSet(12) == expectedPrimeNumbers);
}

TEST_CASE("Generate prime numbers up to 10")
{
	std::set<int> expectedPrimeNumbers { 2, 3, 5, 7 };
	CHECK(GeneratePrimeNumbersSet(10) == expectedPrimeNumbers);
}

TEST_CASE("Generate prime numbers up to upper limit")
{
	boost::timer timer;
	timer.restart();

	std::set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);
	
	double duration = timer.elapsed();
	
	CHECK(primeNumbers.size() == 5761455);
	CHECK(duration < 4);
}