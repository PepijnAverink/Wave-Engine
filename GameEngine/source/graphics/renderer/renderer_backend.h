#pragma once

namespace Graphics
{
	class RendererBackend
	{
	public: 
		static RendererBackend* Create(Window* _window);
		static void Destroy();
		
		static void SubmitCommandBuffer(CommandBuffer* _commandBuffer, Fence* _fence);

		static uint32_t AquireNewFrame(Fence* _fence);
		static void Present();

		static void Resize(const uint32_t _width, const uint32_t _height);
		static uint32_t GetClientWidth();
		static uint32_t GetClientHeight();
		static uint32_t GetBackbufferCount();

		// Probably delete these
		inline RenderDevice* GetRenderDevice() const { return m_RenderDevice; }
		inline Swapchain* GetSwapchain() const { return m_Swapchain; }
		
	private:
		RendererBackend(Window* _window);
		~RendererBackend();

		RenderDevice* m_RenderDevice = nullptr;
		CommandQueue* m_CommandQueue = nullptr;

		Swapchain* m_Swapchain = nullptr;
		uint32_t   m_ClientWidth  = 0;
		uint32_t   m_ClientHeight = 0;
		uint32_t   m_BackbufferCount = 0;
	};
}