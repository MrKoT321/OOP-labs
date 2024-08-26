#pragma once

class CPoint
{
public:
	CPoint() = default;
	CPoint(double x, double y);

	double GetCoordinateX() const;
	double GetCoordinateY() const;

	bool operator==(CPoint const&) const = default;

private:
	double m_x = 0.0;
	double m_y = 0.0;
};