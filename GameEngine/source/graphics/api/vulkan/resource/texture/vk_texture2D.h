#pragma once
#include "./graphics/api/interface/resource/texture/texture2D.h"
#include "./graphics/api/vulkan/vk_render_device.h"
namespace Graphics
{
	class VKTexture2D final : public Texture2D
	{
	public:
		VKTexture2D(VKRenderDevice* _renderDevice, const Texture2DDescriptor* _texture2DDescriptor);
		VKTexture2D(VKRenderDevice* _renderDevice, VkImage _resource, const Texture2DDescriptor* _texture2DDescriptor);
		virtual ~VKTexture2D();

		inline VkImage GetVKTexture() const { return m_ImageObj; }

	private:
		uint32_t FindMemoryType(VKRenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		VkImage m_ImageObj;
		VkDeviceMemory m_BufferMemory;
	};
}