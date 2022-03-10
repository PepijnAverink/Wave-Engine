#pragma once
#include "./graphics/api/interface/pipeline/renderpass/render_pass_attachment.h"

#include <string>
#include <vector>

namespace Graphics
{
	class RenderPassDescriptor
	{
	public:
		RenderPassDescriptor() = default;

		std::string Name;
		std::vector<RenderPassAttachment> Attachments;
	};
}