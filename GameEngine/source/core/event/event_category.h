#pragma once
#define BIT(x) (1 << x)

enum EventCategory
{
	EVENT_CATEGORY_NONE			= BIT(0),
	EVENT_CATEGORY_WINDOW		= BIT(1),
	EVENT_CATEGORY_MOUSE		= BIT(2),
	EVENT_CATEGORY_KEYBOARD		= BIT(3)
};