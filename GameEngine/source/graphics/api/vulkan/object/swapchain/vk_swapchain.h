#pragma once
//#include "./graphics/api/interface/object/swapchain/swapchain.h"
//#include "./graphics/api/vulkan/vk_render_device.h"
//
//#include <vector>

namespace Graphics
{
	class CommandQueue;
	class VKSwapchain final : public Swapchain
	{
	public:
		VKSwapchain(VKRenderDevice* _renderDevice, CommandQueue* _commandQueue, const SwapchainDescriptor* _swapchainDescriptor);
		virtual ~VKSwapchain();

		virtual void Resize(CommandQueue* _commandQueue, const uint32_t _width, const uint32_t _height) override;

		virtual uint32_t AquireNewImage(CommandQueue* _commandQueue, Fence* _fence) override;
		virtual void Present(CommandQueue* _commandQueue) override;

		inline VkSwapchainKHR GetVKSwapchain() const { return m_SwapChainObj; }

	private:
		void CreateSwapchain(VKRenderDevice* _renderDevice, CommandQueue* _commandQueue);

		VkSwapchainKHR m_SwapChainObj;
	};
}