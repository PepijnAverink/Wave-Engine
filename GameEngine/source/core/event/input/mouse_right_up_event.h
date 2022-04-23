#pragma once
#include "./core/event/event.h"

class MouseRightUpEvent final : public Event
{

public:
	MouseRightUpEvent(const int _x, const int _y)
		: m_X(_x), m_Y(_y)

	{}



	inline int GetX()  const { return m_X; }
	inline int GetY()  const { return m_Y; }




	static  EventType GetStaticType() { return EventType::EVENT_TYPE_RIGHT_BUTTON_UP; }
	virtual EventType  GetEventType() const { return GetStaticType(); }

	virtual const char* GetName()  const { return "MOUSE_RIGHT_UP_EVENT"; }
	virtual int GetCategoryFlags() const { return (EVENT_CATEGORY_MOUSE); }

private:
	int m_X, m_Y;

};
