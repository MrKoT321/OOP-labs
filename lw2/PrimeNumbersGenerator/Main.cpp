#include "PrimeNumbersGenerator.h"

void PrintSet(std::set<int> const& set)
{
	for (auto const& elem : set)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	int upperBound;
	if (!(std::cin >> upperBound))
	{
		std::cout << "Failed to read \"upperBound\". Try another one.";
		return EXIT_FAILURE;
	}

	try
	{
		auto primes = GeneratePrimeNumbersSet(upperBound);
		PrintSet(primes);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}