#include "CPoint.h"
#include <stdexcept>

CPoint::CPoint(double x, double y)
{
	if (x < 0 || y < 0)
	{
		throw std::runtime_error("Coordinates shuld be more than 0");
	}

	m_x = x;
	m_y = y;
}

double CPoint::GetCoordinateX() const
{
	return m_x;
}

double CPoint::GetCoordinateY() const
{
	return m_y;
}
