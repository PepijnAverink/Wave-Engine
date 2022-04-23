#pragma once
#include "./graphics/api/interface/object/command/command_pool_descriptor.h"

namespace Graphics
{
    
	class CommandPool
	{
	public:
		CommandPool(const CommandPoolDescriptor* _commandPoolDescriptor);
		virtual ~CommandPool();

		virtual void Reset() = 0;

	protected:
		CommandQueueType m_Type = CommandQueueType::COMMAND_QUEUE_TYPE_NONE;
	};
}