#pragma once

namespace Graphics
{
	enum CullMode
	{
		CULL_MODE_NONE  = 0x00,
		CULL_MODE_ERROR = 0x01,
		CULL_MODE_FRONT = 0x02,
		CULL_MODE_BACK  = 0x03,
	};
}