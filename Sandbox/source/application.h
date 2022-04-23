#pragma once
//#include "./core/window/window.h"
//
//#include "./graphics/api/interface/render_device.h"
//#include "./graphics/api/interface/object/command/command_queue.h"
//#include "./graphics/api/interface/object/swapchain/swapchain.h"
//#include "./graphics/api/interface/object/command/command_pool.h"
//#include "./graphics/api/interface/object/command/command_buffer.h"
//#include "./graphics/api/interface/object/sync/fence.h"
//
//#include "./graphics/api/interface/pipeline/renderpass/render_pass.h"
//#include "./graphics/api/interface/pipeline/framebuffer/frame_buffer.h"
//#include "./graphics/api/interface/pipeline/graphics/graphics_pipeline.h"
//#include "./graphics/api/interface/pipeline/layout/input_layout.h"
//
//#include "./graphics/api/interface/resource/shader/shader.h"
//#include "./graphics/api/interface/resource/buffer/buffer.h"
//
//#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_pool.h"
//#include "./graphics/api/interface/pipeline/layout/descriptor/descriptor_set.h"
//
//#include "./core/event/window/window_resize_event.h"

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
	bool OnKeyDownEvent(KeyDownEvent& _event);
	bool OnKeyUpEvent(KeyUpEvent& _event);
	bool OnMouseMoveEvent(MouseMoveEvent& _event);
	bool OnMouseLeftDown(MouseLeftDownEvent& _event);
	bool OnMouseLeftUp(MouseLeftUpEvent& _event);
	bool OnMouseRightDown(MouseRightDownEvent& _event);
	bool OnMouseRightUp(MouseRightUpEvent& _event);




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