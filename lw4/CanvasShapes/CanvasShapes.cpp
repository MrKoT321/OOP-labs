#include <iostream>
#include "CommandHandler.h"

int main()
{
	CommandHandler commandHandler(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		try
		{
			std::cout << "> ";
			commandHandler.HandleCommand();
		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	if (std::cin.eof())
	{
		commandHandler.PrintResults();
	}

    return EXIT_SUCCESS;
}
