#pragma once
//#include "./graphics/api/interface/render_device.h"
//#include "./graphics/api/interface/object/command/command_queue_type.h"

// If running on windows define windows specific VK implementation

#include <vulkan/vulkan.h>


namespace Graphics
{
	class VKRenderDevice final : public RenderDevice
	{
	public:
		VKRenderDevice(const RenderDeviceDescriptor* _renderDeviceDescriptor);
		~VKRenderDevice();

		inline VkInstance GetVKInstance() const { return m_Instance; }
		inline VkSurfaceKHR GetVKSurface() const { return m_Surface; }

		inline VkPhysicalDevice GetPhysicalDevice() const{ return m_PhysicalDevice; }
		inline VkDevice GetDevice() const { return m_Device; }

		inline uint32_t GetPresentQueueID() const { return m_PresentQueueID; }
		inline uint32_t GetGraphicsQueueID() const { return m_GraphicsQueueID; }

		uint32_t GetQueueFamilyID(const CommandQueueType _type) const;

		virtual CommandPool* CreateCommandPool(const CommandPoolDescriptor* _commandPoolDescriptor) override;
		virtual CommandBuffer* CreateCommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor) override;
		virtual CommandQueue* CreateCommandQueue(const CommandQueueDescriptor* _commandQueueDescriptor) override;
		virtual Swapchain* CreateSwapchain(CommandQueue* _commandQueue, const SwapchainDescriptor* _swapchainDescriptor) override;
		virtual Fence* CreateFence(const FenceDescriptor* _fenceDescriptor) override;

		virtual GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;
		virtual InputLayout* CreateInputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor) override;
		virtual RenderPass* CreateRenderPass(const RenderPassDescriptor* _renderPassDescriptor) override;
		virtual FrameBuffer* CreateFrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor) override;

		virtual DescriptorPool* CreateDescriptorPool(const DescriptorPoolDescriptor* _descriptorPoolDescriptor) override;

		virtual Buffer* CreateBuffer(const BufferDescriptor* _bufferDescriptor) override;
		virtual Shader* CreateShader(const ShaderDescriptor* _shaderDescriptor) override;

		virtual Texture2D* CreateTexture2D(const Texture2DDescriptor* _texture2DDescriptor) override;
		virtual Sampler2D* CreateSampler2D(const Sampler2DDescriptor* _sampler2DDescripotr) override;

	private:
		bool CheckValidationLayerSupport();
		void GetVKPhysicalDevice();

		// Per application state is stored in the VK_Instance object
		// Used to initialize vulkan, should be deleted after everything else is freed
		VkInstance m_Instance;

		VkDebugUtilsMessengerEXT m_DebugMessenger;

		VkSurfaceKHR m_Surface;

		VkDevice m_Device;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

		uint32_t m_PresentQueueID = 0;
		uint32_t m_GraphicsQueueID = 0;
	};
}