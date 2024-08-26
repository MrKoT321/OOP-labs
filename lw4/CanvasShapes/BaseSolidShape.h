#pragma once
#include "ISolidShape.h"

class BaseSolidShape
	: public ISolidShape
{
public:
	BaseSolidShape(uint32_t fillColor, uint32_t outlineColor);

	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;

private:
	uint32_t m_fillColor = 0;
	uint32_t m_outlineColor = 0;
};