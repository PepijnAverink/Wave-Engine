#pragma once

namespace Graphics
{
	enum class BufferUsage
	{
		BUFFER_USAGE_NONE           = 0x00,
		BUFFER_USAGE_ERROR          = 0x01,
		BUFFER_USAGE_VERTEX_BUFFER  = 0x02,
		BUFFER_USAGE_INDEX_BUFFER   = 0x03,
		BUFFER_USAGE_STAGING_BUFFER = 0x04,
		BUFFER_USAGE_UNIFORM_BUFFER = 0x05,
	};
}