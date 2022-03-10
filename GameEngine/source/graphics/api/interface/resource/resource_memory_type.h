#pragma once

namespace Graphics
{
	enum ResourceMemoryType
	{
		RESOURCE_MEMORY_TYPE_NONE		   = 0x00,
		RESOURCE_MEMORY_TYPE_ERROR		   = 0x01,
		RESOURCE_MEMORY_TYPE_HOST_MEMORY   = 0x02,
		RESOURCE_MEMORY_TYPE_DEVICE_MEMORY = 0x03,
	};
}