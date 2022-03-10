#pragma once

namespace Graphics
{
	// Enables the debug layer depending on this structure
	enum DebugMode
	{
		DEBUG_MODE_NONE       = 0x00,
		DEBUG_MODE_ALWAYS     = 0x01,
		DEBUG_MODE_NEVER      = 0x02,
		DEBUG_MODE_DEBUG_ONLY = 0x03,
	};
}