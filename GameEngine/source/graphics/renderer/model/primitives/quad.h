#pragma once
#include "./graphics/renderer/model/mesh.h"

namespace Graphics
{
	class Quad : public Mesh
	{
	public:
        Quad(CommandBuffer* _commandBuffer, Fence* _fence);
	};
}