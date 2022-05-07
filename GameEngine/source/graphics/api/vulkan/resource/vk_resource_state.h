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
			case ResourceState::RESOURCE_STATE_UNDEFINED :
				return VK_IMAGE_LAYOUT_UNDEFINED;
			case ResourceState::RESOURCE_STATE_GENERAL_READ :
				return VK_IMAGE_LAYOUT_UNDEFINED;
			case ResourceState::RESOURCE_STATE_PRESENT :
				return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			case ResourceState::RESOURCE_STATE_GENERAL_WRITE :
				return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			case ResourceState::RESOURCE_STATE_SHADER_READ_ONLY :
				return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
		return VK_IMAGE_LAYOUT_UNDEFINED;
	}
	inline VkAccessFlags ResolveVKAccessFlag(ResourceState _state)
	{
		switch (_state)
		{
		case ResourceState::RESOURCE_STATE_UNDEFINED:
			return 0;
		case ResourceState::RESOURCE_STATE_SHADER_READ_ONLY:
			return VK_ACCESS_SHADER_READ_BIT;
		case ResourceState::RESOURCE_STATE_GENERAL_WRITE:
			return VK_ACCESS_TRANSFER_WRITE_BIT;
		}

		Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
		return VK_ACCESS_SHADER_READ_BIT;
	}
	inline VkPipelineStageFlags ResolveVKStageFlag(ResourceState _state)
	{
		switch (_state)
		{
		case ResourceState::RESOURCE_STATE_UNDEFINED:
			return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		case ResourceState::RESOURCE_STATE_SHADER_READ_ONLY:
			return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		case ResourceState::RESOURCE_STATE_GENERAL_WRITE:
			return VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		Logger::Log("VK_ERROR - Failed to resolve ResourceState: " + _state, LogType::LOG_TYPE_ERROR);
		return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	}
}