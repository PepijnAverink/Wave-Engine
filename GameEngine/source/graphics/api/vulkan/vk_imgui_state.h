#pragma once

namespace Graphics {
	class VKImguiState
	{
	public:
		VKImguiState(VKRenderDevice* vk_render_device, Window* _window, VKCommandQueue* _graphicsQueue, VKRenderPass* _renderPass, VKCommandBuffer* _commandBuffer);
		void DestroyBackend(VKRenderDevice* vk_render_device);
		void InitFrame();
		void RenderFrame(VKFrameBuffer* vk_frame, VKCommandBuffer* vk_command_buffer, VKRenderPass* vk_render_pass, uint32_t width, uint32_t height, VkClearValue* clear_value);
	private:
		VkDescriptorPool* m_imguiPool;
		ImDrawData* m_draw_data;
	};
}
