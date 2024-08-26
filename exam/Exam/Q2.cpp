#include <optional>
#include <iostream>

// std::optional - вспомогательный тип
// empty_optional + empty_optional = empty_optional



void fooQ2()
{
	std::optional<int> result;
	result = std::nullopt;
	result.reset();

	if (!result || !result.has_value())
	{
		// 
	}

	int x = 10;
	int taken = result.value_or(x);
	int taken1 = *result;
	int taken2 = std::move(*result);
	int taken3 = *std::move(result);

	
}