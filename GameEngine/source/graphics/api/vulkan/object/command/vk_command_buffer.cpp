#include "./graphics/api/vulkan/object/command/vk_command_buffer.h"
#include "./graphics/api/vulkan/object/command/vk_command_pool.h"

#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_set.h"
#include "./graphics/api/vulkan/resource/buffer/vk_buffer.h"
#include "./graphics/api/vulkan/pipeline/layout/vk_input_layout.h"
#include "./graphics/api/vulkan/pipeline/graphics/vk_graphics_pipeline.h"


#include "./graphics/api/vulkan/pipeline/framebuffer/vk_frame_buffer.h"
#include "./graphics/api/vulkan/resource/texture/vk_texture2D.h"
#include "./graphics/api/vulkan/pipeline/renderpass/vk_render_pass.h"

#include "./core/logger.h"

namespace Graphics
{
	VKCommandBuffer::VKCommandBuffer(VKRenderDevice* _renderDevice, const CommandBufferDescriptor* _commandBufferDescriptor)
		: CommandBuffer(_commandBufferDescriptor)
	{
		// Creation info
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool        = ((VKCommandPool*)_commandBufferDescriptor->CommandPool)->GetVKCommandPool();
		allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		// Create CommandBuffer
		if (vkAllocateCommandBuffers(_renderDevice->GetDevice(), &allocInfo, &m_CommandBufferObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'CommandBuffer' object.", LogType::LOG_TYPE_ERROR);
	}

	VKCommandBuffer::~VKCommandBuffer()
	{ 
		// Destroy commandBuffer obj
		vkFreeCommandBuffers(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), ((VKCommandPool*)m_CommandPool)->GetVKCommandPool(), 1, &m_CommandBufferObj);
	}

	void VKCommandBuffer::Reset()
	{
		vkResetCommandBuffer(m_CommandBufferObj, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
	}

	void VKCommandBuffer::BeginRecording()
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(m_CommandBufferObj, &beginInfo) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to start recording on local CommandBuffer.", LogType::LOG_TYPE_ERROR);
	}

	void VKCommandBuffer::EndRecording()
	{
		if (vkEndCommandBuffer(m_CommandBufferObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to end recording on local CommandBuffer.", LogType::LOG_TYPE_ERROR);
	}

	void VKCommandBuffer::SetViewPort(ViewPort* _viewPort)
	{
		VkViewport viewport;
		viewport.x        = _viewPort->X;
		viewport.y        = _viewPort->Y;
		viewport.width    = _viewPort->Width;
		viewport.height   = _viewPort->Height;
		viewport.minDepth = _viewPort->MinDepth;
		viewport.maxDepth = _viewPort->MaxDepth;

		vkCmdSetViewport(m_CommandBufferObj, 0, 1, &viewport);
	}

	void VKCommandBuffer::SetScissorRect(ScissorRect* _scrissorRect)
	{
		VkRect2D rect;
		rect.offset = { _scrissorRect->X, _scrissorRect->Y };
		rect.extent = { _scrissorRect->Width, _scrissorRect->Height};

		vkCmdSetScissor(m_CommandBufferObj, 0, 1, &rect);
	}

	void VKCommandBuffer::BeginRenderPass(RenderPass* _renderPass, FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor)
	{
		VkExtent2D extend;
		extend.width  = _width;
		extend.height = _height;

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType			 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass		 = ((VKRenderPass*)_renderPass)->GetVKRenderPass();
		renderPassInfo.framebuffer		 = ((VKFrameBuffer*)_frameBuffer)->GetVKFrameBuffer();
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = extend;

		VkClearValue clearColor = { {{_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(m_CommandBufferObj, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VKCommandBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(m_CommandBufferObj);
	}

	void VKCommandBuffer::CopyBuffer(Buffer* _srcBuffer, Buffer* _dstBuffer, const uint32_t _size)
	{
		VkBufferCopy copyRegion{};
		copyRegion.size = _size;

		vkCmdCopyBuffer(m_CommandBufferObj, ((VKBuffer*)_srcBuffer)->GetVKBuffer(), ((VKBuffer*)_dstBuffer)->GetVKBuffer(), 1, &copyRegion);
	}

	void VKCommandBuffer::CopyBuffer(Buffer* _srcBuffer, Texture2D* _dstTexture)
	{
		VkBufferImageCopy region{};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;

		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;

		region.imageOffset = { 0, 0, 0 };
		region.imageExtent = { _dstTexture->GetWidth(), _dstTexture->GetHeight(), 1 };

		vkCmdCopyBufferToImage(m_CommandBufferObj, ((VKBuffer*)_srcBuffer)->GetVKBuffer(), ((VKTexture2D*)_dstTexture)->GetVKTexture(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	}

	void VKCommandBuffer::SetVertexBuffer(Buffer* _vertexBuffer, const uint32_t _binding)
	{
		VkBuffer vertexBuffer = ((VKBuffer*)_vertexBuffer)->GetVKBuffer();
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(m_CommandBufferObj, _binding, 1, &vertexBuffer, offsets);
	}

	void VKCommandBuffer::SetIndexBuffer(Buffer* _indexBuffer)
	{
		vkCmdBindIndexBuffer(m_CommandBufferObj, ((VKBuffer*)_indexBuffer)->GetVKBuffer(), 0, ((VKBuffer*)_indexBuffer)->GetIndexFormat());
	}

	void VKCommandBuffer::SetConstants(void* _data, const uint32_t _offset, const uint32_t _size, const uint32_t _parameterIndex)
	{
		// TODO:: Find way to nicely abstract vertex bit
		vkCmdPushConstants(m_CommandBufferObj, m_CurrentInputLayout->GetVKInputLayout(), VK_SHADER_STAGE_VERTEX_BIT, _offset, _size, _data);
	}

	void VKCommandBuffer::SetDescriptorSet(DescriptorSet* _descriptorSet, const uint32_t _parameterIndex)
	{
		VkDescriptorSet set = ((VKDescriptorSet*)_descriptorSet)->GetVKDescriptorSet();
		vkCmdBindDescriptorSets(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_GRAPHICS, m_CurrentInputLayout->GetVKInputLayout(), _parameterIndex, 1, &set, 0, nullptr);
	}

	void VKCommandBuffer::SetGraphicsPipeline(GraphicsPipeline* _graphicsPipeline)
	{
		m_CurrentGraphicsPipeline = (VKGraphicsPipeline*)_graphicsPipeline;
		m_CurrentInputLayout = (VKInputLayout*)_graphicsPipeline->GetInputLayout();
		vkCmdBindPipeline(m_CommandBufferObj, VK_PIPELINE_BIND_POINT_GRAPHICS, ((VKGraphicsPipeline*)_graphicsPipeline)->GetVKGraphicsPipeline());
	}

	void VKCommandBuffer::Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount)
	{
		vkCmdDraw(m_CommandBufferObj, _vertexCount, 1, _vertexOffset, 0);
	}

	void VKCommandBuffer::DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount)
	{
		vkCmdDrawIndexed(m_CommandBufferObj, _indexCount, 1, _indexOffset, _vertexOffset, 0);
	}
}