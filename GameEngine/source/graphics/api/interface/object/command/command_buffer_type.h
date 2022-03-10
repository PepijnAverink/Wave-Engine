#pragma once

namespace Graphics
{
	enum CommandBufferType
	{
		COMMAND_BUFFER_TYPE_NONE     = 0x00,
		COMMAND_BUFFER_TYPE_ERROR    = 0x01,
		COMMAND_BUFFER_TYPE_DIRECT   = 0x02,
		COMMAND_BUFFER_TYPE_INDIRECT = 0x03,
		COMMAND_BUFFER_TYPE_COMPUTE  = 0x04,
		COMMAND_BUFFER_TYPE_COPY     = 0x05,
	};
}