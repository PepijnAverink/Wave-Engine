#pragma once
#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_pool_descriptor.h"
#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_set.h"

namespace Graphics
{
	class DescriptorPool
	{
	public:
		DescriptorPool(const DescriptorPoolDescriptor* _descriptorPoolDescriptor);
		virtual ~DescriptorPool();

		virtual DescriptorSet* AllocateDescriptorSet(const DescriptorSetDescriptor* _descriptorSetDescriptor) = 0;
	};
}