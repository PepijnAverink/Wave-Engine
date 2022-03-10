#pragma once
#include <stdint.h>

namespace Graphics
{
	struct SubMesh
	{
		uint32_t VertexOffset;
		uint32_t VertexCount;
		uint32_t IndexOffset;
		uint32_t IndexCount;
	};
}