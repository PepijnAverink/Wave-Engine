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

	void OnUpdate();
	void OnRender();

	void CalculateFrameStats();

	bool OnEvent(Event& _event);
	bool OnWindowCloseEvent();
	bool OnWindowResizeEvent(WindowResizeEvent& _event);
	bool OnKeyDownEvent(KeyDownEvent& _event);
	bool OnKeyUpEvent(KeyUpEvent& _event);
	bool OnMouseMoveEvent(MouseMoveEvent& _event);
	bool OnMouseLeftDown(MouseLeftDownEvent& _event);
	bool OnMouseLeftUp(MouseLeftUpEvent& _event);
	bool OnMouseRightDown(MouseRightDownEvent& _event);
	bool OnMouseRightUp(MouseRightUpEvent& _event);

	

	Timer m_Timer;
	Camera* m_Camera =  nullptr;

	Window* m_Window = nullptr;

	CommandBuffer* m_CommandBuffer = nullptr;
	CommandPool* m_CommandPool = nullptr;

	Fence* m_ExecuteFence = nullptr;
	Fence* m_AquireFence = nullptr;

	RenderPass* m_RenderPass = nullptr;
	std::vector<FrameBuffer*> m_FrameBuffers;
	GraphicsPipeline* m_GraphicsPipeline = nullptr;
	InputLayout* m_InputLayout = nullptr;

	Mesh* m_Mesh = nullptr;

	RendererBackend* m_RenderBackend = nullptr;

	DescriptorPool* m_DescriptorPool = nullptr;
	DescriptorSet* m_DescriptorSet = nullptr;
	Buffer* m_UniformBuffer = nullptr;
	struct UniformBufferObject {
		glm::mat4 view;
		glm::mat4 proj;
	}m_VP;

	int m_MouseX, m_MouseY;
	bool m_FirstMouse = true;
};