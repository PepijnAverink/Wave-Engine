#pragma once
#include "./core/event/event_category.h"
#include "./core/event/event_type.h"

#include <string>
#include <functional>

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

class Event
{
public:
	virtual ~Event() = default;

	bool Handled = false;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int   GetCategoryFlags() const = 0;
	virtual   std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory _category) { return GetCategoryFlags() & _category; }
};

using EventCallbackFn = std::function<void(Event&)>;