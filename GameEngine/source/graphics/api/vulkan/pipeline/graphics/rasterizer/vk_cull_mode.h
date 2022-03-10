#pragma once
#include "./graphics/api/interface/pipeline/graphics/rasterizer/cull_mode.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkCullModeFlagBits ResolveVKCullMode(CullMode _cullMode)
	{
		switch (_cullMode)
		{
			case CullMode::CULL_MODE_NONE :
				return VK_CULL_MODE_NONE;
			case CullMode::CULL_MODE_FRONT :
				return VK_CULL_MODE_FRONT_BIT;
			case CullMode::CULL_MODE_BACK:
				return VK_CULL_MODE_BACK_BIT;
		}

		Logger::Log("VK_ERROR - Failed to resolve CullMode: " + _cullMode, LogType::LOG_TYPE_ERROR);
		return VK_CULL_MODE_NONE;
	}
}