#pragma once
#include "CPoint.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint start, CPoint end, uint32_t color) = 0;
	virtual void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
	virtual ~ICanvas() = default;	
};