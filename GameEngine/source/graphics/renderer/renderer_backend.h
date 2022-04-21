#pragma once
//#include "./core/window/window.h"
//
//#include "./graphics/api/interface/render_device.h"
//#include "./graphics/api/interface/object/swapchain/swapchain.h"
//#include "./graphics/api/interface/object/command/command_queue.h"
//
//#include "./graphics/api/interface/object/sync/fence.h"
//#include "./graphics/api/interface/object/command/command_buffer.h"
namespace Graphics
{
	class RendererBackend
	{
	public: 
		static RendererBackend* Create(Window* _window);
		static void Destroy();
		
		static void SubmitCommandBuffer(CommandBuffer* _commandBuffer, Fence* _fence);

	private:
		RendererBackend(Window* _window);
		~RendererBackend();

		RenderDevice* m_RenderDevice = nullptr;
		Swapchain*    m_Swapchain    = nullptr;

		CommandQueue* m_CommandQueue = nullptr;
	};
}