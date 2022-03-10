#include "./graphics/api/interface/object/command/command_pool.h"

namespace Graphics
{
	CommandPool::CommandPool(const CommandPoolDescriptor* _commandPoolDescriptor)
		: m_Type(_commandPoolDescriptor->Type)
	{ }

	CommandPool::~CommandPool()
	{

	}
}