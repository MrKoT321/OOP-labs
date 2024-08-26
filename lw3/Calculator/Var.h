#pragma once
#include "ValueProvider.h"

class Var :
	public ValueProvider
{
public:
	Var() = default;
	Var(double value);
	void SetValue(double value);
};