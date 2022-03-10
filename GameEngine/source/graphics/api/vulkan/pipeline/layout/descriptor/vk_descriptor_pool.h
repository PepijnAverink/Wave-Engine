#pragma once
#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_pool.h"
#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKDescriptorPool final : public DescriptorPool
	{
	public:
		VKDescriptorPool(VKRenderDevice* _renderDevice, const DescriptorPoolDescriptor* _descriptorPoolDescriptor);
		virtual ~VKDescriptorPool();

		virtual DescriptorSet* AllocateDescriptorSet(const DescriptorSetDescriptor* _descriptorSetDescriptor) override;

		inline VkDescriptorPool GetVKDescriptorPool() const { return m_DescriptorPoolObj; }

	private:
		VkDescriptorPool m_DescriptorPoolObj;
	};
}