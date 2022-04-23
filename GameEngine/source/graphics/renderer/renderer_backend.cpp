//#include "./graphics/renderer/renderer_backend.h"
#include "core/stdafx.h"
namespace Graphics
{
	// Static instance
	static RendererBackend* s_RenderBackend = nullptr;

	RendererBackend* RendererBackend::Create(Window* _window)
	{
		s_RenderBackend = new RendererBackend(_window);
		return s_RenderBackend;
	}

	void RendererBackend::Destroy()
	{
		delete s_RenderBackend;
	}

	void RendererBackend::SubmitCommandBuffer(CommandBuffer* _commandBuffer, Fence* _fence)
	{
		s_RenderBackend->m_CommandQueue->SubmitCommandBuffer(_commandBuffer, _fence);
	}

	RendererBackend::RendererBackend(Window* _window)
	{
		// RenderDevice
		// --------------------------------------------------------------------
		RenderDeviceDescriptor renderDeviceDesc;
		renderDeviceDesc.Window    = _window;
		renderDeviceDesc.API	   = GraphicsAPI::GRAPHICS_API_VULKAN;
		renderDeviceDesc.DebugMode = DebugMode::DEBUG_MODE_DEBUG_ONLY;

		m_RenderDevice = RenderDevice::Create(&renderDeviceDesc);

		// CommandQueue
		// --------------------------------------------------------------------
		Graphics::CommandQueueDescriptor commandQueueDesc;
		commandQueueDesc.Name = "GeneralCommandQueue";
		commandQueueDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

		m_CommandQueue = m_RenderDevice->CreateCommandQueue(&commandQueueDesc);

		// Swapchain
		// --------------------------------------------------------------------
		SwapchainDescriptor swapchainDesc;
		swapchainDesc.Name   = "Swapchain";
		swapchainDesc.Window = _window;
		swapchainDesc.Width  = _window->GetWidth();
		swapchainDesc.Height = _window->GetHeight();

		m_Swapchain = m_RenderDevice->CreateSwapchain(m_CommandQueue, &swapchainDesc);
	}

	RendererBackend::~RendererBackend()
	{
		delete m_Swapchain;
		delete m_CommandQueue;
		delete m_RenderDevice;
	}
}