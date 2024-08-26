#pragma once
#include "BaseShape.h"
#include "CPoint.h"

class CLineSegment
	: public BaseShape
{
public:
	CLineSegment(CPoint const& p1, CPoint const& p2, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	double GetEdgeLength(CPoint const& p1, CPoint const& p2) const;

	CPoint m_startPoint;
	CPoint m_endPoint;
};