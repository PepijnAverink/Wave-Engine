#pragma once

namespace Graphics
{
	enum ResourceBindFlags
	{
		RESOURCE_BIND_FLAGS_NONE = 0x00,
		RESOURCE_BIND_FLAGS_SRV  = 0x01,
		RESOURCE_BIND_FLAGS_RTV  = 0x02,
		RESOURCE_BIND_FLAGS_DSV  = 0x04,
		RESOURCE_BIND_FLAGS_UAV  = 0x08,
	};
}