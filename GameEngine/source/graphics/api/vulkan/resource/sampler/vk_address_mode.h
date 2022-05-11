#pragma once
#include "./graphics/api/interface/resource/sampler/address_mode.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkSamplerAddressMode ResolveVKAddressMode(AddressMode _mode)
	{
		switch (_mode)
		{
		case AddressMode::ADDRESS_MODE_REPEAT :
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		case AddressMode::ADDRESS_MODE_MIRROR :
			return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		case AddressMode::ADDRESS_MODE_CLAMP_TO_EDGE :
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		case AddressMode::ADDRESS_MODE_CLAMP_TO_BORDER :
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		}

		Logger::Log("VK_ERROR - Failed to resolve AddressMode: " + _mode, LogType::LOG_TYPE_ERROR);
		return VK_SAMPLER_ADDRESS_MODE_REPEAT;
	}
}