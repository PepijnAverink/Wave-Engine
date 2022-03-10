#pragma once
#include "./graphics/api/interface/resource/shader/shader_type.h"

#include <string>

namespace Graphics
{
	class ShaderDescriptor
	{
	public:
		ShaderDescriptor() = default;

		std::string  Name;
		ShaderType   Type;

		std::string Filepath;
		std::string EntryPoint;
	};
}