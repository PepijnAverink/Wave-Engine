#pragma once
#include "./graphics/api/interface/pipeline/framebuffer/frame_buffer_descriptor.h"

namespace Graphics
{
	class FrameBuffer
	{
	public:
		FrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor);
		virtual ~FrameBuffer();

	protected:

	};
}