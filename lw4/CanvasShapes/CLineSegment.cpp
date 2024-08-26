#include "CLineSegment.h"
#include <cmath>
#include <format>
#include "Color.h"

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

std::string CLineSegment::ToString() const
{
    return std::format("line {} {} {} {} {}",
        m_startPoint.GetCoordinateX(),
        m_startPoint.GetCoordinateY(),
        m_endPoint.GetCoordinateX(),
        m_endPoint.GetCoordinateY(),
        GetHexStrFromUint32(GetOutlineColor())
    );
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

double CLineSegment::GetEdgeLength(CPoint const& p1, CPoint const& p2) const
{
    return std::sqrt(
        std::pow(p1.GetCoordinateX() - p2.GetCoordinateX(), 2) + std::pow(p1.GetCoordinateY() - p2.GetCoordinateY(), 2)
    );
}
