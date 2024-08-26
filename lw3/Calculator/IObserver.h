#pragma once
#include <functional>

class IObserver
{
public:
	virtual void Update() = 0;

protected:
	~IObserver() = default;
};