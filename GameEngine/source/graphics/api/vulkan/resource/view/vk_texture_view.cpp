//#include "./graphics/api/vulkan/resource/view/vk_texture_view.h"
//#include "./graphics/api/vulkan/resource/vk_resource_format.h"
#include "core/stdafx.h"

namespace Graphics
{
	VKTextureView::VKTextureView(VKRenderDevice* _renderDevice, VKTexture2D* _texture, const TextureViewDescriptor* _TextureViewDescriptor)
		: TextureView(_texture, _TextureViewDescriptor)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image                           = _texture->GetVKTexture();
		createInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format						   = ResolveVKResourceFormat(_texture->GetFormat());
		createInfo.components.r					   = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g					   = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b					   = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a					   = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask	   = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel   = 0;
		createInfo.subresourceRange.levelCount	   = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount     = 1;

		if (vkCreateImageView(_renderDevice->GetDevice(), &createInfo, nullptr, &m_ImageViewObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'ImageView' object.", LogType::LOG_TYPE_ERROR);
	}

	VKTextureView::~VKTextureView()
	{
		vkDestroyImageView(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_ImageViewObj, nullptr);
	}
}