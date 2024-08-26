#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Vector/Vector.h"

TEST_CASE("Multiplie the empty vector by minimum")
{
	std::vector<double> vector = {};

	MultiplieVectorByMunimum(vector);

	std::vector<double> expected = {};
	CHECK(vector == expected);
}

TEST_CASE("Multiplie the vector by positive minimum")
{
	std::vector<double> vector = { 2, 8, 4, 3 };

	MultiplieVectorByMunimum(vector);

	std::vector<double> expected = { 4, 16, 8, 6 };
	CHECK(vector == expected);
}

TEST_CASE("Multiplie the vector by negative minimum")
{
	std::vector<double> vector = { 2, 8, -4, 3 };

	MultiplieVectorByMunimum(vector);

	std::vector<double> expected = { -8, -32, 16, -12 };
	CHECK(vector == expected);
}

TEST_CASE("Multiplie the vector by zero")
{
	std::vector<double> vector = { 2, 8, 4, 0 };

	MultiplieVectorByMunimum(vector);

	std::vector<double> expected = { 0, 0, 0, 0 };
	CHECK(vector == expected);
}

TEST_CASE("Write the empty vector")
{
	std::vector<double> vector = {};
	std::ostringstream output;

	WriteVector(vector, output);

	std::string outputExpected = "\n";
	CHECK(output.str() == outputExpected);
}

TEST_CASE("Write the vector with a precision of 3")
{
	std::vector<double> vector = { 2, 8.7775, 4.0001, 3.9996 };
	std::ostringstream output;

	WriteVector(vector, output);

	std::string outputExpected = "2.000 8.777 4.000 4.000 \n";
	CHECK(output.str() == outputExpected);
}