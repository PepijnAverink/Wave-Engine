#pragma once
#include "./graphics/api/interface/pipeline/renderpass/render_pass_load_op.h"
#include "./core/logger.h"

#include <./vulkan/vulkan.h>

namespace Graphics
{
	inline VkAttachmentLoadOp ResolveVKRenderPassLoadOp(RenderPassLoadOp _loadOp)
	{
		switch (_loadOp)
		{
			case RenderPassLoadOp::RENDER_PASS_LOAD_OP_LOAD :
				return VK_ATTACHMENT_LOAD_OP_LOAD;
			case RenderPassLoadOp::RENDER_PASS_LOAD_OP_CLEAR :
				return VK_ATTACHMENT_LOAD_OP_CLEAR;
			case RenderPassLoadOp::RENDER_PASS_LOAD_OP_DONT_CARE :
				return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		}

		Logger::Log("VK_ERROR - Failed to resolve RenderPassLoadOp: " + _loadOp, LogType::LOG_TYPE_ERROR);
		return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	}
}