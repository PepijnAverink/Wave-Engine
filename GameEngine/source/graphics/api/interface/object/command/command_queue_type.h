#pragma once

namespace Graphics
{
	enum class CommandQueueType
	{
		COMMAND_QUEUE_TYPE_NONE     = 0x00,
		COMMAND_QUEUE_TYPE_ERROR    = 0x01,
		COMMAND_QUEUE_TYPE_GRAPHICS = 0x02,
		COMMAND_QUEUE_TYPE_COMPUTE  = 0x03,
		COMMAND_QUEUE_TYPE_COPY		= 0x04,
	};
}