#pragma once
#include "./graphics/api/interface/pipeline/layout/input_type.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkDescriptorType ResolveVKInputType(InputType _type)
	{
		switch (_type)
		{
			case InputType::INPUT_TYPE_UNIFORM_BUFFER :
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			case InputType::INPUT_TYPE_SAMPLER2D :
				return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		}

		Logger::Log("VK_ERROR - Failed to resolve VKInputType.", LogType::LOG_TYPE_ERROR);
		return VK_DESCRIPTOR_TYPE_MAX_ENUM;
	}
}