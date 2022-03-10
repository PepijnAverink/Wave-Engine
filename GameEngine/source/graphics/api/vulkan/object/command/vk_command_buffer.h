#pragma once
#include "./graphics/api/interface/object/command/command_buffer.h"
#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKInputLayout;
	class VKGraphicsPipeline;
	class VKCommandBuffer final : public CommandBuffer
	{
	public:
		VKCommandBuffer(VKRenderDevice* _renderDevice, const CommandBufferDescriptor* _commandBufferDescriptor);
		virtual ~VKCommandBuffer();

		virtual void Reset() override;

		virtual void BeginRecording() override;
		virtual void EndRecording() override;

		virtual void SetViewPort(ViewPort* _viewPort) override;
		virtual void SetScissorRect(ScissorRect* _scrissorRect) override;

		virtual void BeginRenderPass(RenderPass* _renderPass, FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor) override;
		virtual void EndRenderPass() override;

		virtual void CopyBuffer(Buffer* _srcBuffer, Buffer* _dstBuffer, const uint32_t _size) override;
		virtual void CopyBuffer(Buffer* _srcBuffer, Texture2D* _dstTexture) override;

		virtual void SetVertexBuffer(Buffer* _vertexBuffer, const uint32_t _binding) override;
		virtual void SetIndexBuffer(Buffer* _indexBuffer) override;

		virtual void SetDescriptorSet(DescriptorSet* _descriptorSet, const uint32_t _parameterIndex) override;

		virtual void SetGraphicsPipeline(GraphicsPipeline* _graphicsPipeline) override;

		virtual void Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount) override;
		virtual void DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount) override;

		inline VkCommandBuffer GetVKCommandBuffer() const { return m_CommandBufferObj; }

	private:
		VkCommandBuffer m_CommandBufferObj;

		VKGraphicsPipeline* m_CurrentGraphicsPipeline = nullptr;
		VKInputLayout*      m_CurrentInputLayout = nullptr;
	};
}