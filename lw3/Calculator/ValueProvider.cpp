#include "ValueProvider.h"

double ValueProvider::GetValue() const
{
	return m_value;
}

void ValueProvider::Subscribe(IObserver* observer)
{
	m_observers.insert(observer);
}

void ValueProvider::NotifyObservers() const
{
	for (auto& observer : m_observers)
	{
		observer->Update();
	}
}
