#pragma once
#include <string>

namespace Graphics
{
	class FenceDescriptor
	{
	public:
		FenceDescriptor() = default;
		
		std::string Name;
		uint64_t    TimeOut;
	};
}