#pragma once
//#include "./graphics/api/interface/pipeline/graphics/graphics_pipeline.h"
//#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKGraphicsPipeline final : public GraphicsPipeline
	{
	public:
		VKGraphicsPipeline(VKRenderDevice* _renderDevice, const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor);
		virtual ~VKGraphicsPipeline();

		inline VkPipeline GetVKGraphicsPipeline() const { return m_GraphicsPipelineObj; }

	private:
		VkPipeline m_GraphicsPipelineObj;
	};
}