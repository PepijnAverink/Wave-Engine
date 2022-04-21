//#include "./graphics/api/vulkan/pipeline/renderpass/vk_render_pass.h"
//#include "./graphics/api/vulkan/pipeline/renderpass/vk_render_pass_load_op.h"
//#include "./graphics/api/vulkan/pipeline/renderpass/vk_render_pass_store_op.h"
//#include "./graphics/api/vulkan/resource/vk_resource_format.h"
//#include "./graphics/api/vulkan/resource/vk_resource_state.h"
#include "core/stdafx.h"

namespace Graphics
{
	VKRenderPass::VKRenderPass(VKRenderDevice* _renderDevice, const RenderPassDescriptor* _renderPassDescriptor)
		: RenderPass(_renderPassDescriptor)
	{
		VkAttachmentReference depthAttachment;
		std::vector<VkAttachmentReference> colorAttachments;

		std::vector<VkAttachmentDescription> attachments;
		for (uint32_t i = 0; i < _renderPassDescriptor->Attachments.size(); i++)
		{
			VkAttachmentDescription attachment{};
			attachment.format         = Graphics::ResolveVKResourceFormat(_renderPassDescriptor->Attachments[i].Format);
			attachment.samples        = VK_SAMPLE_COUNT_1_BIT;
			attachment.loadOp		  = ResolveVKRenderPassLoadOp(_renderPassDescriptor->Attachments[i].LoadOp);
			attachment.storeOp		  = ResolveVKRenderPassStoreOp(_renderPassDescriptor->Attachments[i].StoreOp);
			attachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachment.initialLayout  = ResolveVKImageLayout(_renderPassDescriptor->Attachments[i].InitialState);
			attachment.finalLayout    = ResolveVKImageLayout(_renderPassDescriptor->Attachments[i].FinalStatte);

			attachments.push_back(attachment);

			if (_renderPassDescriptor->Attachments[i].Type == RenderPassAttachmentType::RENDER_PASS_ATTACHMENT_TYPE_COLOR)
			{
				VkAttachmentReference colorAttachmentRef{};
				colorAttachmentRef.attachment = i;
				colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

				colorAttachments.push_back(colorAttachmentRef);
			}
			else if (_renderPassDescriptor->Attachments[i].Type == RenderPassAttachmentType::RENDER_PASS_ATTACHMENT_TYPE_DEPTH_STENCIL)
			{
				VkAttachmentReference depthAttachmentRef{};
				depthAttachmentRef.attachment = i;
				depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

				depthAttachment = depthAttachmentRef;
			}
		}

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = colorAttachments.size();
		subpass.pColorAttachments    = colorAttachments.data();

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = attachments.size();
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(_renderDevice->GetDevice(), &renderPassInfo, nullptr, &m_RenderPassObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'VKRenderPass' object.", LogType::LOG_TYPE_ERROR);
	}

	VKRenderPass::~VKRenderPass()
	{
		vkDestroyRenderPass(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_RenderPassObj, nullptr);
	}
}