#pragma once
#include "./graphics/api/interface/pipeline/framebuffer/frame_buffer_attachment.h"
#include "./graphics/api/interface/pipeline/renderpass/render_pass.h"

#include <vector>

namespace Graphics
{
	class FrameBufferDescriptor
	{
	public:
		FrameBufferDescriptor() = default;

		std::string Name;
		uint32_t    Width;
		uint32_t    Height;

		bool	    Contigious = false;
		std::vector<FrameBufferAttachment> Attachments;

		RenderPass* RenderPass = nullptr;
	};
}