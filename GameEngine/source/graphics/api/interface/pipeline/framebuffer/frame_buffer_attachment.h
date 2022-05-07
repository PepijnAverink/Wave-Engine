#pragma once
#include "./graphics/api/interface/pipeline/framebuffer/frame_buffer_attachment_type.h"
#include "./graphics/api/interface/resource/texture/texture2D.h"

namespace Graphics
{
	class FrameBufferAttachment
	{
	public:
		FrameBufferAttachment() = default;

		Texture2D*				  Texture = nullptr;
		FrameBufferAttachmentType Type = FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_NONE;
	};
}