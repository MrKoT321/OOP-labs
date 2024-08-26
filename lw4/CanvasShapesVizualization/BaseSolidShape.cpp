#include "BaseSolidShape.h"
#include <format>
#include "Common.h"

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

std::string BaseSolidShape::ToString() const
{
	return std::format("{} {} {}",
		GetShapeInfo(),
		GetHexStrFromUint32(GetFillColor()),
		GetHexStrFromUint32(GetOutlineColor())
	);
}
