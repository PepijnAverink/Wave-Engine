#pragma once
#include "./graphics/api/interface/pipeline/layout/input_element.h"

#include <vector>

namespace Graphics
{
	class InputSet
	{
	public:
		InputSet(std::vector<InputElement> _elements)
			: Elements(_elements)
		{ }

		std::vector<InputElement> Elements;
	};
}