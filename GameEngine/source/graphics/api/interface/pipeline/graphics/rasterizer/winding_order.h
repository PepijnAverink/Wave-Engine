#pragma once

namespace Graphics
{
	enum WindingOrder
	{
		WINDING_ORDER_NONE  = 0x00,
		WINDING_ORDER_ERROR = 0x01,
		WINDING_ORDER_CW    = 0x02,
		WINDING_ORDER_CCW   = 0x03,
	};
}