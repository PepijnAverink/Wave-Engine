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

	uint32_t RendererBackend::AquireNewFrame(Fence* _fence)
	{
		return s_RenderBackend->m_Swapchain->AquireNewImage(s_RenderBackend->m_CommandQueue, _fence);
	}

	void RendererBackend::Present()
	{
		s_RenderBackend->m_Swapchain->Present(s_RenderBackend->m_CommandQueue);
	}

	void RendererBackend::Resize(const uint32_t _width, const uint32_t _height)
	{
		s_RenderBackend->m_Swapchain->Resize(s_RenderBackend->m_CommandQueue, _width, _height);
		s_RenderBackend->m_ClientWidth  = s_RenderBackend->m_Swapchain->GetWidth();
		s_RenderBackend->m_ClientHeight = s_RenderBackend->m_Swapchain->GetHeight();
	}

	uint32_t RendererBackend::GetClientWidth()
	{
		return s_RenderBackend->m_ClientWidth;
	}

	uint32_t RendererBackend::GetClientHeight()
	{
		return s_RenderBackend->m_ClientHeight;
	}

	uint32_t RendererBackend::GetBackbufferCount()
	{
		return s_RenderBackend->m_BackbufferCount;
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

		// Create swapchain and query dimensions
		m_Swapchain    = m_RenderDevice->CreateSwapchain(m_CommandQueue, &swapchainDesc);
		m_ClientWidth  = m_Swapchain->GetWidth();
		m_ClientHeight = m_Swapchain->GetHeight();
		m_BackbufferCount = m_Swapchain->GetBufferCount();
	}

	RendererBackend::~RendererBackend()
	{
		delete m_Swapchain;
		delete m_CommandQueue;
		delete m_RenderDevice;
	}
}