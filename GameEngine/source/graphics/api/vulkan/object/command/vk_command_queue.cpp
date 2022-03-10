#include "./graphics/api/vulkan/object/command/vk_command_queue.h"
#include "./graphics/api/vulkan/object/command/vk_command_buffer.h"
#include "./graphics/api/vulkan/object/sync/vk_fence.h"

namespace Graphics
{
	VKCommandQueue::VKCommandQueue(VKRenderDevice* _renderDevice, const CommandQueueDescriptor* _commandQueueDescriptor)
		: CommandQueue(_commandQueueDescriptor)
	{
		if (_commandQueueDescriptor->Type == CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS)
		{
			vkGetDeviceQueue(_renderDevice->GetDevice(), _renderDevice->GetGraphicsQueueID(), 0, &m_QueueObj);
			if (_renderDevice->GetGraphicsQueueID() == _renderDevice->GetPresentQueueID())
			{
				AddSupportFlag(COMMAND_QUEUE_SUPPORT_BIT_GRAPHICS);
				AddSupportFlag(COMMAND_QUEUE_SUPPORT_BIT_PRESENT);
			}
		}
	}

	VKCommandQueue::~VKCommandQueue()
	{ }

	void VKCommandQueue::SubmitCommandBuffer(CommandBuffer* _commandBuffer, Fence* _fence)
	{
		VkCommandBuffer cmbuffer = ((VKCommandBuffer*)_commandBuffer)->GetVKCommandBuffer();
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }; // TODO:: abstract this

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount	= 0;
		submitInfo.pWaitDstStageMask	= waitStages;
		submitInfo.commandBufferCount	= 1;
		submitInfo.pCommandBuffers		= &cmbuffer;
		submitInfo.signalSemaphoreCount = 0;

		if (vkQueueSubmit(m_QueueObj, 1, &submitInfo, ((VKFence*)_fence)->GetVKFence()) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to submit CommandBuffer.", LogType::LOG_TYPE_ERROR);
	}
}