#pragma once
#include "./core/event/event.h"

class MouseMoveEvent final : public Event
{
	enum State
	{
		NONE = 0x00,
		LEFT_BUTTON = 0x01,
		RIGHT_BUTTON = 0x02
	};
public:
	MouseMoveEvent(const int _x, const int _y, int _state)
		: m_X(_x), m_Y(_y)

	{
		switch (_state)
		{
		case 0:
			m_State = NONE;
			break;
		case 1:
			m_State = LEFT_BUTTON;
			break;
		case 2:
			m_State = RIGHT_BUTTON;
			break;
		}
	
	}



	inline int GetX()  const { return m_X; }
	inline int GetY()  const { return m_Y; }
	inline State GetState()  const { return m_State; }

	

	static  EventType GetStaticType() { return EventType::EVENT_TYPE_MOUSE_MOVE; }
	virtual EventType  GetEventType() const { return GetStaticType(); }

	virtual const char* GetName()  const { return "MOUSE_MOVE_EVENT"; }
	virtual int GetCategoryFlags() const { return (EVENT_CATEGORY_MOUSE); }

private:
	int m_X, m_Y;
	State m_State;
};