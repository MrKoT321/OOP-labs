#pragma once
#include <set>
#include <memory>
#include "IObserver.h"

class ValueProvider
{
public:
	double GetValue() const;
	void Subscribe(IObserver* observer);
	virtual ~ValueProvider() = default;

protected:
	void NotifyObservers() const;
	double m_value = NAN;

private:
	std::set<IObserver*> m_observers;
	
};  