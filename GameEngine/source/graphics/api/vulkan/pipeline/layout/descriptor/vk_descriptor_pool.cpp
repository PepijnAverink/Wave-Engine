#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_pool.h"
#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_set.h"
#include "./graphics/api/vulkan/pipeline/layout/vk_input_type.h"
#include "./graphics/api/vulkan/pipeline/layout/vk_input_type.h"

namespace Graphics
{
	VKDescriptorPool::VKDescriptorPool(VKRenderDevice* _renderDevice, const DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		: DescriptorPool(_descriptorPoolDescriptor)
	{
		std::vector<VkDescriptorPoolSize> sizes;
		for (uint32_t i = 0; i < _descriptorPoolDescriptor->Sizes.size(); i++)
		{
			VkDescriptorPoolSize poolSize{};
			poolSize.type			 = ResolveVKInputType(_descriptorPoolDescriptor->Sizes[i].Type);
			poolSize.descriptorCount = static_cast<uint32_t>(_descriptorPoolDescriptor->Sizes[i].Count);

			sizes.push_back(poolSize);
		}

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = sizes.size();
		poolInfo.pPoolSizes    = sizes.data();
		poolInfo.maxSets = _descriptorPoolDescriptor->MaxDescriptorSet;

		if (vkCreateDescriptorPool(_renderDevice->GetDevice(), &poolInfo, nullptr, &m_DescriptorPoolObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to crete 'VKDescriptorPool' object.", LogType::LOG_TYPE_ERROR);
	}

	VKDescriptorPool::~VKDescriptorPool()
	{
		vkDestroyDescriptorPool(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_DescriptorPoolObj, nullptr);
	}

	DescriptorSet* VKDescriptorPool::AllocateDescriptorSet(const DescriptorSetDescriptor* _descriptorSetDescriptor)
	{
		VKDescriptorSet* descriptorSet = new VKDescriptorSet(this, _descriptorSetDescriptor);
		return descriptorSet;
	}
}