#include "./graphics/api/vulkan/pipeline/layout/vk_input_layout.h"
#include "./graphics/api/vulkan/pipeline/layout/vk_input_type.h"
#include "./graphics/api/vulkan/resource/shader/vk_shader_type_flags.h"

namespace Graphics
{
	VKInputLayout::VKInputLayout(VKRenderDevice* _renderDevice, const InputLayoutDescriptor* _inputLayoutDescriptor)
		: InputLayout(_inputLayoutDescriptor)
	{
		uint32_t descriptorCount = 0;
		std::vector<VkPushConstantRange> constants;

		for (int i = 0; i < _inputLayoutDescriptor->Layouts.size(); i++)
		{
			InputSet set = _inputLayoutDescriptor->Layouts[i];

			if (set.Elements[0].Type == InputType::INPUT_TYPE_CONSTANT)
			{
				for (int j = 0; j < set.Elements.size(); j++)
				{
					VkPushConstantRange push_constant;
					push_constant.offset     = 0;
					push_constant.size       = set.Elements[j].Size;
					push_constant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

					constants.push_back(push_constant);
				}
			}
			else
			{
				m_DescriptorSetLayouts.resize(m_DescriptorSetLayouts.size()+1);
				std::vector<VkDescriptorSetLayoutBinding> bindings;
				bindings.resize(set.Elements.size());
				for (int j = 0; j < set.Elements.size(); j++)
				{
					bindings[j].binding = set.Elements[j].BaseRegisterID;
					bindings[j].descriptorType = ResolveVKInputType(set.Elements[j].Type);
					bindings[j].descriptorCount = set.Elements[j].Count;
					bindings[j].stageFlags = ResolveVKShaderTypeFlag(set.Elements[j].StageFlag);;
					bindings[j].pImmutableSamplers = nullptr;
				}

				VkDescriptorSetLayoutCreateInfo layoutInfo{};
				layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				layoutInfo.bindingCount = bindings.size();
				layoutInfo.pBindings = bindings.data();
				if (vkCreateDescriptorSetLayout(_renderDevice->GetDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayouts[descriptorCount]) != VK_SUCCESS)
					Logger::Log("VK_ERROR - Failed to create vkDescriptorSetLayout.", LogType::LOG_TYPE_ERROR);

				descriptorCount++;
			}
		}

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount         = m_DescriptorSetLayouts.size();
		pipelineLayoutInfo.pSetLayouts            = m_DescriptorSetLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = constants.size();
		pipelineLayoutInfo.pPushConstantRanges    = constants.data();

		if (vkCreatePipelineLayout(_renderDevice->GetDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayoutObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create VKInputLayout.", LogType::LOG_TYPE_ERROR);
	}

	VKInputLayout::~VKInputLayout()
	{
		vkDestroyPipelineLayout(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_PipelineLayoutObj, nullptr);
		for (int i = 0; i < m_DescriptorSetLayouts.size(); i++)
			vkDestroyDescriptorSetLayout(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_DescriptorSetLayouts[i], nullptr);
	}
}