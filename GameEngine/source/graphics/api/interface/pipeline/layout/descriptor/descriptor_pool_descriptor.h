#pragma once
#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_pool_size.h"

#include <string>
#include <vector>

namespace Graphics
{
	class DescriptorPoolDescriptor
	{
	public:
		DescriptorPoolDescriptor() = default;

		std::string						Name;
		uint32_t						MaxDescriptorSet = 0;
		std::vector<DescriptorPoolSize> Sizes;
	};
}