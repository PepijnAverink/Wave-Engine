#pragma once
#include "./core/event/event.h"

class WindowResizeEvent final : public Event
{
public:
	WindowResizeEvent(const uint32_t _width, const uint32_t _height)
		: m_Width(_width)
		, m_Height(_height)
	{}

	inline uint32_t GetWidth()  const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }

	static  EventType GetStaticType() { return EventType::EVENT_TYPE_WINDOW_RESIZE; }
	virtual EventType  GetEventType() const { return GetStaticType(); }

	virtual const char* GetName()  const { return "WINDOW_RESIZE_EVENT"; }
	virtual int GetCategoryFlags() const { return (EVENT_CATEGORY_WINDOW); }

private:
	uint32_t m_Width;
	uint32_t m_Height;
};