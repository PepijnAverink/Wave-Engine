#pragma once
#include "./graphics/api/interface/pipeline/renderpass/render_pass_attachment_type.h"
#include "./graphics/api/interface/pipeline/renderpass/render_pass_load_op.h"
#include "./graphics/api/interface/pipeline/renderpass/render_pass_store_op.h"
#include "./graphics/api/interface/resource/resource_format.h"
#include "./graphics/api/interface/resource/resource_state.h"

namespace Graphics
{
	class RenderPassAttachment
	{
	public:
		RenderPassAttachment() = default;

		RenderPassAttachmentType Type    = RenderPassAttachmentType::RENDER_PASS_ATTACHMENT_TYPE_NONE;
		ResourceFormat           Format  = ResourceFormat::RESOURCE_FORMAT_NONE;
		RenderPassLoadOp         LoadOp  = RenderPassLoadOp::RENDER_PASS_LOAD_OP_NONE;
		RenderPassStoreOp		 StoreOp = RenderPassStoreOp::RENDER_PASS_STORE_OP_NONE;
		ResourceState			 InitialState = ResourceState::RESOURCE_STATE_NONE;
		ResourceState			 FinalStatte  = ResourceState::RESOURCE_STATE_NONE;
	};
}