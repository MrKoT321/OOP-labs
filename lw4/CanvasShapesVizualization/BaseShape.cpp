#include "BaseShape.h"
#include <format>
#include "Common.h"

BaseShape::BaseShape(uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

uint32_t BaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string BaseShape::ToString() const
{
    return std::format("{} {}",
        GetShapeInfo(),
        GetHexStrFromUint32(GetOutlineColor())
    );
}
