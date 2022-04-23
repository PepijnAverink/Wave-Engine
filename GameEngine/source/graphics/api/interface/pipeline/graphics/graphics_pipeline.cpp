//#include "./graphics/api/interface/pipeline/graphics/graphics_pipeline.h"
#include "core/stdafx.h"
namespace Graphics
{
	GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		: m_InputLayout(_graphicsPipelineDescriptor->InputLayout)
	{ }

	GraphicsPipeline::~GraphicsPipeline()
	{ }
}