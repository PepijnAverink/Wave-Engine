#pragma once

namespace Graphics
{
	class Cube : public Mesh
	{
	public:
		Cube(CommandBuffer* _commandBuffer, Fence* _fence);
	};
}