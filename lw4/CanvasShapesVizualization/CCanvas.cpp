#include "CCanvas.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include <iostream>

CCanvas::CCanvas(sf::RenderTarget& renderTarget)
	: m_renderTarget(renderTarget)
{
}

void CCanvas::DrawLine(CPoint start, CPoint end, uint32_t color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f((float)start.GetCoordinateX(), (float)start.GetCoordinateY()), TransformColor(color)),
		sf::Vertex(sf::Vector2f((float)end.GetCoordinateX(), (float)end.GetCoordinateY()), TransformColor(color))
	};
	
	m_renderTarget.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor)
{
	sf::ConvexShape convex;
	convex.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		convex.setPoint(i, sf::Vector2f((float)points[i].GetCoordinateX(), (float)points[i].GetCoordinateY()));
	}

	convex.setFillColor(TransformColor(fillColor));
	m_renderTarget.draw(convex);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	sf::CircleShape shape((float)radius);
	shape.setOrigin((float)radius, (float)radius);
	shape.setPosition((float)center.GetCoordinateX(), (float)center.GetCoordinateY());
	shape.setOutlineThickness(2);
	shape.setOutlineColor(TransformColor(lineColor));
	m_renderTarget.draw(shape);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	sf::CircleShape shape((float)radius);
	shape.setOrigin((float)radius, (float)radius);
	shape.setPosition((float)center.GetCoordinateX(), (float)center.GetCoordinateY());
	shape.setFillColor(TransformColor(fillColor));
	m_renderTarget.draw(shape);
}

sf::Color CCanvas::TransformColor(uint32_t color) const
{
	return sf::Color((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
}
