//#include "./application.h"
//#include "./core/event/event_dispatcher.h"
//
#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>
#include "stdafx.h"


glm::mat4 model;

namespace App{
    struct Vertex {
        float pos[3];
        float color[3];
    };
}

std::vector<App::Vertex> vertices = {
    //front
    {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f }, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f  }, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f }, {1.0f, 1.0f, 1.0f}},
    ////back
    { {-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, -1.0f }, {0.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f  }, {0.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f }, {1.0f, 1.0f, 1.0f}}
};

std::vector<uint16_t> indices = {
    //front
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    //back
    7, 6, 5,
    5, 4, 7,
    // left
    4, 0, 3,
    3, 7, 4,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // top
    3, 2, 6,
    6, 7, 3
};

void Application::OnInitialize()
{
    // Create a basic window
    m_Window = new Window("GameEngine", 1280, 720);
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    m_Window->Show();


    // Graphics
    // --------------------------------
    RenderDeviceDescriptor renderDeviceDesc;
    renderDeviceDesc.Window = m_Window;
    renderDeviceDesc.API = GraphicsAPI::GRAPHICS_API_VULKAN;
    renderDeviceDesc.DebugMode = DebugMode::DEBUG_MODE_DEBUG_ONLY;

    m_RenderDevice = RenderDevice::Create(&renderDeviceDesc);

    // CommandQueue
    Graphics::CommandQueueDescriptor commandQueueDesc;
    commandQueueDesc.Name = "GeneralCommandQueue";
    commandQueueDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

    m_CommandQueue = m_RenderDevice->CreateCommandQueue(&commandQueueDesc);

    // Swapchain
    SwapchainDescriptor swapchainDesc;
    swapchainDesc.Name = "Swapchain";
    swapchainDesc.Window = m_Window;
    swapchainDesc.Width = m_Window->GetWidth();
    swapchainDesc.Height = m_Window->GetHeight();

    m_Swapchain = m_RenderDevice->CreateSwapchain(m_CommandQueue, &swapchainDesc);

    // CommandPool
    CommandPoolDescriptor commandPoolDesc = {};
    commandPoolDesc.Name = "CommandPool";
    commandPoolDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

    m_CommandPool = m_RenderDevice->CreateCommandPool(&commandPoolDesc);

    // CommandBuffer
    CommandBufferDescriptor commandBufferDesc = {};
    commandBufferDesc.Name = "CommandBuffer";
    commandBufferDesc.Type = CommandBufferType::COMMAND_BUFFER_TYPE_DIRECT;
    commandBufferDesc.CommandPool = m_CommandPool;

    m_CommandBuffer = m_RenderDevice->CreateCommandBuffer(&commandBufferDesc);

    // Fences
    FenceDescriptor fenceDesc;
    fenceDesc.TimeOut = UINT64_MAX;

    fenceDesc.Name = "ExecuteFence";
    m_ExecuteFence = m_RenderDevice->CreateFence(&fenceDesc);

    fenceDesc.Name = "PresentFence";
    m_AquireFence = m_RenderDevice->CreateFence(&fenceDesc);

    // RenderPass
    RenderPassDescriptor renderPassDesc = {};
    renderPassDesc.Name = "RenderPass";
    renderPassDesc.Attachments = { {
            RENDER_PASS_ATTACHMENT_TYPE_COLOR,
            RESOURCE_FORMAT_B8G8R8A8_SRGB,
            RENDER_PASS_LOAD_OP_CLEAR,
            RENDER_PASS_STORE_OP_STORE,
            RESOURCE_STATE_GENERAL_READ,
            RESOURCE_STATE_PRESENT
        }, };

    m_RenderPass = m_RenderDevice->CreateRenderPass(&renderPassDesc);

    // FrameBuffer
    m_FrameBuffers.resize(m_Swapchain->GetBufferCount());
    for (uint32_t i = 0; i < m_Swapchain->GetBufferCount(); i++) {
        FrameBufferDescriptor frameBufferDesc = {};
        frameBufferDesc.Name = "FrameBuffer" + i;
        frameBufferDesc.Width = m_Swapchain->GetWidth();
        frameBufferDesc.Height = m_Swapchain->GetHeight();
        frameBufferDesc.Contigious = true;
        frameBufferDesc.Attachments = { {m_Swapchain->GetTextureViewAtIndex(i), FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
        frameBufferDesc.RenderPass = m_RenderPass;

        m_FrameBuffers[i] = m_RenderDevice->CreateFrameBuffer(&frameBufferDesc);
    }

    // VertexShader
    ShaderDescriptor shaderDesc = {};
    shaderDesc.Name = "VertexShader";
    shaderDesc.Filepath = "../GameEngine/assets/vert.spv";
    shaderDesc.EntryPoint = "main";
    shaderDesc.Type = Graphics::ShaderType::SHADER_TYPE_VERTEX;

    Shader* vertexShader = m_RenderDevice->CreateShader(&shaderDesc);

    // PixelShader
    shaderDesc.Name = "PixelShader";
    shaderDesc.Filepath = "../GameEngine/assets/frag.spv";
    shaderDesc.EntryPoint = "main";
    shaderDesc.Type = Graphics::ShaderType::SHADER_TYPE_PIXEL;

    Shader* pixelShader = m_RenderDevice->CreateShader(&shaderDesc);

    // Create inputLayout
    InputLayoutDescriptor inputLayoutDesc = {};
    inputLayoutDesc.Name = "InputLayout";
    inputLayoutDesc.Layouts = { InputSet({ { "ModelMatrix", INPUT_TYPE_CONSTANT, SHADER_TYPE_FLAG_VERTEX, 0, sizeof(UniformBufferObject) }, }),
                                InputSet({ { "CameraMatrices", INPUT_TYPE_UNIFORM_BUFFER, SHADER_TYPE_FLAG_VERTEX, 0, 1 }, }), };

    m_InputLayout = m_RenderDevice->CreateInputLayout(&inputLayoutDesc);

    // Create graphicsPipeline
    GraphicsPipelineDescriptor graphicsPipelineDesc = {};
    graphicsPipelineDesc.Name = "GraphicsPipeline";
    graphicsPipelineDesc.CullMode = CullMode::CULL_MODE_BACK;
    graphicsPipelineDesc.FillMode = FillMode::FILL_MODE_SOLID;
    graphicsPipelineDesc.WindingOrder = WindingOrder::WINDING_ORDER_CCW;
    graphicsPipelineDesc.Topology = Topology::TOPOLOGY_TRIANGLE_LIST;
    graphicsPipelineDesc.Width = m_Swapchain->GetWidth();
    graphicsPipelineDesc.Height = m_Swapchain->GetHeight();
    graphicsPipelineDesc.VertexShader = vertexShader;
    graphicsPipelineDesc.PixelShader = pixelShader;
    graphicsPipelineDesc.InputLayout = m_InputLayout;
    graphicsPipelineDesc.RenderPass = m_RenderPass;
    graphicsPipelineDesc.VertexLayout = VertexLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT },
                                                       { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });

    m_GraphicsPipeline = m_RenderDevice->CreateGraphicsPipeline(&graphicsPipelineDesc);
    delete vertexShader;
    delete pixelShader;

    uint32_t bufferSizeV = sizeof(vertices[0]) * vertices.size();

    BufferDescriptor bufferDesc;
    bufferDesc.Name = "VertexStagingBuffer";
    bufferDesc.Size = bufferSizeV;
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
    bufferDesc.Data = vertices.data();
    bufferDesc.BufferLayout = BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
                                                       { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });

    Buffer* stagingBufferV = m_RenderDevice->CreateBuffer(&bufferDesc);

    bufferDesc = {};
    bufferDesc.Name = "VertexBuffer";
    bufferDesc.Size = bufferSizeV;
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_VERTEX_BUFFER;
    bufferDesc.Data = nullptr;
    bufferDesc.BufferLayout = BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
                                             { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });

    m_VertexBuffer = m_RenderDevice->CreateBuffer(&bufferDesc);

    uint32_t bufferSizeI = sizeof(indices[0]) * indices.size();

    bufferDesc = {};
    bufferDesc.Name = "IndexStagingBuffer";
    bufferDesc.Size = bufferSizeI;
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
    bufferDesc.Data = indices.data();
    bufferDesc.BufferLayout = BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, });

    Buffer* stagingBufferI = m_RenderDevice->CreateBuffer(&bufferDesc);

    bufferDesc = {};
    bufferDesc.Name = "IndexBuffer";
    bufferDesc.Size = bufferSizeI;
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_INDEX_BUFFER;
    bufferDesc.Data = nullptr;
    bufferDesc.BufferLayout = BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, });

    m_IndexBuffer = m_RenderDevice->CreateBuffer(&bufferDesc);

    m_CommandBuffer->BeginRecording();
    m_CommandBuffer->CopyBuffer(stagingBufferV, m_VertexBuffer, bufferSizeV);
    m_CommandBuffer->CopyBuffer(stagingBufferI, m_IndexBuffer, bufferSizeI);
    m_CommandBuffer->EndRecording();

    m_ExecuteFence->Reset();
    m_CommandQueue->SubmitCommandBuffer(m_CommandBuffer, m_ExecuteFence);
    m_ExecuteFence->WaitForFence();
    delete stagingBufferV;
    delete stagingBufferI;

   
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    m_VP.view = m_Camera->GetViewMatrix();/*glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
    m_VP.proj = glm::perspective(glm::radians(45.0f), m_Swapchain->GetWidth() / (float)m_Swapchain->GetHeight(), 0.1f, 100.0f);
    m_VP.proj[1][1] *= -1;

    bufferDesc = {};
    bufferDesc.Name = "UniformBuffer";
    bufferDesc.Size = sizeof(UniformBufferObject);
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_UNIFORM_BUFFER;
    bufferDesc.Data = &m_VP;
    bufferDesc.BufferLayout = BufferLayout({ { "EMMM",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, }); // CHange this

    m_UniformBuffer = m_RenderDevice->CreateBuffer(&bufferDesc);

    DescriptorPoolDescriptor poolDesc = {};
    poolDesc.Name = "DescriptorPool";
    poolDesc.MaxDescriptorSet = 1;
    poolDesc.Sizes = { {INPUT_TYPE_UNIFORM_BUFFER, 1}, };

    m_DescriptorPool = m_RenderDevice->CreateDescriptorPool(&poolDesc);

    DescriptorSetDescriptor setDesc = {};
    setDesc.Name = "DescriptorSet";
    setDesc.InputLayout = m_InputLayout;
    setDesc.SetIndex = 0;

    m_DescriptorSet = m_DescriptorPool->AllocateDescriptorSet(&setDesc);

    m_DescriptorSet->AllocateDescriptor(m_UniformBuffer, 0, 0);

    m_MouseX = 0.5 * m_Window->GetWidth();
    m_MouseY = 0.5 * m_Window->GetHeight();
}

void Application::OnTerminate()
{
    delete m_DescriptorSet;
    delete m_DescriptorPool;

    // Cleanup
    delete m_VertexBuffer;
    delete m_IndexBuffer;

    delete m_InputLayout;
    delete m_GraphicsPipeline;

    for (uint32_t i = 0; i < m_Swapchain->GetBufferCount(); i++)
        delete m_FrameBuffers[i];

    delete m_RenderPass;

    delete m_AquireFence;
    delete m_ExecuteFence;

    delete m_CommandBuffer;
    delete m_CommandPool;

    delete m_Swapchain;
    delete m_CommandQueue;

    delete m_RenderDevice;
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
       /* if (m_Camera->HasTranslationChanged())
            m_Camera->ApplyTranslation(elapsedTime);*/
       
        m_VP.view = m_Camera->GetViewMatrix();
        m_UniformBuffer->SetData(&m_VP, sizeof(UniformBufferObject));
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
    // ViewPort
    ViewPort viewPort;
    viewPort.X = 0.0f;
    viewPort.Y = 0.0f;
    viewPort.Width = m_Swapchain->GetWidth();
    viewPort.Height = m_Swapchain->GetHeight();
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    // ScissorRect
    ScissorRect scissorRect;
    scissorRect.X = 0;
    scissorRect.Y = 0;
    scissorRect.Width = m_Swapchain->GetWidth();
    scissorRect.Height = m_Swapchain->GetHeight();

    m_AquireFence->Reset();
    uint32_t imageIndex = m_Swapchain->AquireNewImage(m_CommandQueue, m_AquireFence);
    m_AquireFence->WaitForFence();

    m_CommandBuffer->Reset();
    m_CommandPool->Reset();

    m_CommandBuffer->BeginRecording();

    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_CommandBuffer->BeginRenderPass(m_RenderPass, m_FrameBuffers[imageIndex], m_Swapchain->GetWidth(), m_Swapchain->GetHeight(), clearColor);

    m_CommandBuffer->SetViewPort(&viewPort);
    m_CommandBuffer->SetScissorRect(&scissorRect);

    m_CommandBuffer->SetGraphicsPipeline(m_GraphicsPipeline);

    m_CommandBuffer->SetConstants(&model, 0, sizeof(glm::mat4), 0);
    m_CommandBuffer->SetDescriptorSet(m_DescriptorSet, 0);

    m_CommandBuffer->SetVertexBuffer(m_VertexBuffer, 0);
    m_CommandBuffer->SetIndexBuffer(m_IndexBuffer);

    m_CommandBuffer->DrawIndexed(0, 0, indices.size());
    m_CommandBuffer->EndRenderPass();

    m_CommandBuffer->EndRecording();

    m_ExecuteFence->Reset();
    m_CommandQueue->SubmitCommandBuffer(m_CommandBuffer, m_ExecuteFence);
    m_ExecuteFence->WaitForFence();

    m_Swapchain->Present(m_CommandQueue);
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
    m_Swapchain->Resize(m_CommandQueue, _event.GetWidth(), _event.GetHeight());
    for (uint32_t i = 0; i < m_FrameBuffers.size(); i++)
    {
        delete m_FrameBuffers[i];

        FrameBufferDescriptor frameBufferDesc = {};
        frameBufferDesc.Name = "FrameBuffer" + i;
        frameBufferDesc.Width = m_Swapchain->GetWidth();
        frameBufferDesc.Height = m_Swapchain->GetHeight();
        frameBufferDesc.Contigious = true;
        frameBufferDesc.Attachments = { {m_Swapchain->GetTextureViewAtIndex(i), FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
        frameBufferDesc.RenderPass = m_RenderPass;

        m_FrameBuffers[i] = m_RenderDevice->CreateFrameBuffer(&frameBufferDesc);
    }

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
        int xOffset = _event.GetX() - m_MouseX;
        int yOffset = _event.GetY() - m_MouseY;
        m_MouseX = _event.GetX();
        m_MouseY = _event.GetY();
        m_Camera->Rotate(xOffset, yOffset);
    }
    //Logger::Log(" Mouse Moves to: X: " + std::to_string(_event.GetX()) + ", Y: " + std::to_string(_event.GetY()), LOG_TYPE_INFO);

    return true;
}

bool Application::OnMouseLeftDown(MouseLeftDownEvent& _event)
{
    //Logger::Log(" Left Down to: X: " + std::to_string(_event.GetX()) + ", Y: " + std::to_string(_event.GetY()), LOG_TYPE_INFO);

    return true;
}

bool Application::OnMouseLeftUp(MouseLeftUpEvent& _event)
{
    //Logger::Log(" Left Up to: X: " + std::to_string(_event.GetX()) + ", Y: " + std::to_string(_event.GetY()), LOG_TYPE_INFO);
    m_FirstMouse = true;
    return true;
}

bool Application::OnMouseRightDown(MouseRightDownEvent& _event)
{
    //Logger::Log(" Right Down to: X: " + std::to_string(_event.GetX()) + ", Y: " + std::to_string(_event.GetY()), LOG_TYPE_INFO);

    return true;
}

bool Application::OnMouseRightUp(MouseRightUpEvent& _event)
{
    Logger::Log(" Right Up to: X: " + std::to_string(_event.GetX()) + ", Y: " + std::to_string(_event.GetY()), LOG_TYPE_INFO);

    return true;
}
