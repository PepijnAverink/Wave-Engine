#pragma once
#include "./graphics/api/interface/resource/shader/shader_type.h"

namespace Graphics
{
	
	class Shader
	{
	public:
		Shader(const ShaderDescriptor* _shaderDescriptor);
		virtual ~Shader();

		inline std::string GetEntryPoint() const { return m_EntryPoint; }

	protected:
		// Stores the type this shader is associated with
		ShaderType m_Type = ShaderType::SHADER_TYPE_NONE;

		std::string m_EntryPoint;
	};
}