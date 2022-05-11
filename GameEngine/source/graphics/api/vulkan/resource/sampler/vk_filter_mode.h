#pragma once
#include "./graphics/api/interface/resource/sampler/filter_mode.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkFilter ResolveVKFilterMode(FilterMode _mode)
	{
		switch (_mode)
		{
			case FilterMode::FILTER_MODE_LINEAR :
				return VK_FILTER_LINEAR;
			case FilterMode::FILTER_MODE_NEAREST :
				return VK_FILTER_NEAREST;
		}

		Logger::Log("VK_ERROR - Failed to resolve FilterMode: " + _mode, LogType::LOG_TYPE_ERROR);
		return VK_FILTER_NEAREST;
	}
}