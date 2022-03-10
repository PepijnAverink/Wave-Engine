#pragma once
#include "./graphics/renderer/renderer_backend.h"

#include "./graphics/renderer/material/material_instance.h"
#include "./graphics/renderer/model/mesh.h"

#include <glm/glm.hpp>

namespace Graphics
{
	class Renderer3D
	{
	public:
		virtual void OnInitialize(RendererBackend* _backend);
		virtual void OnTerminate();

		virtual void DrawMesh(Mesh* _mesh, const glm::mat4& transform);
		virtual void DrawSubMesh(Mesh* _mesh, const uint32_t _subMeshID, const glm::mat4& transform);

		virtual void DrawMesh(Mesh* _mesh, MaterialInstance* _material, const glm::mat4& transform);
		virtual void DrawSubMesh(Mesh* _mesh, const uint32_t _subMeshID, MaterialInstance* _material, const glm::mat4& transform);

		virtual void DrawFullscreenRect(MaterialInstance* _material);

	private:
		RendererBackend*  m_RendererBackend = nullptr;

		Material*         m_DefaultMaterial = nullptr;
		MaterialInstance* m_DefaultMaterialInstance = nullptr;

		Material*		  m_FullscreenMaterial = nullptr;
	};
}