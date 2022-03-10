#pragma once
#include "./graphics/api/interface/resource/buffer/buffer_usage.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkBufferUsageFlags ResolveVKBufferUsage(BufferUsage _usage)
	{
		switch (_usage)
		{
			case BufferUsage::BUFFER_USAGE_VERTEX_BUFFER :
				return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case BufferUsage::BUFFER_USAGE_INDEX_BUFFER :
				return VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case BufferUsage::BUFFER_USAGE_STAGING_BUFFER :
				return VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
			case BufferUsage::BUFFER_USAGE_UNIFORM_BUFFER :
				return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		}

		Logger::Log("Failed to resolve BufferUsage: ", LogType::LOG_TYPE_ERROR);
		return VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	}

	inline VkDescriptorType ResolveVKDescriptorType(BufferUsage _usage)
	{
		switch (_usage)
		{
			case BufferUsage::BUFFER_USAGE_UNIFORM_BUFFER:
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		}

		Logger::Log("Failed to resolve BufferUsage: ", LogType::LOG_TYPE_ERROR);
		return VK_DESCRIPTOR_TYPE_SAMPLER;
	}
}