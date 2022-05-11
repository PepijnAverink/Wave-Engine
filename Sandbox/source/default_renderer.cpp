#include "default_renderer.h"
#include "stdafx.h"

void DefaultRenderer::OnInitialize(Graphics::RendererBackend* _backend)
{
	// Initalizing base of Render3D...
    // --------------------------------------------------------------------
	Graphics::Renderer3D::OnInitialize(_backend);
    Graphics::RenderDevice* lDevice = m_RendererBackend->GetRenderDevice();

    // CommandPool
    // --------------------------------------------------------------------
    CommandPoolDescriptor commandPoolDesc = {};
    commandPoolDesc.Name = "CommandPool";
    commandPoolDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

    m_CommandPool = lDevice->CreateCommandPool(&commandPoolDesc);

    // CommandBuffer
    // --------------------------------------------------------------------
    CommandBufferDescriptor commandBufferDesc = {};
    commandBufferDesc.Name = "CommandBuffer";
    commandBufferDesc.Type = CommandBufferType::COMMAND_BUFFER_TYPE_DIRECT;
    commandBufferDesc.CommandPool = m_CommandPool;

    m_CommandBuffer = lDevice->CreateCommandBuffer(&commandBufferDesc);
    

    // Fences
    // --------------------------------------------------------------------
    FenceDescriptor fenceDesc;
    fenceDesc.Name    = "ExecuteFence";
    fenceDesc.TimeOut = UINT64_MAX;

    m_Fence = lDevice->CreateFence(&fenceDesc);

    // RenderPass
    // --------------------------------------------------------------------
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

    m_RenderPass = lDevice->CreateRenderPass(&renderPassDesc);

    // FrameBuffer
    // --------------------------------------------------------------------
    m_FrameBuffers.resize(RendererBackend::GetBackbufferCount());
    for (uint32_t i = 0; i < RendererBackend::GetBackbufferCount(); i++) {
        FrameBufferDescriptor frameBufferDesc = {};
        frameBufferDesc.Name   = "FrameBuffer" + i;
        frameBufferDesc.Width  = RendererBackend::GetClientWidth();
        frameBufferDesc.Height = RendererBackend::GetClientHeight();
        frameBufferDesc.Contigious  = true;
        frameBufferDesc.Attachments = { {m_RendererBackend->GetSwapchain()->GetTextureAtIndex(i), FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
        frameBufferDesc.RenderPass  = m_RenderPass;

        m_FrameBuffers[i] = lDevice->CreateFrameBuffer(&frameBufferDesc);
    }

    // VertexShader
    // --------------------------------------------------------------------
    ShaderDescriptor shaderDesc = {};
    shaderDesc.Name       = "VertexShader";
    shaderDesc.Filepath   = "../GameEngine/assets/vert.spv";
    shaderDesc.EntryPoint = "main";
    shaderDesc.Type = Graphics::ShaderType::SHADER_TYPE_VERTEX;

    Shader* vertexShader = lDevice->CreateShader(&shaderDesc);

    // PixelShader
    // --------------------------------------------------------------------
    shaderDesc.Name       = "PixelShader";
    shaderDesc.Filepath   = "../GameEngine/assets/frag.spv";
    shaderDesc.EntryPoint = "main";
    shaderDesc.Type = Graphics::ShaderType::SHADER_TYPE_PIXEL;

    Shader* pixelShader = lDevice->CreateShader(&shaderDesc);

    // Create inputLayout
    // --------------------------------------------------------------------
    InputLayoutDescriptor inputLayoutDesc = {};
    inputLayoutDesc.Name    = "InputLayout";
    inputLayoutDesc.Layouts = { InputSet({ { "CameraMatrices", INPUT_TYPE_CONSTANT, SHADER_TYPE_FLAG_VERTEX, 0, sizeof(glm::mat4) * 3 }, }),
                                InputSet({ { "ModelMatrix", INPUT_TYPE_SAMPLER2D, SHADER_TYPE_FLAG_PIXEL, 0, 1}, }) };

    m_InputLayout = lDevice->CreateInputLayout(&inputLayoutDesc);

    // Create graphicsPipeline
    // --------------------------------------------------------------------
    GraphicsPipelineDescriptor graphicsPipelineDesc = {};
    graphicsPipelineDesc.Name         = "GraphicsPipeline";
    graphicsPipelineDesc.CullMode     = CullMode::CULL_MODE_BACK;
    graphicsPipelineDesc.FillMode     = FillMode::FILL_MODE_SOLID;
    graphicsPipelineDesc.WindingOrder = WindingOrder::WINDING_ORDER_CCW;
    graphicsPipelineDesc.Topology     = Topology::TOPOLOGY_TRIANGLE_LIST;
    graphicsPipelineDesc.Width        = RendererBackend::GetClientWidth();
    graphicsPipelineDesc.Height       = RendererBackend::GetClientHeight();
    graphicsPipelineDesc.VertexShader = vertexShader;
    graphicsPipelineDesc.PixelShader  = pixelShader;
    graphicsPipelineDesc.InputLayout  = m_InputLayout;
    graphicsPipelineDesc.RenderPass   = m_RenderPass;
    graphicsPipelineDesc.VertexLayout = VertexLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT },
                                                       { "TEXCOORD",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT }, });

    m_GraphicsPipeline = lDevice->CreateGraphicsPipeline(&graphicsPipelineDesc);
    delete vertexShader;
    delete pixelShader;


    // Create texture
