//#include "./graphics/api/vulkan/resource/texture/vk_texture2D.h"
//#include "./graphics/api/vulkan/resource/vk_resource_format.h"
#include "core/stdafx.h"

namespace Graphics
{
	VKTexture2D::VKTexture2D(VKRenderDevice* _renderDevice, const Texture2DDescriptor* _texture2DDescriptor)
		: Texture2D(_texture2DDescriptor)
	{
		VkImageCreateInfo imageInfo{};
		imageInfo.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType     = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width  = static_cast<uint32_t>(_texture2DDescriptor->Width);
		imageInfo.extent.height = static_cast<uint32_t>(_texture2DDescriptor->Height);
		imageInfo.extent.depth  = 1;
		imageInfo.mipLevels     = 1;
		imageInfo.arrayLayers   = 1;
		imageInfo.format		= ResolveVKResourceFormat(_texture2DDescriptor->Format);
		imageInfo.tiling		= VK_IMAGE_TILING_OPTIMAL;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage			= VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		imageInfo.sharingMode	= VK_SHARING_MODE_EXCLUSIVE;
		imageInfo.samples		= VK_SAMPLE_COUNT_1_BIT;
		imageInfo.flags			= 0; // Optional
		
		if (vkCreateImage(_renderDevice->GetDevice(), &imageInfo, nullptr, &m_ImageObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'VKTexture2D' object.", LogType::LOG_TYPE_ERROR);

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(_renderDevice->GetDevice(), m_ImageObj, &memRequirements);
		
		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType			  = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize  = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(_renderDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		
		if (vkAllocateMemory(_renderDevice->GetDevice(), &allocInfo, nullptr, &m_BufferMemory) != VK_SUCCESS) {
			Logger::Log("VK_ERROR - Failed to create 'VKTexture2D' object.", LogType::LOG_TYPE_ERROR);
		}
		
		vkBindImageMemory(_renderDevice->GetDevice(), m_ImageObj, m_BufferMemory, 0);

		VkImageViewCreateInfo createInfo{};
		createInfo.sType							= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image							= m_ImageObj;
		createInfo.viewType							= VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format							= ResolveVKResourceFormat(m_Format);
		createInfo.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel	= 0;
		createInfo.subresourceRange.levelCount		= 1;
		createInfo.subresourceRange.baseArrayLayer	= 0;
		createInfo.subresourceRange.layerCount		= 1;

		if (vkCreateImageView(_renderDevice->GetDevice(), &createInfo, nullptr, &m_ImageViewObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'ImageView' object.", LogType::LOG_TYPE_ERROR);
	}

	VKTexture2D::VKTexture2D(VKRenderDevice* _renderDevice, VkImage _resource, const Texture2DDescriptor* _texture2DDescriptor)
		: Texture2D(_texture2DDescriptor)
		, m_ImageObj(_resource)
	{ 
		VkImageViewCreateInfo createInfo{};
		createInfo.sType							= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image							= m_ImageObj;
		createInfo.viewType							= VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format							= ResolveVKResourceFormat(m_Format);
		createInfo.components.r						= VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g						= VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b						= VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a						= VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel	= 0;
		createInfo.subresourceRange.levelCount		= 1;
		createInfo.subresourceRange.baseArrayLayer	= 0;
		createInfo.subresourceRange.layerCount		= 1;

		if (vkCreateImageView(_renderDevice->GetDevice(), &createInfo, nullptr, &m_ImageViewObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'ImageView' object.", LogType::LOG_TYPE_ERROR);
	}

	VKTexture2D::~VKTexture2D()
	{
		vkDestroyImage(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_ImageObj, nullptr);
		vkFreeMemory(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_BufferMemory, nullptr);
		FreeImageView();
	}

	void VKTexture2D::FreeImageView()
	{
		vkDestroyImageView(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_ImageViewObj, nullptr);
	}

	uint32_t VKTexture2D::FindMemoryType(VKRenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(_renderDevice->GetPhysicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		Logger::Log("VK_ERROR - Failed to find suitable memory type.", LogType::LOG_TYPE_ERROR);
		return 0;
	}
}