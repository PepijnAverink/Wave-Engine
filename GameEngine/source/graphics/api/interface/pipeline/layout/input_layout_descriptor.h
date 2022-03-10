#pragma once
#include "./graphics/api/interface/pipeline/layout/input_set.h"

#include <string>
#include <vector>

namespace Graphics
{
	class InputLayoutDescriptor
	{
	public:
		InputLayoutDescriptor() = default;

		std::string				  Name;
		std::vector<InputSet>     Layouts;
	};
}