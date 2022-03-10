#pragma once
#include "./core/logger.h"

namespace Graphics
{
	enum ResourceFormat
	{
		RESOURCE_FORMAT_NONE			 = 0x00,
		RESOURCE_FORMAT_ERROR			 = 0x01,
		RESOURCE_FORMAT_B8G8R8A8_SRGB	 = 0x02,
		RESOURCE_FORMAT_R32G32_SFLOAT	 = 0x03,
		RESOURCE_FORMAT_R32G32B32_SFLOAT = 0x04,
		RESOURCE_FORMAT_R16_UINT		 = 0x05,
		RESOURCE_FORMAT_CUSTOM			 = 0x06,
	};

	inline uint32_t GetFormatSize(ResourceFormat _resourceFormat)
	{
		switch (_resourceFormat)
		{
			case RESOURCE_FORMAT_B8G8R8A8_SRGB :
				return sizeof(uint8_t) * 4;
			case RESOURCE_FORMAT_R32G32_SFLOAT :
				return sizeof(float) * 2;
			case RESOURCE_FORMAT_R32G32B32_SFLOAT :
				return sizeof(float) * 3;
			case RESOURCE_FORMAT_R16_UINT:
				return sizeof(uint16_t) * 1;
		}

		Logger::Log("No correct size was found for ResourceFormat:" + _resourceFormat, LogType::LOG_TYPE_ERROR);
		return 0;
	}
}