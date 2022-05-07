#pragma once
#include "./graphics/renderer/model/mesh.h"

namespace Graphics
{
	class Cube : public Mesh
	{
	public:
		Cube(CommandBuffer* _commandBuffer, Fence* _fence);
	};
}