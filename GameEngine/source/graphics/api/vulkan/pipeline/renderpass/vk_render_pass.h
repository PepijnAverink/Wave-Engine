#pragma once
//#include "./graphics/api/interface/pipeline/renderpass/render_pass.h"
//#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKRenderPass final : public RenderPass
	{
	public:
		VKRenderPass(VKRenderDevice* _renderDevice, const RenderPassDescriptor* _renderPassDescriptor);
		virtual ~VKRenderPass();

		inline VkRenderPass GetVKRenderPass() const { return m_RenderPassObj; }

	private:
		VkRenderPass m_RenderPassObj;
	};
}