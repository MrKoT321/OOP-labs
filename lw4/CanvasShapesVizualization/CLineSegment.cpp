#include "CLineSegment.h"
#include <cmath>
#include <format>
#include "Common.h"

CLineSegment::CLineSegment(CPoint const& p1, CPoint const& p2, uint32_t outlineColor)
    : m_startPoint(p1), m_endPoint(p2), BaseShape(outlineColor)
{
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    return GetEdgeLength(m_startPoint, m_endPoint);
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_startPoint, m_endPoint, GetOutlineColor());
}

std::string CLineSegment::GetShapeInfo() const
{
    return std::format("line {} {} {} {}",
        m_startPoint.GetCoordinateX(),
        m_startPoint.GetCoordinateY(),
        m_endPoint.GetCoordinateX(),
        m_endPoint.GetCoordinateY());
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

