#pragma once
#include "./graphics/api/interface/pipeline/framebuffer/frame_buffer_attachment_type.h"
#include "./graphics/api/interface/resource/view/texture_view.h"

namespace Graphics
{
	class FrameBufferAttachment
	{
	public:
		FrameBufferAttachment() = default;

		TextureView*			  TextureView = nullptr;
		FrameBufferAttachmentType Type = FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_NONE;
	};
}