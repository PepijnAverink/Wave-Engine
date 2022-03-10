#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_set.h"
#include "./graphics/api/vulkan/pipeline/layout/vk_input_layout.h"
#include "./graphics/api/vulkan/resource/buffer/vk_buffer_usage.h"
#include "./graphics/api/vulkan/resource/buffer/vk_buffer.h"

namespace Graphics
{
	VKDescriptorSet::VKDescriptorSet(VKDescriptorPool* _descriptorPool, const DescriptorSetDescriptor* _descriptorSetDescriptor)
		: DescriptorSet(_descriptorSetDescriptor)
	{

		VkDescriptorSetLayout layout = ((VKInputLayout*)_descriptorSetDescriptor->InputLayout)->GetVKDescriptorSetLayout(_descriptorSetDescriptor->SetIndex);

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType				 = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool	 = _descriptorPool->GetVKDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts        = &layout;

		if (vkAllocateDescriptorSets(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), &allocInfo, &m_DescriptorSetObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to allocate 'DescriptorSet' object.", LogType::LOG_TYPE_ERROR);
	}

	VKDescriptorSet::~VKDescriptorSet()
	{
		// Will be implicitely freed when descriptor pool is de-allocated
	}

	void VKDescriptorSet::AllocateDescriptor(Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex)
	{
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = ((VKBuffer*)_buffer)->GetVKBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range  = _buffer->GetSize();

		VkWriteDescriptorSet descriptorWrite{};
		descriptorWrite.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet           = m_DescriptorSetObj;
		descriptorWrite.dstBinding       = _bindingIndex;
		descriptorWrite.dstArrayElement  = _arrayIndex;
		descriptorWrite.descriptorType   = ResolveVKDescriptorType(_buffer->GetUsage());
		descriptorWrite.descriptorCount  = 1;
		descriptorWrite.pBufferInfo      = &bufferInfo;
		descriptorWrite.pImageInfo       = nullptr; // Optional
		descriptorWrite.pTexelBufferView = nullptr; // Optional

		vkUpdateDescriptorSets(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), 1, &descriptorWrite, 0, nullptr);
	}
}