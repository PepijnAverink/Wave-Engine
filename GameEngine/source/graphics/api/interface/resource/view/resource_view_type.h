#pragma once

namespace Graphics
{
	enum ResourceViewState
	{
		RESOURCE_VIEW_STATE_NONE = 0x00,
		RESOURCE_VIEW_STATE_SRV  = 0x01,
		RESOURCE_VIEW_STATE_RTV  = 0x02,
		RESOURCE_VIEW_STATE_DSV  = 0x03,
		RESOURCE_VIEW_STATE_UAV  = 0x04,
	};
}