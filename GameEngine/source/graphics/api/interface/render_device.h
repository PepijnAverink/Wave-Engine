#pragma once
#include "./graphics/api/interface/render_device_descriptor.h"
//#include "graphics/api/graphics_api.h"
//#include "graphics/api/interface/debug_mode.h"
class Window;
namespace Graphics
{
	class RenderDeviceDescriptor;
	class CommandPool;
	class CommandPoolDescriptor;
	class CommandBuffer;
	class CommandBufferDescriptor;
	class CommandQueue;
	class CommandQueueDescriptor;
	class Swapchain;
	class SwapchainDescriptor;
	class Fence;
	class FenceDescriptor;

	class GraphicsPipeline;
	class GraphicsPipelineDescriptor;
	class InputLayout;
	class InputLayoutDescriptor;
	class RenderPass;
	class RenderPassDescriptor;
	class FrameBuffer;
	class FrameBufferDescriptor;

	class DescriptorPool;
	class DescriptorPoolDescriptor;
	class DescriptorSet;
	class DescriptorSetDescriptor;

	class Buffer;
	class BufferDescriptor;
	class Shader;
	class ShaderDescriptor;
	class RenderDevice
	{
	public:
		static RenderDevice* Create(const RenderDeviceDescriptor* _renderDeviceDescriptor);
		virtual ~RenderDevice();

		// Get singleton instance
		static RenderDevice* GetInstance();

		virtual CommandPool* CreateCommandPool(const CommandPoolDescriptor* _commandPoolDescriptor) = 0;
		virtual CommandBuffer* CreateCommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor) = 0;
		virtual CommandQueue* CreateCommandQueue(const CommandQueueDescriptor* _commandQueueDescriptor) = 0;
		virtual Swapchain* CreateSwapchain(CommandQueue* _commandQueue, const SwapchainDescriptor* _swapchainDescriptor) = 0;
		virtual Fence* CreateFence(const FenceDescriptor* _fenceDescriptor) = 0;

		virtual GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) = 0;
		virtual InputLayout* CreateInputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor) = 0;
		virtual RenderPass* CreateRenderPass(const RenderPassDescriptor* _renderPassDescriptor) = 0;
		virtual FrameBuffer* CreateFrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor) = 0;

		virtual DescriptorPool* CreateDescriptorPool(const DescriptorPoolDescriptor* _descriptorPoolDescriptor) = 0;

		virtual Buffer* CreateBuffer(const BufferDescriptor* _bufferDescriptor) = 0;
		virtual Shader* CreateShader(const ShaderDescriptor* _shaderDescriptor) = 0;

	protected:
		RenderDevice(const RenderDeviceDescriptor* _renderDeviceDescriptor);

		// API
		GraphicsAPI m_API = GraphicsAPI::GRAPHICS_API_NONE;

		// DebugMode
		// Set's the DebugEnabled according to the DebugMode
		bool m_DebugEnabled   = false;
		DebugMode m_DebugMode = DebugMode::DEBUG_MODE_NONE;
		void CorrectDebugMode();

	};
}