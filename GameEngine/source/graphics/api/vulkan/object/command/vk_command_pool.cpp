#include "./graphics/api/vulkan/object/command/vk_command_pool.h"
#include "./core/logger.h"

namespace Graphics
{
	VKCommandPool::VKCommandPool(VKRenderDevice* _renderDevice, const CommandPoolDescriptor* _commandPoolDescriptor)
		: CommandPool(_commandPoolDescriptor)
	{
		// Craetion info
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = _renderDevice->GetQueueFamilyID(_commandPoolDescriptor->Type);
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		// Create CommandPool
		if (vkCreateCommandPool(_renderDevice->GetDevice(), &poolInfo, nullptr, &m_CommandPoolObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'CommandPool' object.", LogType::LOG_TYPE_ERROR);
	}

	VKCommandPool::~VKCommandPool()
	{
		vkDestroyCommandPool(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_CommandPoolObj, nullptr);
	}

	void VKCommandPool::Reset()
	{
		vkResetCommandPool(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_CommandPoolObj, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	}
}