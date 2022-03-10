#pragma once
#include "./graphics/api/interface/object/command/command_buffer_descriptor.h"

namespace Graphics
{
	class ViewPort;
	class ScissorRect;

	class Buffer;
	class Texture2D;
	class DescriptorSet;

	class GraphicsPipeline;
	class RenderPass;
	class FrameBuffer;
	class CommandBuffer
	{
	public:
		CommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor);
		virtual ~CommandBuffer();

		virtual void Reset() = 0;

		virtual void BeginRecording() = 0;
		virtual void EndRecording() = 0;

		virtual void SetViewPort(ViewPort* _viewPort) = 0;
		virtual void SetScissorRect(ScissorRect* _scrissorRect) = 0;
		
		virtual void BeginRenderPass(RenderPass* _renderPass, FrameBuffer* _frameBuffer, const uint32_t _width, const uint32_t _height, float* _clearColor) = 0;
		virtual void EndRenderPass() = 0;

		virtual void CopyBuffer(Buffer* _srcBuffer, Buffer* _dstBuffer, const uint32_t _size) = 0;
		virtual void CopyBuffer(Buffer* _srcBuffer, Texture2D* _dstTexture) = 0;

		virtual void SetVertexBuffer(Buffer* _vertexBuffer, const uint32_t _binding) = 0;
		virtual void SetIndexBuffer(Buffer* _indexBuffer) = 0;

		virtual void SetDescriptorSet(DescriptorSet* _descriptorSet, const uint32_t _parameterIndex) = 0;

		virtual void SetGraphicsPipeline(GraphicsPipeline* _graphicsPipeline) = 0;

		virtual void Draw(const uint32_t _vertexOffset, const uint32_t _vertexCount) = 0;
		virtual void DrawIndexed(const uint32_t _vertexOffset, const uint32_t _indexOffset, const uint32_t _indexCount) = 0;

	protected:
		CommandBufferType m_Type = CommandBufferType::COMMAND_BUFFER_TYPE_NONE;
		CommandPool* m_CommandPool = nullptr;
	};
}