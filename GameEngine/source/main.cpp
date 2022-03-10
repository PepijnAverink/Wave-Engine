//#include "./core/window/window.h"
//
//#include "./graphics/api/vulkan/vk_render_device.h"
//#include "./graphics/api/interface/resource/shader/shader.h"
//#include "./graphics/api/interface/object/command/command_queue.h"
//#include "./graphics/api/interface/object/command/command_pool.h"
//#include "./graphics/api/interface/object/command/command_buffer.h"
//#include "./graphics/api/interface/object/swapchain/swapchain.h"
//#include "./graphics/api/interface/pipeline/graphics/graphics_pipeline.h"
//#include "./graphics/api/interface/resource/view/texture_view.h"
//#include "./graphics/api/interface/resource/resource_format.h"
//#include "./graphics/api/interface/pipeline/renderpass/render_pass.h"
//#include "./graphics/api/interface/pipeline/framebuffer/frame_buffer.h"
//#include "./graphics/api/interface/resource/buffer/buffer.h"
//#include "./graphics/api/interface/object/sync/fence.h"
//
//
//struct Vertex {
//    float pos[2];
//    float color[3];
//};
//
//std::vector<Vertex> vertices = {
//    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
//    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
//    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
//};
//
//std::vector<uint16_t> indices = {
//    0, 1, 2, 2, 3, 0
//};
//
//class HelloTriangleApplication {
//public:
//    void run() {
//        initWindow();
//        initVulkan();
//        mainLoop();
//        cleanup();
//    }
//
//private:
//    Window* window;
//    Graphics::RenderDevice* renderDevice = nullptr;
//
//    Graphics::CommandQueue* commandQueue = nullptr;
//    Graphics::Swapchain* swapchain = nullptr;
//
//    Graphics::RenderPass* renderPass = nullptr;
//
//    std::vector<Graphics::FrameBuffer*> swapChainFramebuffers;
//    Graphics::GraphicsPipeline* graphicsPipeline;
//
//    Graphics::CommandPool* commandPool;
//    std::vector<Graphics::CommandBuffer*> commandBuffers;
//
//    Graphics::Buffer* vertexBuffer;
//    Graphics::Buffer* indexBuffer;
//
//    Graphics::Fence* executeFence;
//    Graphics::Fence* presentFence;
//
//    bool framebufferResized = false;
//
//    void initWindow() {
//
//        window = new Window("GameEngine", 1280, 720);
//        window->Show();
//
//        Graphics::RenderDeviceDescriptor renderDeviceDesc = {};
//        renderDeviceDesc.Window    = window;
//        renderDeviceDesc.API       = Graphics::GraphicsAPI::GRAPHICS_API_VULKAN;
//        renderDeviceDesc.DebugMode = Graphics::DebugMode::DEBUG_MODE_DEBUG_ONLY;
//
//        renderDevice = Graphics::RenderDevice::Create(&renderDeviceDesc);
//    }
//
//    static void framebufferResizeCallback(Window* window, int width, int height) {
//        auto app = reinterpret_cast<HelloTriangleApplication*>(window);
//        app->framebufferResized = true;
//    }
//
//    void initVulkan() {
//        createLogicalDevice();
//        createFramebuffers();
//        createGraphicsPipeline();
//        createCommandPool();
//        createCommandBuffers();
//        createSyncObjects();
//        createVertexBuffer();
//        createIndexBuffer();
//        FillCommandBuffer();
//    }
//
//    void mainLoop() {
//        while (!window->ShouldClose()) {
//            window->PollEvents();
//            drawFrame();
//        }
//    }
//
//    void cleanupSwapChain() {
//        for (int i = 0; i < swapChainFramebuffers.size(); i++)
//        {
//            delete swapChainFramebuffers[i];
//        }
//
//       // vkFreeCommandBuffers(renderDevice->GetDevice(), commandPool->GetVKCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
//        for (int i = 0; i < commandBuffers.size(); i++)
//            delete commandBuffers[i];
//
//        delete graphicsPipeline;
//    }
//
//    void cleanup() {
//        cleanupSwapChain();
//
//        delete indexBuffer;
//        delete vertexBuffer;
//
//        delete executeFence;
//        delete presentFence;
//
//        delete renderPass;
//
//        delete swapchain;
//
//        delete commandPool;
//        delete commandQueue;
//        delete renderDevice;
//        delete window;
//    }
//
//    void createLogicalDevice() {
//        Graphics::CommandQueueDescriptor commandQueueDesc = {};
//        commandQueueDesc.Name = "GeneralCommandQueue";
//        commandQueueDesc.Type = Graphics::CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;
//
//        commandQueue = renderDevice->CreateCommandQueue(&commandQueueDesc);
//
//        Graphics::SwapchainDescriptor swapchainDesc = {};
//        swapchainDesc.Name   = "Swapchain";
//        swapchainDesc.Window = window;
//        swapchainDesc.Width  = 1280;
//        swapchainDesc.Height = 720;
//
//        swapchain = renderDevice->CreateSwapchain(commandQueue, &swapchainDesc);
//
//        Graphics::RenderPassDescriptor renderPassDesc = {};
//        renderPassDesc.Name = "RenderPass";
//        renderPassDesc.Attachments = {  {
//                Graphics::RENDER_PASS_ATTACHMENT_TYPE_COLOR, 
//                Graphics::RESOURCE_FORMAT_B8G8R8A8_SRGB, 
//                Graphics::RENDER_PASS_LOAD_OP_CLEAR, 
//                Graphics::RENDER_PASS_STORE_OP_STORE,
//                Graphics::RESOURCE_STATE_GENERAL_READ, 
//                Graphics::RESOURCE_STATE_PRESENT 
//            },};
//
//        renderPass = renderDevice->CreateRenderPass(&renderPassDesc);
//    }
//
//    void createGraphicsPipeline() 
//    {
//        Graphics::ShaderDescriptor shaderDesc = {};
//        shaderDesc.Name       = "VertexShader";
//        shaderDesc.Filepath   = "assets/vert.spv";
//        shaderDesc.EntryPoint = "main";
//        shaderDesc.Type       = Graphics::ShaderType::SHADER_TYPE_VERTEX;
//
//        Graphics::Shader* vertexShader = renderDevice->CreateShader(&shaderDesc);
//
//        //shaderDesc = {};
//        shaderDesc.Name       = "PixelShader";
//        shaderDesc.Filepath   = "assets/frag.spv";
//        shaderDesc.EntryPoint = "main";
//        shaderDesc.Type       = Graphics::ShaderType::SHADER_TYPE_PIXEL;
//
//        Graphics::Shader* pixelShader = renderDevice->CreateShader(&shaderDesc);
//
//        Graphics::ViewPort viewPort;
//        viewPort.X        = 0.0f;
//        viewPort.Y        = 0.0f;
//        viewPort.Width    = window->GetWidth();
//        viewPort.Height   = window->GetHeight();
//        viewPort.MinDepth = 0.0f;
//        viewPort.MaxDepth = 1.0f;
//
//        Graphics::ScissorRect scissorRect;
//        scissorRect.X      = 0;
//        scissorRect.Y      = 0;
//        scissorRect.Width  = window->GetWidth();
//        scissorRect.Height = window->GetHeight();
//
//        Graphics::GraphicsPipelineDescriptor graphicsPipelineDesc = {};
//        graphicsPipelineDesc.Name         = "GraphicsPipeline";
//        graphicsPipelineDesc.CullMode     = Graphics::CullMode::CULL_MODE_BACK;
//        graphicsPipelineDesc.FillMode     = Graphics::FillMode::FILL_MODE_SOLID;
//        graphicsPipelineDesc.WindingOrder = Graphics::WindingOrder::WINDING_ORDER_CW;
//        graphicsPipelineDesc.Topology     = Graphics::Topology::TOPOLOGY_TRIANGLE_LIST;
//        graphicsPipelineDesc.Width        = window->GetWidth();
//        graphicsPipelineDesc.Height       = window->GetHeight();
//        graphicsPipelineDesc.ViewPort     = viewPort;
//        graphicsPipelineDesc.ScissorRect  = scissorRect;
//        graphicsPipelineDesc.VertexShader = vertexShader;
//        graphicsPipelineDesc.PixelShader  = pixelShader;
//        graphicsPipelineDesc.RenderPass   = renderPass;
//        graphicsPipelineDesc.VertexLayout = Graphics::VertexLayout({ { "POS",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
//   																	 { "COLOR",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });
//
//        graphicsPipeline = renderDevice->CreateGraphicsPipeline(&graphicsPipelineDesc);
//
//        delete vertexShader;
//        delete pixelShader;
//    }
//
//    void createFramebuffers() {
//        swapChainFramebuffers.resize(swapchain->GetBufferCount());
//
//        for (size_t i = 0; i < swapchain->GetBufferCount(); i++) {
//            Graphics::FrameBufferDescriptor frameBufferDesc = {};
//            frameBufferDesc.Name        = "FrameBuffer"+i;
//            frameBufferDesc.Width       = swapchain->GetWidth();
//            frameBufferDesc.Height      = swapchain->GetHeight();
//            frameBufferDesc.Contigious  = true;
//            frameBufferDesc.Attachments = { {swapchain->GetTextureViewAtIndex(i), Graphics::FrameBufferAttachmentType::FRAME_BUFFER_ATTACHMENT_TYPE_COLOR }, };
//            frameBufferDesc.RenderPass  = renderPass;
//
//            swapChainFramebuffers[i] = renderDevice->CreateFrameBuffer(&frameBufferDesc);
//        }
//    }
//
//    void createCommandPool() {
//        Graphics::CommandPoolDescriptor commandPoolDesc = {};
//        commandPoolDesc.Name = "CommandPool";
//        commandPoolDesc.Type = Graphics::CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;
//
//
//        commandPool = renderDevice->CreateCommandPool(&commandPoolDesc);
//    }
//
//    void createVertexBuffer() {
//        uint32_t bufferSize = sizeof(vertices[0]) * vertices.size();
//
//        Graphics::BufferDescriptor bufferDesc = {};
//        bufferDesc.Name         = "VertexStagingBuffer";
//        bufferDesc.Size         = bufferSize;
//        bufferDesc.MemoryType   = Graphics::ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
//        bufferDesc.Usage        = Graphics::BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
//        bufferDesc.Data         = vertices.data();
//        bufferDesc.BufferLayout = Graphics::BufferLayout({ { "POS",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
//                                                           { "COLOR",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });
//
//        Graphics::Buffer* stagingBuffer = renderDevice->CreateBuffer(&bufferDesc);
//       
//        bufferDesc = {};
//        bufferDesc.Name         = "VertexBuffer";
//        bufferDesc.Size         = bufferSize;
//        bufferDesc.MemoryType   = Graphics::ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
//        bufferDesc.Usage        = Graphics::BufferUsage::BUFFER_USAGE_VERTEX_BUFFER;
//        bufferDesc.Data         = nullptr;
//        bufferDesc.BufferLayout = Graphics::BufferLayout({ { "POS",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
//                                                           { "COLOR",  Graphics::ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });
//
//        vertexBuffer = renderDevice->CreateBuffer(&bufferDesc);
//
//        commandBuffers[0]->BeginRecording();
//        commandBuffers[0]->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);
//        commandBuffers[0]->EndRecording();
//
//        executeFence->Reset();
//        commandQueue->SubmitCommandBuffer(commandBuffers[0], executeFence);
//        executeFence->WaitForFence();
//
//        delete stagingBuffer;
//    }
//
//    void createIndexBuffer() {
//        uint32_t bufferSize = sizeof(indices[0]) * indices.size();
//
//        Graphics::BufferDescriptor bufferDesc = {};
//        bufferDesc.Name         = "IndexStagingBuffer";
//        bufferDesc.Size         = bufferSize;
//        bufferDesc.MemoryType   = Graphics::ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
//        bufferDesc.Usage        = Graphics::BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
//        bufferDesc.Data         = indices.data();
//        bufferDesc.BufferLayout = Graphics::BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, });
//
//        Graphics::Buffer* stagingBuffer = renderDevice->CreateBuffer(&bufferDesc);
//
//        bufferDesc = {};
//        bufferDesc.Name         = "IndexBuffer";
//        bufferDesc.Size         = bufferSize;
//        bufferDesc.MemoryType   = Graphics::ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
//        bufferDesc.Usage        = Graphics::BufferUsage::BUFFER_USAGE_INDEX_BUFFER;
//        bufferDesc.Data         = nullptr;
//        bufferDesc.BufferLayout = Graphics::BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, });
//
//        indexBuffer = renderDevice->CreateBuffer(&bufferDesc);
//
//        commandBuffers[0]->BeginRecording();
//        commandBuffers[0]->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);
//        commandBuffers[0]->EndRecording();
//
//        executeFence->Reset();
//        commandQueue->SubmitCommandBuffer(commandBuffers[0], executeFence);
//        executeFence->WaitForFence();
//
//        delete stagingBuffer;
//    }
//
//    void createCommandBuffers() {
//        commandBuffers.resize(swapChainFramebuffers.size());
//
//        // Create info
//        Graphics::CommandBufferDescriptor commandBufferDesc = {};
//        commandBufferDesc.Name        = "CommandBuffer";
//        commandBufferDesc.Type        = Graphics::CommandBufferType::COMMAND_BUFFER_TYPE_DIRECT;
//        commandBufferDesc.CommandPool = commandPool;
//
//        // Create CommandBuffers
//        for (int i = 0; i < commandBuffers.size(); i++)
//            commandBuffers[i] = renderDevice->CreateCommandBuffer(&commandBufferDesc);
//
//       // VkCommandBufferAllocateInfo allocInfo{};
//       // allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//       // allocInfo.commandPool = commandPool->GetVKCommandPool();
//       // allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//       // allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();
//       //
//       // if (vkAllocateCommandBuffers(renderDevice->GetDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
//       //     throw std::runtime_error("failed to allocate command buffers!");
//       // }
//
//        
//    }
//
//
//    void FillCommandBuffer()
//    {
//        for (size_t i = 0; i < commandBuffers.size(); i++) {
//            //  VkCommandBufferBeginInfo beginInfo{};
//            //  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//            //
//            //  if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
//            //      throw std::runtime_error("failed to begin recording command buffer!");
//            //  }
//
//            commandBuffers[i]->BeginRecording();
//
//            float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
//            commandBuffers[i]->BeginRenderPass(renderPass, swapChainFramebuffers[i], swapchain->GetWidth(), swapchain->GetHeight(), clearColor);
//
//            commandBuffers[i]->SetGraphicsPipeline(graphicsPipeline);
//
//            commandBuffers[i]->SetVertexBuffer(vertexBuffer, 0);
//            commandBuffers[i]->SetIndexBuffer(indexBuffer);
//
//            commandBuffers[i]->DrawIndexed(0, 0, indices.size());
//
//            commandBuffers[i]->EndRenderPass();
//
//            commandBuffers[i]->EndRecording();
//            //    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
//            //        throw std::runtime_error("failed to record command buffer!");
//            //    }
//        } 
//    }
//    void createSyncObjects() {
//
//            Graphics::FenceDescriptor fenceDesc = {};
//            fenceDesc.Name = "Fence";
//            fenceDesc.TimeOut = UINT64_MAX;
//
//            executeFence = renderDevice->CreateFence(&fenceDesc);
//            presentFence = renderDevice->CreateFence(&fenceDesc);
//    }
//
//    void drawFrame() {
//        presentFence->Reset();
//        uint32_t imageIndex = swapchain->AquireNewImage(commandQueue, presentFence);
//        presentFence->WaitForFence();
//
//        executeFence->Reset();
//        commandQueue->SubmitCommandBuffer(commandBuffers[imageIndex], executeFence);
//        executeFence->WaitForFence();
//
//        swapchain->Present(commandQueue);
//    }
//};
//
//int main() {
//    HelloTriangleApplication app;
//
//    app.run();
//
//
//    return EXIT_SUCCESS;
//}