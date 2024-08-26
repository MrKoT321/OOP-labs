#include <iostream>	
#include <sstream>
#include "Car.h"

namespace {
	enum class Command {
		ERROR,
		INFO,
		ENGINE_ON,
		ENGINE_OFF,
		SET_GEAR,
		SET_SPEED
	};
	
	std::map<std::string, Command> commandToIdMap = {
		{"Info", Command::INFO},
		{"EngineOn", Command::ENGINE_ON},
		{"EngineOff", Command::ENGINE_OFF},
		{"SetGear", Command::SET_GEAR},
		{"SetSpeed", Command::SET_SPEED}
	};
}

std::string DirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::Forward:
		return "forward";
	case Direction::Backward:
		return "backward";
	case Direction::Standing:
		return "standing still";
	default:
		return "";
	}
}

void WriteCarInfo(Car& car)
{
	std::cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << std::endl;
	std::cout << "Direction: " << DirectionToString(car.GetDirection()) << std::endl;
	std::cout << "Speed: " << car.GetSpeed() << std::endl;
	std::cout << "Gear: " << car.GetGear() << std::endl;
}

void HandleErrorMessage(bool isActionSuccess, std::string errorMessage, std::string successMessage)
{
	if (isActionSuccess)
	{
		std::cout << successMessage << std::endl;
		return;
	}
	std::cout << errorMessage << std::endl;
}

void TurnOnEngineErrorHandling(bool wasTurnedOnSuccessfully)
{
	HandleErrorMessage(wasTurnedOnSuccessfully, "Engine turned on", "Unable to turn on engine");
}

void TurnOffEngineErrorHandling(bool wasTurnedOffSuccessfully)
{
	HandleErrorMessage(wasTurnedOffSuccessfully, "Engine turned off", "Unable to turn off engine");
}

void SetGearErrorHandling(bool wasSettedSuccessfully)
{
	HandleErrorMessage(wasSettedSuccessfully, "Gear set", "Unable to set gear");
}

void SetSpeedErrorHandling(bool wasSettedSuccessfully)
{
	HandleErrorMessage(wasSettedSuccessfully, "Speed set", "Unable to set speed");
}

void RunCarActions(Car & car)
{
	std::string command;

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> command;
		switch (commandToIdMap[command])
		{
		case Command::INFO:
			WriteCarInfo(car);
			break;
		case Command::ENGINE_ON:
			TurnOnEngineErrorHandling(car.TurnOnEngine());
			break;
		case Command::ENGINE_OFF:
			TurnOffEngineErrorHandling(car.TurnOffEngine());
			break;
		case Command::SET_GEAR:
			int gear;
			std::cin >> gear;
			SetGearErrorHandling(car.SetGear(gear));
			break;
		case Command::SET_SPEED:
			int speed;
			std::cin >> speed;
			SetSpeedErrorHandling(car.SetSpeed(speed));
			break;
		default:
			std::cout << "Unknown command" << std::endl;
		}
	}
}

int main()
{
	Car car;

	RunCarActions(car);

	return EXIT_SUCCESS;
}