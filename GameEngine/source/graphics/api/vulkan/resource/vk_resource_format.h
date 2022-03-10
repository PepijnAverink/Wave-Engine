#pragma once
#include "./graphics/api/interface/resource/resource_format.h"
#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkFormat ResolveVKResourceFormat(ResourceFormat _resourceFormat)
	{
		switch (_resourceFormat)
		{
			case ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_SRGB :
				return VK_FORMAT_B8G8R8A8_SRGB;
			case ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT :
				return VK_FORMAT_R32G32_SFLOAT;
			case ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT :
				return VK_FORMAT_R32G32B32_SFLOAT;
			case ResourceFormat::RESOURCE_FORMAT_R16_UINT :
				return VK_FORMAT_R16_UINT;
		}

		return VK_FORMAT_UNDEFINED;
	}

	inline VkIndexType ResolveVKIndexFormat(ResourceFormat _resourceFormat)
	{
		switch (_resourceFormat)
		{
			case ResourceFormat::RESOURCE_FORMAT_R16_UINT:
				return VK_INDEX_TYPE_UINT16;
		}

		return VK_INDEX_TYPE_UINT16;
	}

	inline ResourceFormat ResolveResourceFormat(VkFormat _format)
	{
		switch (_format)
		{
			case VK_FORMAT_B8G8R8A8_SRGB :
				return ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_SRGB;
			case VK_FORMAT_R32G32_SFLOAT :
				return ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT;
			case VK_FORMAT_R32G32B32_SFLOAT :
				return ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT;
		}

		return ResourceFormat::RESOURCE_FORMAT_NONE;
	}
}