#pragma once
#include "./graphics/api/interface/resource/shader/shader_type_flags.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkShaderStageFlags ResolveVKShaderTypeFlag(ShaderTypeFlag _flag)
	{
		VkFlags result = 0;
		if (_flag & ShaderTypeFlag::SHADER_TYPE_FLAG_VERTEX)
			result |= VK_SHADER_STAGE_VERTEX_BIT;
		if (_flag & ShaderTypeFlag::SHADER_TYPE_FLAG_PIXEL)
			result |= VK_SHADER_STAGE_FRAGMENT_BIT;
		if (_flag & ShaderTypeFlag::SHADER_TYPE_FLAG_ALL)
			result |= VK_SHADER_STAGE_ALL;

		return result;
	}
}