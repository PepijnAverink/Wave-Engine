#pragma once
#include "./graphics/api/interface/resource/resource_format.h"
#include "./graphics/api/interface/resource/resource_state.h"

#include <string>

namespace Graphics
{
	class Texture2DDescriptor
	{
	public:
		Texture2DDescriptor() = default;

		std::string Name;
		uint32_t Width;
		uint32_t Height;

		ResourceFormat Format = ResourceFormat::RESOURCE_FORMAT_NONE;
		ResourceState State   = ResourceState::RESOURCE_STATE_NONE;
	};
}