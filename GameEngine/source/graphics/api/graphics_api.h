#pragma once
#include "./core/logger.h"

namespace Graphics
{
	enum GraphicsAPI
	{
		GRAPHICS_API_NONE   = 0x00,
		GRAPHICS_API_ERROR  = 0x01,
		GRAPHICS_API_VULKAN = 0x02,
	};

	inline std::string GraphicsApiToString(GraphicsAPI _api)
	{
		switch (_api)
		{
			case GraphicsAPI::GRAPHICS_API_NONE : 
				return "GRAPHICS_API_NONE";
			case GraphicsAPI::GRAPHICS_API_ERROR :
				return "GRAPHICS_API_ERROR";
			case GraphicsAPI::GRAPHICS_API_VULKAN :
				return "GRAPHICS_API_VULKAN";
		}

		// Error checking and logging
		Logger::Log("No string found for graphics-api: " + _api, LogType::LOG_TYPE_ERROR);
		return "GRAPHICS_API_ERROR";
	}
}