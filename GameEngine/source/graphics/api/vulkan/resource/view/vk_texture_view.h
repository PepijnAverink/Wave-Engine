#pragma once
#include "./graphics/api/interface/resource/view/texture_view.h"
#include "./graphics/api/vulkan/vk_render_device.h"

#include "./graphics/api/vulkan/resource/texture/vk_texture2D.h"

namespace Graphics
{
	class VKTextureView final : public TextureView
	{
	public:
		VKTextureView(VKRenderDevice* _renderDevice, VKTexture2D* _texture, const TextureViewDescriptor* _TextureViewDescriptor);
		virtual ~VKTextureView();
		
		inline VkImageView GetVKTextureView() const { return m_ImageViewObj; }

	private:
		VkImageView m_ImageViewObj;
	};
}