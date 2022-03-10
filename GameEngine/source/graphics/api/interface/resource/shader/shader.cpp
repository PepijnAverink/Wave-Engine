#include "./graphics/api/interface/resource/shader/shader.h"

namespace Graphics
{
	Shader::Shader(const ShaderDescriptor* _shaderDescriptor)
		: m_Type(_shaderDescriptor->Type)
		, m_EntryPoint(_shaderDescriptor->EntryPoint)
	{ }

	Shader::~Shader()
	{

	}
}