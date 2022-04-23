#pragma once
//#include "./graphics/api/interface/resource/shader/shader.h"
//#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKShader : public Shader
	{
	public:
		VKShader(VKRenderDevice* _renderDevice, const ShaderDescriptor* _shaderDescriptor);
		~VKShader();

		// Vulkan specific method
		// Get's the underlaying vk_ShaderMoule
		inline VkShaderModule GetVKShaderModule() const { return m_ShaderModule; }

	private:
		VkShaderModule m_ShaderModule;
	};
}