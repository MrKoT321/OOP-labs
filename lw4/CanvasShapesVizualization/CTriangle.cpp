#include "CTriangle.h"
#include "Common.h"
#include <cmath>
#include <format>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor)
	: BaseSolidShape(fillColor, outlineColor)
{
	if ((vertex3.GetCoordinateX() - vertex1.GetCoordinateX()) * (vertex2.GetCoordinateY() - vertex1.GetCoordinateY()) ==
		(vertex2.GetCoordinateX() - vertex1.GetCoordinateX()) * (vertex3.GetCoordinateY() - vertex1.GetCoordinateY()))
	{
		throw std::runtime_error("Triangle points must not lie in a straight line");
	}

	m_vertex1 = vertex1;
	m_vertex2 = vertex2;
	m_vertex3 = vertex3;
}

double CTriangle::GetArea() const
{
	return std::abs(0.5 * (m_vertex1.GetCoordinateX() - m_vertex3.GetCoordinateX()
		* (m_vertex2.GetCoordinateY() - m_vertex3.GetCoordinateY())
		- (m_vertex2.GetCoordinateX() - m_vertex3.GetCoordinateX())
		* (m_vertex1.GetCoordinateY() - m_vertex3.GetCoordinateY())));
}

double CTriangle::GetPerimeter() const
{
	return GetEdgeLength(m_vertex1, m_vertex2) + GetEdgeLength(m_vertex1, m_vertex3) + GetEdgeLength(m_vertex3, m_vertex2);
}

std::string CTriangle::GetShapeInfo() const
{
	return std::format("triangle {} {} {} {} {} {}",
		m_vertex1.GetCoordinateX(),
		m_vertex1.GetCoordinateY(),
		m_vertex2.GetCoordinateX(),
		m_vertex2.GetCoordinateY(),
		m_vertex3.GetCoordinateX(),
		m_vertex3.GetCoordinateY()
	);
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({
		m_vertex1,
		m_vertex2,
		m_vertex3
		}, GetFillColor());
	canvas.DrawLine(m_vertex1, m_vertex2, GetOutlineColor());
	canvas.DrawLine(m_vertex1, m_vertex3, GetOutlineColor());
	canvas.DrawLine(m_vertex3, m_vertex2, GetOutlineColor());

}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
