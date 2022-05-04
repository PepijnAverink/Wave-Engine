
#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>
#include "stdafx.h"



void Application::OnInitialize()
{
    // Create a basic window
    m_Window = new Window("GameEngine", 1280, 720);
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    m_Window->Show();


    m_RenderBackend = RendererBackend::Create(m_Window);


    // CommandPool
    CommandPoolDescriptor commandPoolDesc = {};
    commandPoolDesc.Name = "CommandPool";
    commandPoolDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

    m_CommandPool = m_RenderBackend->GetRenderDevice()->CreateCommandPool(&commandPoolDesc);

    // CommandBuffer
    CommandBufferDescriptor commandBufferDesc = {};
    commandBufferDesc.Name = "CommandBuffer";
    commandBufferDesc.Type = CommandBufferType::COMMAND_BUFFER_TYPE_DIRECT;
    commandBufferDesc.CommandPool = m_CommandPool;

    m_CommandBuffer = m_RenderBackend->GetRenderDevice()->CreateCommandBuffer(&commandBufferDesc);

    // Fences
    FenceDescriptor fenceDesc;
    fenceDesc.TimeOut = UINT64_MAX;

    fenceDesc.Name = "ExecuteFence";
    m_ExecuteFence = m_RenderBackend->GetRenderDevice()->CreateFence(&fenceDesc);

    fenceDesc.Name = "PresentFence";
    m_AquireFence = m_RenderBackend->GetRenderDevice()->CreateFence(&fenceDesc);

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

    m_RenderPass = m_RenderBackend->GetRenderDevice()->CreateRenderPass(&renderPassDesc);

    // FrameBuffer
    m_FrameBuffers.resize(RendererBackend::GetBackbufferCount());
    for (uint32_t i = 0; i < RendererBackend::GetBackbufferCount(); i++) {
        FrameBufferDescriptor frameBufferDesc = {};
        frameBufferDesc.Name        = "FrameBuffer" + i;
        frameBufferDesc.Width       = RendererBackend::GetClientWidth();
        frameBufferDesc.Height      = RendererBackend::GetClientHeight();
        frameBufferDesc.Contigious  = true;
        frameBufferDesc.Attachments = { {m_RenderBackend->GetSwapchain()->GetTextureViewAtIndex(i), FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
        frameBufferDesc.RenderPass  = m_RenderPass;

        m_FrameBuffers[i] = m_RenderBackend->GetRenderDevice()->CreateFrameBuffer(&frameBufferDesc);
    }

    // VertexShader
    ShaderDescriptor shaderDesc = {};
    shaderDesc.Name = "VertexShader";
    shaderDesc.Filepath = "../GameEngine/assets/vert.spv";
    shaderDesc.EntryPoint = "main";
    shaderDesc.Type = Graphics::ShaderType::SHADER_TYPE_VERTEX;

    Shader* vertexShader = m_RenderBackend->GetRenderDevice()->CreateShader(&shaderDesc);

    // PixelShader
    shaderDesc.Name = "PixelShader";
    shaderDesc.Filepath = "../GameEngine/assets/frag.spv";
    shaderDesc.EntryPoint = "main";
    shaderDesc.Type = Graphics::ShaderType::SHADER_TYPE_PIXEL;

    Shader* pixelShader = m_RenderBackend->GetRenderDevice()->CreateShader(&shaderDesc);

    // Create inputLayout
    InputLayoutDescriptor inputLayoutDesc = {};
    inputLayoutDesc.Name = "InputLayout";
    inputLayoutDesc.Layouts = { InputSet({ { "ModelMatrix", INPUT_TYPE_CONSTANT, SHADER_TYPE_FLAG_VERTEX, 0, sizeof(UniformBufferObject) }, }),
                                InputSet({ { "CameraMatrices", INPUT_TYPE_UNIFORM_BUFFER, SHADER_TYPE_FLAG_VERTEX, 0, 1 }, }), };

    m_InputLayout = m_RenderBackend->GetRenderDevice()->CreateInputLayout(&inputLayoutDesc);

    // Create graphicsPipeline
    GraphicsPipelineDescriptor graphicsPipelineDesc = {};
    graphicsPipelineDesc.Name = "GraphicsPipeline";
    graphicsPipelineDesc.CullMode = CullMode::CULL_MODE_BACK;
    graphicsPipelineDesc.FillMode = FillMode::FILL_MODE_SOLID;
    graphicsPipelineDesc.WindingOrder = WindingOrder::WINDING_ORDER_CCW;
    graphicsPipelineDesc.Topology = Topology::TOPOLOGY_TRIANGLE_LIST;
    graphicsPipelineDesc.Width = RendererBackend::GetClientWidth();
    graphicsPipelineDesc.Height = RendererBackend::GetClientHeight();
    graphicsPipelineDesc.VertexShader = vertexShader;
    graphicsPipelineDesc.PixelShader = pixelShader;
    graphicsPipelineDesc.InputLayout = m_InputLayout;
    graphicsPipelineDesc.RenderPass = m_RenderPass;
    graphicsPipelineDesc.VertexLayout = VertexLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT },
                                                       { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });

    m_GraphicsPipeline = m_RenderBackend->GetRenderDevice()->CreateGraphicsPipeline(&graphicsPipelineDesc);
    delete vertexShader;
    delete pixelShader;

    m_Mesh = new Cube(m_CommandBuffer, m_ExecuteFence);



   
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    /*m_Camera = new Perspective(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
        45.0f, 0.1f, 100.0f, m_Swapchain->GetWidth() / (float)m_Swapchain->GetHeight());*/
    m_Camera = new Orthographic(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2(-5.0f, 5.0f), glm::vec2(-5.0f, 5.0f), glm::vec2(0.1f, 10.0f));
    m_VP.view = m_Camera->GetViewMatrix();
    m_VP.proj = m_Camera->GetProjectionMatrix();
    m_VP.proj[1][1] *= -1;


    BufferDescriptor bufferDesc;
    bufferDesc = {};
    bufferDesc.Name = "UniformBuffer";
    bufferDesc.Size = sizeof(UniformBufferObject);
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_UNIFORM_BUFFER;
    bufferDesc.Data = &m_VP;
    bufferDesc.BufferLayout = BufferLayout({ { "EMMM",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, }); // CHange this

    m_UniformBuffer = m_RenderBackend->GetRenderDevice()->CreateBuffer(&bufferDesc);

    DescriptorPoolDescriptor poolDesc = {};
    poolDesc.Name = "DescriptorPool";
    poolDesc.MaxDescriptorSet = 1;
    poolDesc.Sizes = { {INPUT_TYPE_UNIFORM_BUFFER, 1}, };

    m_DescriptorPool = m_RenderBackend->GetRenderDevice()->CreateDescriptorPool(&poolDesc);

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
    delete m_Mesh;

    delete m_InputLayout;
    delete m_GraphicsPipeline;

    for (uint32_t i = 0; i < RendererBackend::GetBackbufferCount(); i++)
        delete m_FrameBuffers[i];

    delete m_RenderPass;

    delete m_AquireFence;
    delete m_ExecuteFence;

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


    
        RendererBackend::Present();
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
        viewPort.Width = RendererBackend::GetClientWidth();
        viewPort.Height = RendererBackend::GetClientHeight();
        viewPort.MinDepth = 0.0f;
        viewPort.MaxDepth = 1.0f;
    
        // ScissorRect
        ScissorRect scissorRect;
        scissorRect.X = 0;
        scissorRect.Y = 0;
        scissorRect.Width = RendererBackend::GetClientWidth();
        scissorRect.Height = RendererBackend::GetClientHeight();
    
        m_AquireFence->Reset();
        uint32_t imageIndex = RendererBackend::AquireNewFrame(m_AquireFence);
        m_AquireFence->WaitForFence();
    
        m_CommandBuffer->Reset();
        m_CommandPool->Reset();
    
        m_CommandBuffer->BeginRecording();
    
        float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        m_CommandBuffer->BeginRenderPass(m_RenderPass, m_FrameBuffers[imageIndex], RendererBackend::GetClientWidth(), RendererBackend::GetClientHeight(), clearColor);
    
        m_CommandBuffer->SetViewPort(&viewPort);
        m_CommandBuffer->SetScissorRect(&scissorRect);
    
        m_CommandBuffer->SetGraphicsPipeline(m_GraphicsPipeline);
    
        m_CommandBuffer->SetConstants(&model, 0, sizeof(glm::mat4), 0);
        m_CommandBuffer->SetDescriptorSet(m_DescriptorSet, 0);
    
        m_CommandBuffer->SetVertexBuffer(m_Mesh->GetVertexBuffer(), 0);
        m_CommandBuffer->SetIndexBuffer(m_Mesh->GetIndexBuffer());
    
        m_CommandBuffer->DrawIndexed(0, 0, m_Mesh->GetSubMeshes()[0].IndexCount);
        m_CommandBuffer->EndRenderPass();
    
        m_CommandBuffer->EndRecording();
    
        m_ExecuteFence->Reset();
        RendererBackend::SubmitCommandBuffer(m_CommandBuffer, m_ExecuteFence);
        m_ExecuteFence->WaitForFence();
    
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
    RendererBackend::Resize(_event.GetWidth(), _event.GetHeight());
    for (uint32_t i = 0; i < m_FrameBuffers.size(); i++)
    {
        delete m_FrameBuffers[i];

        FrameBufferDescriptor frameBufferDesc = {};
        frameBufferDesc.Name        = "FrameBuffer" + i;
        frameBufferDesc.Width       = RendererBackend::GetClientWidth();
        frameBufferDesc.Height      = RendererBackend::GetClientHeight();
        frameBufferDesc.Contigious  = true;
        frameBufferDesc.Attachments = { {m_RenderBackend->GetSwapchain()->GetTextureViewAtIndex(i), FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
        frameBufferDesc.RenderPass  = m_RenderPass;

        m_FrameBuffers[i] = m_RenderBackend->GetRenderDevice()->CreateFrameBuffer(&frameBufferDesc);
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
