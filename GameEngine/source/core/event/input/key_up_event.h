#pragma once
#include "./core/event/event.h"

class KeyUpEvent final : public Event
{
public:
	KeyUpEvent(const uint8_t _key, const uint32_t _info)
		: m_Key(_key), m_Info(_info)

	{}



	inline uint8_t GetKey()  const { return m_Key; }
	inline uint32_t GetInfo() const { return m_Info; }
	//inline bool isPressed() const { return HIWORD(m_Info) & KF_REPEAT == KF_REPEAT; } // TODO: make it platform independent

	static  EventType GetStaticType() { return EventType::EVENT_TYPE_KEY_UP; }
	virtual EventType  GetEventType() const { return GetStaticType(); }

	virtual const char* GetName()  const { return "KEY_UP_EVENT"; }
	virtual int GetCategoryFlags() const { return (EVENT_CATEGORY_KEYBOARD); }

private:
	uint8_t m_Key;
	uint32_t m_Info;
};
