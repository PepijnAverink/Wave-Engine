#pragma once
#include "./graphics/api/interface/pipeline/layout/input_layout.h"
#include "./graphics/api/interface/pipeline/layout/vertex_layout.h"
#include "./graphics/api/interface/pipeline/graphics/rasterizer/cull_mode.h"
#include "./graphics/api/interface/pipeline/graphics/rasterizer/fill_mode.h"
#include "./graphics/api/interface/pipeline/graphics/rasterizer/winding_order.h"
#include "./graphics/api/interface/pipeline/graphics/topology/topology.h"
#include "./graphics/api/interface/pipeline/graphics/viewport/view_port.h"
#include "./graphics/api/interface/pipeline/graphics/viewport/scissor_rect.h"
#include "./graphics/api/interface/resource/shader/shader.h"

#include "./graphics/api/interface/pipeline/renderpass/render_pass.h"

#include <string>

namespace Graphics
{
	class GraphicsPipelineDescriptor
	{
	public:
		GraphicsPipelineDescriptor() = default;

		std::string Name;

		// Topology
		Topology Topology = Topology::TOPOLOGY_NONE;

		InputLayout* InputLayout = nullptr;
		VertexLayout VertexLayout;

		// Rasterizer
		CullMode CullMode		  = CullMode::CULL_MODE_NONE;
		FillMode FillMode		  = FillMode::FILL_MODE_NONE;
		WindingOrder WindingOrder = WindingOrder::WINDING_ORDER_NONE;

		// Viewport
		uint32_t	Width;
		uint32_t	Height;
		ViewPort    ViewPort;
		ScissorRect ScissorRect;

		// Shaders
		Shader* VertexShader = nullptr;
		Shader* PixelShader  = nullptr;

		// RenderPass
		RenderPass* RenderPass = nullptr;
	};
}