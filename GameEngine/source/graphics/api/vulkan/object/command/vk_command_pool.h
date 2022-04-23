#pragma once
//#include "./graphics/api/interface/object/command/command_pool.h"
//#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKCommandPool final : public CommandPool
	{
	public:
		VKCommandPool(VKRenderDevice* _renderDevice, const CommandPoolDescriptor* _commandPoolDescriptor);
		virtual ~VKCommandPool();

		virtual void Reset() override;

		inline VkCommandPool GetVKCommandPool() const { return m_CommandPoolObj; }

	private:
		VkCommandPool m_CommandPoolObj;
	};
}