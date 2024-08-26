#pragma once
#include "ICanvas.h"
#include "SFML/Graphics/RenderWindow.hpp"

class CCanvas
	: public ICanvas
{
public:
	CCanvas(sf::RenderTarget& renderTarget);
	void DrawLine(CPoint start, CPoint end, uint32_t color) override;
	void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;

private:
	sf::Color TransformColor(uint32_t color) const;

	sf::RenderTarget& m_renderTarget;
};