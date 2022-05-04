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

		inline std::vector<SubMesh> GetSubMeshes() { return m_SubMeshes; }
		inline const std::vector<SubMesh> GetSubMeshes() const { return m_SubMeshes; }

		inline Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
		inline Buffer* GetIndexBuffer() const { return m_IndexBuffer; }

	protected:
		void CreateVertexBuffer(CommandBuffer* _commandBuffer, Fence* _fence, void* _data, const uint32_t _size, BufferLayout _layout);
		void CreateIndexBuffer(CommandBuffer* _commandBuffer, Fence* _fence, void* _data, const uint32_t _size, BufferLayout _layout);

		Buffer* m_VertexBuffer = nullptr;
		Buffer* m_IndexBuffer  = nullptr;
		BufferLayout m_VertexBufferLayout;

		std::vector<SubMesh> m_SubMeshes;
	};
}