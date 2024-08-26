#include "CCircle.h"
#include "Common.h"
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

std::string CCircle::GetShapeInfo() const
{
    return std::format("circle {} {} {}",
        m_center.GetCoordinateX(),
        m_center.GetCoordinateY(),
        m_radius
    );
}

void CCircle::Draw(ICanvas& canvas) const
{
    canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
    canvas.FillCircle(m_center, m_radius, GetFillColor());
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}
