#pragma once
#include "./core/event/event.h"

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event& _event)
		: m_Event(_event)
	{ }

	template<typename T>
	bool Dispatch(EventFn<T> _function)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handled = _function(*(T*)&m_Event);
			return true;
		}
		return false;
	}

private:
	Event& m_Event;
};