// ----------------------------------------------------------------------------
    Texture2DDescriptor texture2DDesc = {};
    texture2DDesc.Name = "TestTexture2D";
    texture2DDesc.Width = 16;
    texture2DDesc.Height = 16;
    texture2DDesc.Format = ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_SRGB;
    texture2DDesc.State = ResourceState::RESOURCE_STATE_GENERAL_WRITE;

    m_Texture = lDevice->CreateTexture2D(&texture2DDesc);

    // Texture data
    std::vector<char> data;
    
    for (uint32_t y = 0; y < 16; y++)
    {
        for (uint32_t x = 0; x < 16; x++)
        {
            char r = (x + y) % 6 == 0 ? 255 : (x + y) % 6 == 1 ? 127 : 0;
            char g = (x + y) % 6 == 2 ? 255 : (x + y) % 6 == 3 ? 127 : 0;
            char b = (x + y) % 6 == 4 ? 255 : (x + y) % 6 == 5 ? 127 : 0;
            data.push_back(r);
            data.push_back(g);
            data.push_back(b);
            data.push_back(255);
        }
    }

    // Staging buffer
    BufferDescriptor bufferDesc;
    bufferDesc.Name = "Generated-IndexStagingBuffer";
    bufferDesc.Size = sizeof(char) * 4 * 16 * 16;
    bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
    bufferDesc.Usage = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
    bufferDesc.Data = data.data();
    bufferDesc.BufferLayout = BufferLayout({ { "TBUFFER",  Graphics::ResourceFormat::RESOURCE_FORMAT_B8G8R8A8_SRGB }, });

    Buffer* buffer = lDevice->CreateBuffer(&bufferDesc);

    m_CommandBuffer->BeginRecording();
    m_CommandBuffer->TransitionTexture(m_Texture, ResourceState::RESOURCE_STATE_UNDEFINED, ResourceState::RESOURCE_STATE_GENERAL_WRITE);
    m_CommandBuffer->CopyBuffer(buffer, m_Texture);
    m_CommandBuffer->TransitionTexture(m_Texture, ResourceState::RESOURCE_STATE_GENERAL_WRITE, ResourceState::RESOURCE_STATE_SHADER_READ_ONLY);
    m_CommandBuffer->EndRecording();

    m_Fence->Reset();
    RendererBackend::SubmitCommandBuffer(m_CommandBuffer, m_Fence);
    m_Fence->WaitForFence();
    delete buffer;

    Sampler2DDescriptor samplerDesc;
    samplerDesc.Name     = "Sampler";
    samplerDesc.Filter   = FilterMode::FILTER_MODE_NEAREST;
    samplerDesc.AddressU = AddressMode::ADDRESS_MODE_REPEAT;
    samplerDesc.AddressV = AddressMode::ADDRESS_MODE_REPEAT;
    samplerDesc.AddressW = AddressMode::ADDRESS_MODE_REPEAT;

    m_Sampler = lDevice->CreateSampler2D(&samplerDesc);

    DescriptorPoolDescriptor poolDesc = {};
    poolDesc.Name = "DescriptorPool";
    poolDesc.MaxDescriptorSet = 1;
    poolDesc.Sizes = { {INPUT_TYPE_SAMPLER2D, 1}, };

    m_DescriptorPool = lDevice->CreateDescriptorPool(&poolDesc);

    DescriptorSetDescriptor setDesc = {};
    setDesc.Name = "DescriptorSet";
    setDesc.InputLayout = m_InputLayout;
    setDesc.SetIndex = 0;

    m_DescriptorSet = m_DescriptorPool->AllocateDescriptorSet(&setDesc);

    m_DescriptorSet->AllocateDescriptor(m_Texture, m_Sampler, 0, 0);
}

void DefaultRenderer::OnTerminate()
{
    delete m_DescriptorSet;
    delete m_DescriptorPool;

    delete m_Texture;
    delete m_Sampler;

    delete m_InputLayout;
    delete m_GraphicsPipeline;

    for (uint32_t i = 0; i < RendererBackend::GetBackbufferCount(); i++)
        delete m_FrameBuffers[i];

    delete m_RenderPass;

    delete m_Fence;
    delete m_CommandBuffer;
    delete m_CommandPool;
}

