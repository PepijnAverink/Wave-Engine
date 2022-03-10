#include "./graphics/api/vulkan/resource/shader/vk_shader.h"
#include "./core/system/file_system.h"
#include "./core/logger.h"

namespace Graphics
{
	VKShader::VKShader(VKRenderDevice* _renderDevice, const ShaderDescriptor* _shaderDescriptor)
		: Shader(_shaderDescriptor)
	{
		// Read shader code
		void* code  = nullptr;
		size_t size = 0;
		FileSystem::ReadFile(_shaderDescriptor->Filepath, &code, size);

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = size;
		createInfo.pCode    = reinterpret_cast<const uint32_t*>(code);

		// Crate shader module ander error check
		if (vkCreateShaderModule(_renderDevice->GetDevice(), &createInfo, nullptr, &m_ShaderModule) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create shader module.", LogType::LOG_TYPE_ERROR);
	}

	VKShader::~VKShader()
	{
		 vkDestroyShaderModule(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_ShaderModule, nullptr);
	}
}