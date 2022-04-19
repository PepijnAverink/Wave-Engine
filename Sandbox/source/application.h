#pragma once


using namespace Graphics;
class Application
{
public:
	Application() = default;

	void OnInitialize();
	void OnTerminate();

	void Run();

private:
	bool OnEvent(Event& _event);

	bool OnWindowCloseEvent();
	bool OnWindowResizeEvent(WindowResizeEvent& _event);

	Window* m_Window = nullptr;

	RenderDevice* m_RenderDevice = nullptr;
	Swapchain* m_Swapchain = nullptr;

	CommandQueue* m_CommandQueue = nullptr;
	CommandBuffer* m_CommandBuffer = nullptr;
	CommandPool* m_CommandPool = nullptr;

	Fence* m_ExecuteFence = nullptr;
	Fence* m_AquireFence = nullptr;

	RenderPass* m_RenderPass = nullptr;
	std::vector<FrameBuffer*> m_FrameBuffers;
	GraphicsPipeline* m_GraphicsPipeline = nullptr;
	InputLayout* m_InputLayout = nullptr;

	Buffer* m_VertexBuffer = nullptr;
	Buffer* m_IndexBuffer = nullptr;


	DescriptorPool* m_DescriptorPool = nullptr;
	DescriptorSet* m_DescriptorSet = nullptr;
	Buffer* m_UniformBuffer = nullptr;
};