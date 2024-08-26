#pragma once
#include <optional>
#include <map>


enum class Direction
{
	Forward,
	Backward,
	Standing
};

class Car
{
public:
	static const int REVERSE_GEAR = -1;
	static const int NEUTRAL_GEAR = 0;
	static const int FIRST_GEAR = 1;
	static const int SECOND_GEAR = 2;
	static const int THIRD_GEAR = 3;
	static const int FOURTH_GEAR = 4;
	static const int FIFTH_GEAR = 5;

	bool IsTurnedOn() const;
	int GetSpeed() const;
	int GetGear() const;
	Direction GetDirection() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	struct SpeedRange { int min, max; };

	static inline const SpeedRange FIRST_GEAR_SPEED_RANGE = { 0, 30 };
	static inline const SpeedRange SECOND_GEAR_SPEED_RANGE = { 20, 50 };
	static inline const SpeedRange THIRD_GEAR_SPEED_RANGE = { 30, 60 };
	static inline const SpeedRange FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
	static inline const SpeedRange FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
	static inline const SpeedRange REVERSE_GEAR_SPEED_RANGE = { 0, 20 };
	static inline const SpeedRange CAR_SPEED_RANGE = { -REVERSE_GEAR_SPEED_RANGE.max, FIFTH_GEAR_SPEED_RANGE.max };
	static inline const std::map<int, Car::SpeedRange> GEAR_TO_SPEED_MAP = {
		{ Car::REVERSE_GEAR, Car::REVERSE_GEAR_SPEED_RANGE },
		{ Car::NEUTRAL_GEAR, Car::CAR_SPEED_RANGE },
		{ Car::FIRST_GEAR, Car::FIRST_GEAR_SPEED_RANGE },
		{ Car::SECOND_GEAR, Car::SECOND_GEAR_SPEED_RANGE },
		{ Car::THIRD_GEAR, Car::THIRD_GEAR_SPEED_RANGE },
		{ Car::FOURTH_GEAR, Car::FOURTH_GEAR_SPEED_RANGE },
		{ Car::FIFTH_GEAR, Car::FIFTH_GEAR_SPEED_RANGE },
	};

	bool IsSpeedInRange(int value, SpeedRange range) const;
	bool IsCarDirectionAllowsSetGear(int gear) const;
	std::optional<SpeedRange> GetGearSpeedRange(int gear) const;

	bool m_isTurnedOn = false;
	int m_speed = 0;
	int m_gear = 0;
};