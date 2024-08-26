#include "CRectangle.h"
#include "Common.h"
#include <format>

CRectangle::CRectangle(CPoint const& p1, CPoint const& p2, uint32_t fillColor, uint32_t outlineColor)
    : BaseSolidShape(fillColor, outlineColor)
{
    double leftTopX = std::min(p1.GetCoordinateX(), p2.GetCoordinateX());
    double leftTopY = std::min(p1.GetCoordinateY(), p2.GetCoordinateY());
    double rightBottomX = std::max(p1.GetCoordinateX(), p2.GetCoordinateX());
    double rightBottomY = std::max(p1.GetCoordinateY(), p2.GetCoordinateY());

    m_leftTop = CPoint(leftTopX, leftTopY);
    m_rightBottom = CPoint(rightBottomX, rightBottomY);
}

double CRectangle::GetArea() const
{
    return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
    return 2 * (GetWidth() + GetHeight());
}

std::string CRectangle::GetShapeInfo() const
{
    return std::format("rectangle {} {} {} {}",
        m_leftTop.GetCoordinateX(),
        m_leftTop.GetCoordinateY(),
        GetWidth(),
        GetHeight()
    );
}

void CRectangle::Draw(ICanvas& canvas) const
{
    canvas.FillPolygon({
        m_leftTop,
        { m_leftTop.GetCoordinateX(), m_rightBottom.GetCoordinateY()},
        m_rightBottom,
        { m_rightBottom.GetCoordinateX(), m_leftTop.GetCoordinateY()}
        }, GetFillColor());
    canvas.DrawLine(m_leftTop, CPoint(m_rightBottom.GetCoordinateX(), m_leftTop.GetCoordinateY()), GetOutlineColor());
    canvas.DrawLine(CPoint(m_rightBottom.GetCoordinateX(), m_leftTop.GetCoordinateY()), m_rightBottom, GetOutlineColor());
    canvas.DrawLine(m_rightBottom, CPoint(m_leftTop.GetCoordinateX(), m_rightBottom.GetCoordinateY()), GetOutlineColor());
    canvas.DrawLine(CPoint(m_leftTop.GetCoordinateX(), m_rightBottom.GetCoordinateY()), m_leftTop, GetOutlineColor());
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
    return m_rightBottom;
}

double CRectangle::GetWidth() const
{
    return m_rightBottom.GetCoordinateX() - m_leftTop.GetCoordinateX();
}

double CRectangle::GetHeight() const
{
    return m_rightBottom.GetCoordinateY() - m_leftTop.GetCoordinateY();
}
