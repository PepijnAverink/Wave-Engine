#pragma once
#include "./graphics/api/interface/resource/sampler/sampler2D_descriptor.h"

namespace Graphics
{
	class Sampler2D
	{
	public:
		Sampler2D(const Sampler2DDescriptor* _sampler2DDescriptor);
		virtual ~Sampler2D();

	protected:
		FilterMode m_FilterMode;
	};
}