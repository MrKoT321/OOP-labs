#include "Car.h"

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

Direction Car::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	if (m_speed < 0)
	{
		return Direction::Backward;
	}
	return Direction::Standing;
}

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;
	return m_isTurnedOn;
}

bool Car::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == NEUTRAL_GEAR)
	{
		m_isTurnedOn = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{
	if (gear == m_gear)
	{
		return true;
	}

	if (!m_isTurnedOn)
	{
		return false;
	}

	std::optional gearSpeedRange = Car::GetGearSpeedRange(gear);
	if (!gearSpeedRange.has_value())
	{
		return false;
	}
	if (!Car::IsSpeedInRange(m_speed, gearSpeedRange.value()) || !Car::IsCarDirectionAllowsSetGear(gear))
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isTurnedOn)
	{
		return false;
	}

	auto gearSpeedRange = Car::GetGearSpeedRange(m_gear);
	if (!gearSpeedRange.has_value())
	{
		return false;
	}
	if (!Car::IsSpeedInRange(speed, gearSpeedRange.value()))
	{
		return false;
	}
	if (m_gear == NEUTRAL_GEAR && speed > abs(m_speed))
	{
		return false;	
	}
	bool isCarWillMoveBackward = m_gear == Car::REVERSE_GEAR || Car::GetDirection() == Direction::Backward;
	m_speed = isCarWillMoveBackward ? -speed : speed;

	return true;
}

bool Car::IsSpeedInRange(int value, SpeedRange range) const
{
	return value >= range.min && value <= range.max;
}

bool Car::IsCarDirectionAllowsSetGear(int gear) const
{
	const Direction direction = Car::GetDirection();
	if (gear >= Car::FIRST_GEAR)
	{
		return direction != Direction::Backward;
	}
	if (gear == Car::REVERSE_GEAR)
	{
		return direction == Direction::Standing;
	}
	return true;
}

std::optional<Car::SpeedRange> Car::GetGearSpeedRange(int gear) const
{
	if (gear < Car::REVERSE_GEAR || gear > Car::FIFTH_GEAR)
	{
		return std::nullopt;
	}
	auto gearToSpeedMap = Car::GEAR_TO_SPEED_MAP;
	return gearToSpeedMap[gear];
}