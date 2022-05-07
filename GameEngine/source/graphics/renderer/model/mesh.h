#pragma once


namespace Graphics
{
	class CommandBuffer;
	class Fence;
	class Mesh
	{
	public:
		Mesh() = default;
		~Mesh();


		// Helpers for the submeshes
		inline uint32_t GetSubmeshCount() const { return m_SubMeshCount; }
		inline std::vector<SubMesh> GetSubMeshes() { return m_SubMeshes; }
		inline const std::vector<SubMesh> GetSubMeshes() const { return m_SubMeshes; }

		// Individual buffer getters
		inline Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
		inline Buffer* GetIndexBuffer()  const { return m_IndexBuffer; }

	protected:
		void CreateVertexBuffer(CommandBuffer* _commandBuffer, Fence* _fence, void* _data, const uint32_t _size, BufferLayout _layout);
		void CreateIndexBuffer(CommandBuffer* _commandBuffer, Fence* _fence, void* _data, const uint32_t _size, BufferLayout _layout);

		// Helper for friend classes.
		void AddSubmesh(SubMesh _mesh);

		Buffer* m_VertexBuffer = nullptr;
		Buffer* m_IndexBuffer  = nullptr;
		BufferLayout m_VertexBufferLayout;

		uint32_t m_SubMeshCount = 0;
		std::vector<SubMesh> m_SubMeshes;
	};
}