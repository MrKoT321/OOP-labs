#include <iostream>
#include "CommandHandler.h"

void HandleCommand(CommandHandler& commandHandler)
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

void PollEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
		{
			sf::FloatRect visibleArea(
				0,
				0,
				static_cast<float>(event.size.width),
				static_cast<float>(event.size.height));
			window.setView(sf::View(visibleArea));
			break;
		}
		default:
			break;
		}
	}
}

void DrawShapes(sf::RenderWindow& window, CommandHandler& commandHandler)
{
	while (window.isOpen())
	{
		PollEvents(window);
		window.clear(sf::Color::White);
		commandHandler.DrawShapes(window);
		window.display();
	}
}

int main()
{
	CommandHandler commandHandler(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		HandleCommand(commandHandler);
	}

	if (std::cin.eof())
	{
		commandHandler.PrintResults();
	}

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shapes", sf::Style::Default, settings);
	DrawShapes(window, commandHandler);

	return EXIT_SUCCESS;
}
