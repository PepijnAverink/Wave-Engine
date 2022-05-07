#pragma once
//#include "./graphics/renderer/renderer_backend.h"
//
//#include "./graphics/renderer/material/material_instance.h"
//#include "./graphics/renderer/model/mesh.h"

#include "../dependencies/include/glm/glm.hpp"

namespace Graphics
{
	class Fence;
	class CommandPool;
	class CommandBuffer;

	class RenderPass;
	class FrameBuffer;
	class GraphicsPipeline;
	class InputLayout;

	class Mesh;
	class Camera;

	class RendererBackend;
	class Renderer3D
	{
	public:
		virtual void OnInitialize(RendererBackend* _backend);
		virtual void OnTerminate();

		virtual void OnResize(const uint32_t _width, const uint32_t _height) = 0;

		virtual void BeginScene(Graphics::Camera* _camera) = 0;
		virtual void EndScene() = 0;

		virtual void DrawMesh(Mesh* _mesh, const glm::mat4& transform) {}
		virtual void DrawSubMesh(Mesh* _mesh, const uint32_t _subMeshID, const glm::mat4& transform) {}

	protected:
		RendererBackend*  m_RendererBackend = nullptr;

		Material*         m_DefaultMaterial			= nullptr;
		MaterialInstance* m_DefaultMaterialInstance = nullptr;
	};
}