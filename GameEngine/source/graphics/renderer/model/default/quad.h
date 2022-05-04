#pragma once


namespace Graphics
{
	class Quad : public Mesh
	{
	public:
        Quad(CommandBuffer* _commandBuffer, Fence* _fence);
	};
}