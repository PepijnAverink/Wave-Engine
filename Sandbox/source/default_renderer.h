#pragma once
#include "./graphics/renderer/renderer3D.h"
#include <vector>

class DefaultRenderer : public Graphics::Renderer3D
{
public:
	virtual void OnInitialize(Graphics::RendererBackend* _backend) override;
	virtual void OnTerminate() override;

	virtual void OnResize(const uint32_t _width, const uint32_t _height) override;

	virtual void BeginScene(Graphics::Camera* _camera) override;
	virtual void EndScene() override;

	virtual void DrawMesh(Graphics::Mesh* _mesh, const glm::mat4& transform) override;
	virtual void DrawSubMesh(Graphics::Mesh* _mesh, const uint32_t _subMeshID, const glm::mat4& transform) override;

private:
	Graphics::CommandPool*   m_CommandPool   = nullptr;
	Graphics::CommandBuffer* m_CommandBuffer = nullptr;

	Graphics::Fence* m_Fence = nullptr;

	Graphics::RenderPass*  m_RenderPass  = nullptr;
	Graphics::InputLayout* m_InputLayout = nullptr;
	Graphics::GraphicsPipeline* m_GraphicsPipeline = nullptr;

	std::vector<Graphics::FrameBuffer*> m_FrameBuffers;

	Graphics::Sampler2D* m_Sampler = nullptr;
	Graphics::Texture2D* m_Texture = nullptr;

	Graphics::DescriptorPool* m_DescriptorPool = nullptr;
	Graphics::DescriptorSet* m_DescriptorSet = nullptr;
};