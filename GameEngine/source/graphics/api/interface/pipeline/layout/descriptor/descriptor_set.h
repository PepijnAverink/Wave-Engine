#pragma once
//#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_set_descriptor.h"

namespace Graphics
{
	class Texture2D;
	class Sampler2D;
	class Buffer;
	class DescriptorSet
	{
	public: 
		DescriptorSet(const DescriptorSetDescriptor* _descriptorSetDescriptor);
		virtual ~DescriptorSet();

		virtual void AllocateDescriptor(Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex) = 0;
		virtual void AllocateDescriptor(Texture2D* _texture, Sampler2D* _sampler, const uint32_t _bindingIndex, const uint32_t _arrayIndex) = 0;

	protected:

	};
}