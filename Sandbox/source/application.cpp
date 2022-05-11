
#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>
#include "stdafx.h"

glm::mat4 model;


void Application::OnInitialize()
{
    // Create a basic window
    m_Window = new Window("GameEngine", 1280, 720);
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    m_Window->Show();


    m_RenderBackend = RendererBackend::Create(m_Window);

    // CommandPool
    {
        CommandPoolDescriptor commandPoolDesc = {};
        commandPoolDesc.Name = "CommandPool";
        commandPoolDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

        m_CommandPool = m_RenderBackend->GetRenderDevice()->CreateCommandPool(&commandPoolDesc);
    }

    // CommandBuffer
    {
        CommandBufferDescriptor commandBufferDesc = {};
        commandBufferDesc.Name = "CommandBuffer";
        commandBufferDesc.Type = CommandBufferType::COMMAND_BUFFER_TYPE_DIRECT;
        commandBufferDesc.CommandPool = m_CommandPool;

        m_CommandBuffer = m_RenderBackend->GetRenderDevice()->CreateCommandBuffer(&commandBufferDesc);
    }

    // Fences
    {
        FenceDescriptor fenceDesc;
        fenceDesc.Name    = "ExecuteFence";
        fenceDesc.TimeOut = UINT64_MAX;

        m_AquireFence = m_RenderBackend->GetRenderDevice()->CreateFence(&fenceDesc);
    }

    m_Renderer = new DefaultRenderer();
    m_Renderer->OnInitialize(m_RenderBackend);

    m_Mesh = new Cube(m_CommandBuffer, m_AquireFence);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    m_Camera = new Perspective(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
        45.0f, 0.1f, 100.0f, RendererBackend::GetClientWidth() / (float)RendererBackend::GetClientHeight());
   /* m_Camera = new Orthographic(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2(-5.0f, 5.0f), glm::vec2(-5.0f, 5.0f), glm::vec2(0.1f, 10.0f));*/

    m_MouseX = 0.5 * m_Window->GetWidth();
    m_MouseY = 0.5 * m_Window->GetHeight();
}

void Application::OnTerminate()
{
    // Cleanup
    delete m_Mesh;

    m_Renderer->OnTerminate();
    delete m_Renderer;

    delete m_AquireFence;

    delete m_CommandBuffer;
    delete m_CommandPool;

    RendererBackend::Destroy();
    delete m_Window;
}

void Application::Run()
{
    // Main loop, only closes when the window is shut down
    while (m_Window->ShouldClose() == false)
    {
        // Poll window events
        m_Window->PollEvents();
    
        OnUpdate();
        OnRender();
    }
}

void Application::OnUpdate()
{
    m_Timer.Tick();
    CalculateFrameStats();
    float elapsedTime = static_cast<float>(m_Timer.GetElapsedSeconds());
    // Update Camera
    if (m_Camera->HasChanged())
    {
        if (m_Camera->HasRotationChanged())
            m_Camera->ApplyRotation(elapsedTime);
        if (m_Camera->HasTranslationChanged())
            m_Camera->ApplyTranslation(elapsedTime);
    }
}

void Application::CalculateFrameStats()
{
    static int frameCount = 0;
    static double prevTime = 0.0;
    double totalTime = m_Timer.GetTotalSeconds();
    frameCount++;
    if ((totalTime - prevTime) > 1.0)
    {
        float diff = static_cast<float>(totalTime - prevTime);
        float fps = static_cast<float>(frameCount) / diff;
        frameCount = 0;
        prevTime = totalTime;
        std::wstring windowText = StringToWString(m_Window->GetTitle()) + L" | FPS:  " + 
            StringToWString(to_string_with_precision(fps, 2));
        SetWindowText(m_Window->GetWindowHandle(), windowText.c_str());

    }
}

void Application::OnRender()
{
        m_AquireFence->Reset();
        uint32_t imageIndex = RendererBackend::AquireNewFrame(m_AquireFence);
        m_AquireFence->WaitForFence();

        m_Renderer->BeginScene(m_Camera);
        m_Renderer->DrawMesh(m_Mesh, model);
        m_Renderer->EndScene();

        RendererBackend::Present();
}

bool Application::OnEvent(Event& _event)
{
    // Dispatch Window close event
    EventDispatcher dispatcher(_event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResizeEvent));
    dispatcher.Dispatch<KeyDownEvent>(BIND_EVENT_FN(Application::OnKeyDownEvent));
    dispatcher.Dispatch<KeyUpEvent>(BIND_EVENT_FN(Application::OnKeyUpEvent));
    dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT_FN(Application::OnMouseMoveEvent));
    dispatcher.Dispatch<MouseLeftDownEvent>(BIND_EVENT_FN(Application::OnMouseLeftDown));
    dispatcher.Dispatch<MouseLeftUpEvent>(BIND_EVENT_FN(Application::OnMouseLeftUp));
    dispatcher.Dispatch<MouseRightDownEvent>(BIND_EVENT_FN(Application::OnMouseRightDown));
    dispatcher.Dispatch<MouseRightUpEvent>(BIND_EVENT_FN(Application::OnMouseRightUp));
    return false;
}

bool Application::OnWindowResizeEvent(WindowResizeEvent& _event)
{
    RendererBackend::OnResize(_event.GetWidth(), _event.GetHeight());
    m_Renderer->OnResize(_event.GetWidth(), _event.GetHeight());
    return true;
}

bool Application::OnKeyDownEvent(KeyDownEvent& _event)
{
    switch (_event.GetKey())
    {
    case 'W':
        m_Camera->MoveForward();
        break;
    case 'S':
        m_Camera->MoveBackward();
        break;
    case 'A':
        m_Camera->MoveLeft();
        break;
    case 'D':
        m_Camera->MoveRight();
        break;
    }
    return true;
}

bool Application::OnKeyUpEvent(KeyUpEvent& _event)
{
    //Logger::Log(std::to_string(_event.GetKey()) + " was released", LOG_TYPE_INFO);
    return true;
}

bool Application::OnMouseMoveEvent(MouseMoveEvent& _event)
{
    if (_event.GetState() == MouseMoveEvent::State::LEFT_BUTTON)
    {
        if (m_FirstMouse)
        {
            m_MouseX = _event.GetX();
            m_MouseY = _event.GetY();
            m_FirstMouse = false;
        }
        else
        {
            int xOffset =  m_MouseX - _event.GetX();
            int yOffset =  _event.GetY() - m_MouseY;
            m_MouseX = _event.GetX();
            m_MouseY = _event.GetY();
            m_Camera->Rotate(xOffset, yOffset);
           
        }
        
    }

    return true;
}

bool Application::OnMouseLeftDown(MouseLeftDownEvent& _event)
{

    return true;
}

bool Application::OnMouseLeftUp(MouseLeftUpEvent& _event)
{
    m_FirstMouse = true;
    return true;
}

bool Application::OnMouseRightDown(MouseRightDownEvent& _event)
{

    return true;
}

bool Application::OnMouseRightUp(MouseRightUpEvent& _event)
{
    Logger::Log(" Right Up to: X: " + std::to_string(_event.GetX()) + ", Y: " + std::to_string(_event.GetY()), LOG_TYPE_INFO);

    return true;
}
