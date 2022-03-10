#pragma once

namespace Graphics
{
	enum ResourceState
	{
		RESOURCE_STATE_NONE			= 0x00,
		RESOURCE_STATE_ERROR		= 0x01,
		RESOURCE_STATE_GENERAL_READ = 0x02,
		RESOURCE_STATE_PRESENT		= 0x03,
	};
}