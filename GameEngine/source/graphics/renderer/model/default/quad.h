#pragma once
#include "./graphics/renderer/model/mesh.h"

#include "./graphics/api/interface/object/sync/fence.h"
#include "./graphics/api/interface/object/command/command_buffer.h"

namespace Graphics
{
	class Quad : public Mesh
	{
	public:
        Quad(CommandBuffer* _commandBuffer, Fence* _fence);
	};
}