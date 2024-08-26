#include "CTriangle.h"
#include "Color.h"
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

std::string CTriangle::ToString() const
{
	return std::format("triangle {} {} {} {} {} {} {} {}",
		m_vertex1.GetCoordinateX(),
		m_vertex1.GetCoordinateY(),
		m_vertex2.GetCoordinateX(),
		m_vertex2.GetCoordinateY(),
		m_vertex3.GetCoordinateX(),
		m_vertex3.GetCoordinateY(),
		GetHexStrFromUint32(GetFillColor()),
		GetHexStrFromUint32(GetOutlineColor())
	);
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

// move to common
double CTriangle::GetEdgeLength(CPoint const& p1, CPoint const& p2) const
{
	return std::sqrt(
		std::pow(p1.GetCoordinateX() - p2.GetCoordinateX(), 2) + std::pow(p1.GetCoordinateY() - p2.GetCoordinateY(), 2)
	);
}
