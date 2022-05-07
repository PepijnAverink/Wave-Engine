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

	Fence* m_AquireFence = nullptr;

	Mesh* m_Mesh         = nullptr;

	RendererBackend* m_RenderBackend = nullptr;
	Renderer3D* m_Renderer = nullptr;

	Graphics::CommandPool* m_CommandPool = nullptr;
	Graphics::CommandBuffer* m_CommandBuffer = nullptr;

	int m_MouseX, m_MouseY;
	bool m_FirstMouse = true;
};