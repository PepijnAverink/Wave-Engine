#pragma once
#include "./graphics/api/interface/resource/buffer/buffer_usage.h"
#include "./graphics/api/interface/resource/resource_memory_type.h"
#include "./graphics/api/interface/pipeline/layout/vertex_layout.h"

#include <string>

namespace Graphics
{
	using BufferLayout = VertexLayout;
	using BufferElement = VertexElement;
	class BufferDescriptor
	{
	public:
		BufferDescriptor() = default;

		std::string		   Name;
		void*			   Data = nullptr;
		uint32_t		   Size;
		BufferLayout	   BufferLayout;
		BufferUsage		   Usage = BufferUsage::BUFFER_USAGE_NONE;
		ResourceMemoryType MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_NONE;
	};
}