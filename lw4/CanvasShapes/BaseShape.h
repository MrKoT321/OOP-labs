#pragma once
#include "IShape.h"

class BaseShape
	: public IShape
{
public:
	BaseShape(uint32_t outlineColor);

	uint32_t GetOutlineColor() const override;

private:
	uint32_t m_outlineColor = 0;
};