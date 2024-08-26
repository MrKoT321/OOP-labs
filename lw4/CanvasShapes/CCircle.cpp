#include "CCircle.h"
#include "Color.h"
#include <numbers>
#include <stdexcept>
#include <format>

CCircle::CCircle(CPoint const& center, double radius, uint32_t fillColor, uint32_t outlineColor)
    : BaseSolidShape(fillColor, outlineColor)
{
    if (radius <= 0)
    {
        throw std::runtime_error("Radius should be more than 0");
    }

    m_center = center;
    m_radius = radius;
}

double CCircle::GetArea() const
{
    return std::numbers::pi * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * std::numbers::pi * m_radius;
}

std::string CCircle::ToString() const
{
    return std::format("circle {} {} {} {} {}",
        m_center.GetCoordinateX(),
        m_center.GetCoordinateY(),
        m_radius,
        GetHexStrFromUint32(GetFillColor()),
        GetHexStrFromUint32(GetOutlineColor())
    );
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}
