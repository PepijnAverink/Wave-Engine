#pragma once
#include "./graphics/api/interface/resource/resource_state.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkImageLayout ResolveVKImageLayout(ResourceState _state)
	{
		switch (_state)
		{
			case ResourceState::RESOURCE_STATE_GENERAL_READ :
				return VK_IMAGE_LAYOUT_UNDEFINED;
			case ResourceState::RESOURCE_STATE_PRESENT :
				return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		}

		Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
		return VK_IMAGE_LAYOUT_UNDEFINED;
	}
}