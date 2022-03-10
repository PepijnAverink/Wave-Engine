#pragma once
#define BIT(x) (1 << x)

enum EventCategory
{
	EVENT_CATEGORY_NONE			= BIT(0),
	EVENT_CATEGORY_WINDOW		= BIT(1),
};