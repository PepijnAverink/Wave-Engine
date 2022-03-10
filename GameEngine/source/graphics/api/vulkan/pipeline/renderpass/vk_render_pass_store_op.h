#pragma once
#include "./graphics/api/interface/pipeline/renderpass/render_pass_store_op.h"
#include "./core/logger.h"

#include <./vulkan/vulkan.h>

namespace Graphics
{
	inline VkAttachmentStoreOp ResolveVKRenderPassStoreOp(RenderPassStoreOp _storeOp)
	{
		switch (_storeOp)
		{
			case RenderPassStoreOp::RENDER_PASS_STORE_OP_STORE :
				return VK_ATTACHMENT_STORE_OP_STORE;
			case RenderPassStoreOp::RENDER_PASS_STORE_OP_DONT_CARE :
				return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		}

		Logger::Log("VK_ERROR - Failed to resolve RenderPassStoreOp: " + _storeOp, LogType::LOG_TYPE_ERROR);
		return VK_ATTACHMENT_STORE_OP_DONT_CARE;
	}
}