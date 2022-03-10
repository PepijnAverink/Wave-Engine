#pragma once

namespace Graphics
{
	enum ShaderTypeFlag
	{
		SHADER_TYPE_FLAG_NONE   = 0x00,
		SHADER_TYPE_FLAG_ERROR  = 0x01,
		SHADER_TYPE_FLAG_VERTEX = 0x02,
		SHADER_TYPE_FLAG_PIXEL  = 0x04,
		SHADER_TYPE_FLAG_ALL    = 0x08,
	};
}