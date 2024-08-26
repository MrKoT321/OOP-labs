#pragma once
#include "BaseSolidShape.h"
#include "CPoint.h"

class CCircle
	: public BaseSolidShape
{
public:
	CCircle(CPoint const& center, double radius, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};