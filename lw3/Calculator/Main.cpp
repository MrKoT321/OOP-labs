#include "CommandHandler.h"
#include <iostream>
#include <format>

int main()
{
	{
		Calculator calculator;
		CommandHandler commandHandler(calculator, std::cin, std::cout);

		while (!(std::cin.eof() || std::cin.fail()))
		{
			std::cout << "> ";
			try
			{
				commandHandler.HandleCommand();
			}
			catch (std::exception const& e)
			{
				std::cout << e.what() << std::endl;

			}
		}
	}

	return EXIT_SUCCESS;
}