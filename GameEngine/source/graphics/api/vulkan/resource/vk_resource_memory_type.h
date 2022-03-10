#pragma once
#include "./graphics/api/interface/resource/resource_memory_type.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkMemoryPropertyFlags  ResoleVKResourceMemoryType(ResourceMemoryType _type)
	{
		switch (_type)
		{
			case ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY :
				return (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			case ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY :
				return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

		}

		Logger::Log("VK_ERROR - Failed to resolve ResourceMemroyType: " + _type, LogType::LOG_TYPE_ERROR);
		return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	}
}