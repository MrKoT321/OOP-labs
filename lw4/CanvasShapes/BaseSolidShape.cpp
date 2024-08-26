#include "BaseSolidShape.h"

BaseSolidShape::BaseSolidShape(uint32_t fillColor, uint32_t outlineColor)
	: m_fillColor(fillColor), m_outlineColor(outlineColor)
{
}

uint32_t BaseSolidShape::GetFillColor() const
{
	return m_fillColor;
}

uint32_t BaseSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}
