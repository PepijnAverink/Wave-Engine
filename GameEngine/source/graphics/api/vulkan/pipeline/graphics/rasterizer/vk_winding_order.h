#pragma once
#include "./graphics/api/interface/pipeline/graphics/rasterizer/winding_order.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkFrontFace ResolveVKWindingOrder(WindingOrder _windingOrder)
	{
		switch (_windingOrder)
		{
			case WindingOrder::WINDING_ORDER_CW :
				return VK_FRONT_FACE_CLOCKWISE;
			case WindingOrder::WINDING_ORDER_CCW:
				return VK_FRONT_FACE_COUNTER_CLOCKWISE;
		}

		Logger::Log("VK_ERROR - Failed to resolve WindingOrder: " + _windingOrder, LogType::LOG_TYPE_ERROR);
		return VK_FRONT_FACE_CLOCKWISE;
	}
}