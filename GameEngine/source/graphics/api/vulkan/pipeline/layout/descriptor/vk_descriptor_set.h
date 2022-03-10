#pragma once
#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_set.h"
#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_pool.h"

namespace Graphics
{
	class VKDescriptorSet final : public DescriptorSet
	{
	public:
		virtual ~VKDescriptorSet();

		virtual void AllocateDescriptor(Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex) override;

		inline VkDescriptorSet GetVKDescriptorSet() const { return m_DescriptorSetObj; }

	private:
		friend class VKDescriptorPool;
		VKDescriptorSet(VKDescriptorPool* _descriptorPool, const DescriptorSetDescriptor* _descriptorSetDescriptor);

		VkDescriptorSet m_DescriptorSetObj;
	};
}