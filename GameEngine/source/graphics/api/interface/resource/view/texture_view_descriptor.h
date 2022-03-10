#pragma once
#include "./graphics/api/interface/resource/resource_memory_type.h"

#include <string>

namespace Graphics
{
	class TextureViewDescriptor
	{
	public:
		std::string Name;
		ResourceMemoryType MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_NONE;
	};
}