#pragma once
#include "BaseSolidShape.h"
#include "CPoint.h"

class CTriangle
	: public BaseSolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	double GetEdgeLength(CPoint const& p1, CPoint const& p2) const;

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};