#pragma once
#include "./graphics/api/interface/object/command/command_queue_type.h"

#include <string>
namespace Graphics
{
	class CommandQueueDescriptor
	{
	public:
		CommandQueueDescriptor() = default;

		std::string      Name;
		CommandQueueType Type = CommandQueueType::COMMAND_QUEUE_TYPE_NONE;
	};
}