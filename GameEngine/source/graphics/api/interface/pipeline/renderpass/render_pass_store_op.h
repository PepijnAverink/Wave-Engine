#pragma once

namespace Graphics
{
	enum RenderPassStoreOp
	{
		RENDER_PASS_STORE_OP_NONE	   = 0x00,
		RENDER_PASS_STORE_OP_ERROR	   = 0x01,
		RENDER_PASS_STORE_OP_STORE	   = 0x02,
		RENDER_PASS_STORE_OP_DONT_CARE = 0x03,
	};
}