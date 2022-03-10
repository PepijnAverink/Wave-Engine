#pragma once
#include "./graphics/renderer/model/sub_mesh.h"
#include "./graphics/renderer/model/vertex.h"

#include "./graphics/api/interface/resource/buffer/buffer.h"

namespace Graphics
{
	class Mesh
	{
	public:
		Mesh() = default;

		inline std::vector<SubMesh> GetSubMeshes() { return m_SubMeshes; }
		inline const std::vector<SubMesh> GetSubMeshes() const { return m_SubMeshes; }

	private:
		Buffer* m_VertexBuffer = nullptr;
		Buffer* m_IndexBuffer  = nullptr;
		BufferLayout m_VertexBufferLayout;

		std::vector<SubMesh> m_SubMeshes;
	};
}