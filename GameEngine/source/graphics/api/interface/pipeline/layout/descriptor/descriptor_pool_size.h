#pragma once
#include "./graphics/api/interface/pipeline/layout/input_type.h"

#include <stdint.h>

namespace Graphics
{
	class DescriptorPoolSize
	{
	public:
		DescriptorPoolSize() = default;

		InputType Type;
		uint32_t  Count = 0;
	};
}