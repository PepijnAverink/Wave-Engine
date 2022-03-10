#pragma once
#include "./graphics/api/interface/pipeline/graphics/rasterizer/fill_mode.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkPolygonMode ResolveVKFillMode(FillMode _fillMode)
	{
		switch (_fillMode)
		{
			case FillMode::FILL_MODE_SOLID :
				return VK_POLYGON_MODE_FILL;
			case FillMode::FILL_MODE_WIREFRAME :
				return VK_POLYGON_MODE_LINE;
		}

		Logger::Log("VK_ERROR - Failed to resolve FillMode: " + _fillMode, LogType::LOG_TYPE_ERROR);
		return VK_POLYGON_MODE_FILL;
	}
}