#pragma once
#include "./graphics/api/interface/pipeline/layout/input_layout.h"

#include <string>

namespace Graphics
{
	class DescriptorSetDescriptor
	{
	public:
		DescriptorSetDescriptor() = default;

		std::string		Name;

		InputLayout*	InputLayout;
		uint32_t        SetIndex;
	};
}