#include "BaseShape.h"

BaseShape::BaseShape(uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

uint32_t BaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}
