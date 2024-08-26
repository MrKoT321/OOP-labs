#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Car/Car.h"

void AssertSpeedRangeLimits(Car& car, int minSpeed, int maxSpeed)
{
	CHECK(!car.SetSpeed(minSpeed - 1));
	CHECK(car.SetSpeed(minSpeed));
	CHECK(!car.SetSpeed(maxSpeed + 1));
	CHECK(car.SetSpeed(maxSpeed));
}

void AssertMinSpeedToChangeGear(Car& car, int speed, int gear)
{
	car.SetSpeed(speed - 1);
	CHECK(!car.SetGear(gear));
	car.SetSpeed(speed);
	CHECK(car.SetGear(gear));
}

void AssertMaxSpeedToChangeGear(Car& car, int speed, int gear)
{
	car.SetSpeed(speed + 1);
	CHECK(!car.SetGear(gear));
	car.SetSpeed(speed);
	CHECK(car.SetGear(gear));
}

TEST_CASE("The car is turned off in the start")
{
	Car car;
	CHECK(!car.IsTurnedOn());
}

TEST_CASE("The car can be started")
{
	Car car;
	CHECK(car.TurnOnEngine());
	CHECK(car.IsTurnedOn());
}

TEST_CASE("The car can be turned off after starting")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.TurnOffEngine());
	CHECK(!car.IsTurnedOn());
}

TEST_CASE("The car can change gear")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.SetGear(Car::FIRST_GEAR));
	CHECK(car.GetGear() == Car::FIRST_GEAR);
}

TEST_CASE("The car can't change gear when turned off")
{
	Car car;
	CHECK(!car.SetGear(Car::FIRST_GEAR));
}

TEST_CASE("The car can't change gear that not exist")
{
	Car car;
	car.TurnOnEngine();
	CHECK(!car.SetGear(100000));
}

TEST_CASE("The car can't change gear that not in speed range")
{
	Car car;
	car.TurnOnEngine();
	CHECK(!car.SetGear(Car::SECOND_GEAR));
}

TEST_CASE("The car can't change gear to first while driving backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::REVERSE_GEAR);
	car.SetSpeed(10);
	CHECK(!car.SetGear(Car::FIRST_GEAR));
	CHECK(car.SetGear(Car::NEUTRAL_GEAR));
}

TEST_CASE("The car can't change gear to reverse while driving forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::FIRST_GEAR);
	car.SetSpeed(10);

	CHECK(!car.SetGear(Car::REVERSE_GEAR));
	CHECK(car.SetGear(Car::NEUTRAL_GEAR));
}

TEST_CASE("The car can change the gear to reverse")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.GetSpeed() == 0);
	car.SetGear(Car::REVERSE_GEAR);
	CHECK(car.GetGear() == Car::REVERSE_GEAR);
}

TEST_CASE("The car may start to drive with speed")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::FIRST_GEAR);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
}

TEST_CASE("The car can't change speed while turning off")
{
	Car car;
	CHECK(!car.SetSpeed(100));
}

TEST_CASE("The car can't change speed out of gear speed range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::FIRST_GEAR);
	CHECK(!car.SetSpeed(31));
}

TEST_CASE("The car can't increase speed on neutral gear") // Замедленние на передней скорости
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::FIRST_GEAR);
	car.SetSpeed(20);

	car.SetGear(Car::NEUTRAL_GEAR);
	CHECK(!car.SetSpeed(21));
	CHECK(car.SetSpeed(20));
	CHECK(car.SetSpeed(19));
}

TEST_CASE("The car can drive with negative speed")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::REVERSE_GEAR);
	car.SetSpeed(10);
	CHECK(car.GetSpeed() == -10);

	car.SetGear(Car::NEUTRAL_GEAR);
	CHECK(!car.SetSpeed(11));
	CHECK(car.SetSpeed(5));
	CHECK(car.GetSpeed() == -5);
}

TEST_CASE("The car can change drive direction")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.GetDirection() == Direction::Standing);

	car.SetGear(Car::FIRST_GEAR);
	car.SetSpeed(20);
	CHECK(car.GetDirection() == Direction::Forward);

	car.SetSpeed(0);
	car.SetGear(Car::REVERSE_GEAR);
	car.SetSpeed(10);
	CHECK(car.GetDirection() == Direction::Backward);
}

TEST_CASE("The car can be turned off only at zero speed")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::FIRST_GEAR);
	car.SetSpeed(20);
	CHECK(!car.TurnOffEngine());

	car.SetSpeed(0);
	car.SetGear(Car::NEUTRAL_GEAR);
	CHECK(car.TurnOffEngine());
	CHECK(!car.IsTurnedOn());
}

TEST_CASE("Test car speed limits") // граничные значения для каждой скорости и передачи передачи
{
	Car car;
	car.TurnOnEngine();

	car.SetGear(Car::REVERSE_GEAR);
	AssertSpeedRangeLimits(car, 0, 20);
	car.SetSpeed(0);

	car.SetGear(Car::FIRST_GEAR);
	AssertSpeedRangeLimits(car, 0, 30);
	
	car.SetGear(Car::SECOND_GEAR);
	AssertSpeedRangeLimits(car, 20, 50);

	car.SetGear(Car::THIRD_GEAR);
	AssertSpeedRangeLimits(car, 30, 60);

	car.SetGear(Car::FOURTH_GEAR);
	AssertSpeedRangeLimits(car, 40, 90);

	car.SetGear(Car::FIFTH_GEAR);
	AssertSpeedRangeLimits(car, 50, 150);
	CHECK(car.SetGear(Car::NEUTRAL_GEAR));
}

TEST_CASE("Test car gear speed range limits")
{
	Car car;
	car.TurnOnEngine();

	car.SetGear(Car::FIRST_GEAR);
	AssertMaxSpeedToChangeGear(car, 0, Car::REVERSE_GEAR);

	car.SetGear(Car::FIRST_GEAR);
	AssertMinSpeedToChangeGear(car, 20, Car::SECOND_GEAR);
	AssertMaxSpeedToChangeGear(car, 30, Car::FIRST_GEAR);

	car.SetGear(Car::SECOND_GEAR);
	AssertMinSpeedToChangeGear(car, 30, Car::THIRD_GEAR);
	AssertMaxSpeedToChangeGear(car, 50, Car::SECOND_GEAR);

	car.SetGear(Car::THIRD_GEAR);
	AssertMinSpeedToChangeGear(car, 40, Car::FOURTH_GEAR);
	AssertMaxSpeedToChangeGear(car, 60, Car::THIRD_GEAR);

	car.SetGear(Car::FOURTH_GEAR);
	AssertMinSpeedToChangeGear(car, 50, Car::FIFTH_GEAR);
	AssertMaxSpeedToChangeGear(car, 90, Car::FOURTH_GEAR);
}