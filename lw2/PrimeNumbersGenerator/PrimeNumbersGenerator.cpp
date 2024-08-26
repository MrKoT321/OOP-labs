#include "PrimeNumbersGenerator.h"

std::vector<bool> GetSieveOfErastophene(int upperBound)
{
	std::vector<bool> sieveOfErastophene(upperBound + 1, true);

	// test number < upperBound
	for (int number = 2; number <= upperBound; number++)
	{
		if (sieveOfErastophene[number])
		{
			if (INT_MAX / number < number)
			{
				continue;
			}

			// All even numbers are deleted when processing multiples of 2
			// We may jump over even numbers when number is >= 3
			int summand = number == 2 ? number : 2 * number;
			for (int i = number * number; i <= upperBound; i += summand)
			{
				sieveOfErastophene[i] = false;
			}
		}
	}

	return sieveOfErastophene;
}

std::set<int> GetPrimeNumbersSetFromErastopheneSieve(std::vector<bool> const& sieveOfErastophene, int upperBound)
{
	std::set<int> primeNumbers;

	// loop can work fast
	for (int i = 2; i <= upperBound; i++)
	{
		if (sieveOfErastophene[i])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	int lowerBound = 2;
	int maxUpperBound = 100000000;

	if (upperBound < lowerBound || upperBound > maxUpperBound)
	{
		throw std::out_of_range("Failed to generate prime numbers. Try to use another \"upperBound\" from " 
			+ std::to_string(lowerBound) + " to " + std::to_string(maxUpperBound)
		);
	}

	auto sieveOfErastophene = GetSieveOfErastophene(upperBound);
	
	return GetPrimeNumbersSetFromErastopheneSieve(sieveOfErastophene, upperBound);
}