void DefaultRenderer::OnResize(const uint32_t _width, const uint32_t _height)
{
    for (uint32_t i = 0; i < m_FrameBuffers.size(); i++)
    {
        delete m_FrameBuffers[i];

        FrameBufferDescriptor frameBufferDesc = {};
        frameBufferDesc.Name = "FrameBuffer" + i;
        frameBufferDesc.Width = RendererBackend::GetClientWidth();
        frameBufferDesc.Height = RendererBackend::GetClientHeight();
        frameBufferDesc.Contigious = true;
        frameBufferDesc.Attachments = { {m_RendererBackend->GetSwapchain()->GetTextureAtIndex(i), FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
        frameBufferDesc.RenderPass = m_RenderPass;

        m_FrameBuffers[i] = m_RendererBackend->GetRenderDevice()->CreateFrameBuffer(&frameBufferDesc);
    }
}

void DefaultRenderer::BeginScene(Graphics::Camera* _camera)
{
    // ViewPort
    ViewPort viewPort;
    viewPort.X        = 0.0f;
    viewPort.Y        = 0.0f;
    viewPort.Width    = RendererBackend::GetClientWidth();
    viewPort.Height   = RendererBackend::GetClientHeight();
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    // ScissorRect
    ScissorRect scissorRect;
    scissorRect.X = 0;
    scissorRect.Y = 0;
    scissorRect.Width = RendererBackend::GetClientWidth();
    scissorRect.Height = RendererBackend::GetClientHeight();


    // Retreives the current index of the swapchain buffer
    uint32_t index = m_RendererBackend->GetCurrntBackbufferIndex();

    m_CommandBuffer->Reset();
    m_CommandPool->Reset();

    m_CommandBuffer->BeginRecording();

    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_CommandBuffer->BeginRenderPass(m_RenderPass, m_FrameBuffers[index], RendererBackend::GetClientWidth(), RendererBackend::GetClientHeight(), clearColor);

    m_CommandBuffer->SetViewPort(&viewPort);
    m_CommandBuffer->SetScissorRect(&scissorRect);

    m_CommandBuffer->SetGraphicsPipeline(m_GraphicsPipeline);

    // Set view and projection matrices
    glm::mat4 view = _camera->GetViewMatrix();
    glm::mat4 proj = _camera->GetProjectionMatrix();
    m_CommandBuffer->SetConstants(&view, 0, sizeof(glm::mat4), 0);
    m_CommandBuffer->SetConstants(&proj, sizeof(glm::mat4), sizeof(glm::mat4), 0);

    m_CommandBuffer->SetDescriptorSet(m_DescriptorSet, 0);
}

void DefaultRenderer::EndScene()
{
    m_CommandBuffer->EndRenderPass();
    m_CommandBuffer->EndRecording();

    m_Fence->Reset();
    RendererBackend::SubmitCommandBuffer(m_CommandBuffer, m_Fence);
    m_Fence->WaitForFence();
}

void DefaultRenderer::DrawMesh(Graphics::Mesh* _mesh, const glm::mat4& transform)
{
    glm::mat4 mat = transform;
    m_CommandBuffer->SetConstants(&mat, sizeof(glm::mat4) * 2, sizeof(glm::mat4), 0);

    m_CommandBuffer->SetVertexBuffer(_mesh->GetVertexBuffer(), 0);
    m_CommandBuffer->SetIndexBuffer(_mesh->GetIndexBuffer());

    std::vector<SubMesh> meshes = _mesh->GetSubMeshes();
    for (uint32_t i = 0; i < meshes.size(); i++)
        m_CommandBuffer->DrawIndexed(meshes[i].VertexOffset, meshes[i].IndexOffset, meshes[i].IndexCount);
}

void DefaultRenderer::DrawSubMesh(Graphics::Mesh* _mesh, const uint32_t _subMeshID, const glm::mat4& transform)
{
    if (_mesh->GetSubmeshCount() < _subMeshID)
    {
        Logger::Log("User tried to draw submesh, index out of bounds...", LogType::LOG_TYPE_ERROR);
        return;
    }

    glm::mat4 mat = transform;
    m_CommandBuffer->SetConstants(&mat, sizeof(glm::mat4) * 2, sizeof(glm::mat4), 0);

    m_CommandBuffer->SetVertexBuffer(_mesh->GetVertexBuffer(), 0);
    m_CommandBuffer->SetIndexBuffer(_mesh->GetIndexBuffer());

    Graphics::SubMesh sm = _mesh->GetSubMeshes()[_subMeshID];
    m_CommandBuffer->DrawIndexed(sm.VertexOffset, sm.IndexOffset, sm.IndexCount);
}
