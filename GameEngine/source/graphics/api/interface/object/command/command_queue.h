#pragma once
#include "./graphics/api/interface/object/command/command_queue_descriptor.h"
#include "./graphics/api/interface/object/command/command_queue_support_bit.h"

namespace Graphics
{
	class CommandBuffer;
	class Fence;
	class CommandQueue
	{
	public:
		CommandQueue(const CommandQueueDescriptor* _commandQueueDescriptor);
		virtual ~CommandQueue();

		virtual void SubmitCommandBuffer(CommandBuffer* _commandBuffer, Fence* _fence) = 0;

		inline bool CheckSupportFlag(uint32_t _flag) const { return (m_SupportFlags & _flag); }

	protected:
		// Functionality for support flags
		inline void AddSupportFlag(uint32_t _flag)        { m_SupportFlags &= _flag; }
		inline void RemoveSupportFlag(uint32_t _flag) { m_SupportFlags &= ~_flag; }
		uint32_t m_SupportFlags = COMMAND_QUEUE_SUPPORT_BIT_NONE;
	};
}