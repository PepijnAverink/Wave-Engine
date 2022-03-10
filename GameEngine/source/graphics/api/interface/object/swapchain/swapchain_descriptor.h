#pragma once
#include "./graphics/api/interface/resource/resource_format.h"

#include <string>

class Window;
namespace Graphics
{
	class SwapchainDescriptor
	{
	public:
		SwapchainDescriptor() = default;

		std::string Name;
		Window*     Window = nullptr;

		uint32_t    Width = 0;
		uint32_t    Height = 0;
	};
}