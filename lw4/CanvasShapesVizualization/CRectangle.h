#pragma once
#include "BaseSolidShape.h"
#include "CPoint.h"

class CRectangle
	: public BaseSolidShape
{
public:
	CRectangle(CPoint const& p1, CPoint const& p2, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetShapeInfo() const override;
	void Draw(ICanvas& canvas) const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};