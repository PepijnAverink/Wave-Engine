#pragma once

namespace Graphics
{
	enum RenderPassLoadOp
	{
		RENDER_PASS_LOAD_OP_NONE      = 0x00,
		RENDER_PASS_LOAD_OP_ERROR     = 0x01,
		RENDER_PASS_LOAD_OP_LOAD      = 0x02,
		RENDER_PASS_LOAD_OP_CLEAR     = 0x03,
		RENDER_PASS_LOAD_OP_DONT_CARE = 0x04,
	};
}