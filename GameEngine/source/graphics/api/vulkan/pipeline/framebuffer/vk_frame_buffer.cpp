//#include "./graphics/api/vulkan/pipeline/framebuffer/vk_frame_buffer.h"
//#include "./graphics/api/vulkan/pipeline/renderpass/vk_render_pass.h"
//#include "./graphics/api/vulkan/resource/view/vk_texture_view.h"
#include "core/stdafx.h"
namespace Graphics
{
	VKFrameBuffer::VKFrameBuffer(VKRenderDevice* _renderDevice, const FrameBufferDescriptor* _frameBufferDescriptor)
		: FrameBuffer(_frameBufferDescriptor)
	{
        std::vector<VkImageView> imageViews;
        for (uint32_t i = 0; i < _frameBufferDescriptor->Attachments.size(); i++)
        {
            imageViews.push_back(((VKTexture2D*)_frameBufferDescriptor->Attachments[i].Texture)->GetVKTextureView());
        }

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass      = ((VKRenderPass*)_frameBufferDescriptor->RenderPass)->GetVKRenderPass();
        framebufferInfo.attachmentCount = imageViews.size();
        framebufferInfo.pAttachments    = imageViews.data();
        framebufferInfo.width           = _frameBufferDescriptor->Width;
        framebufferInfo.height          = _frameBufferDescriptor->Height;
        framebufferInfo.layers          = 1;

        if (vkCreateFramebuffer(_renderDevice->GetDevice(), &framebufferInfo, nullptr, &m_FrameBufferObj) != VK_SUCCESS)
            Logger::Log("VK_ERROR - Failed to create 'FrameBuffer' object.", LogType::LOG_TYPE_ERROR);
	}

	VKFrameBuffer::~VKFrameBuffer()
	{
        vkDestroyFramebuffer(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_FrameBufferObj, nullptr);
	}
}