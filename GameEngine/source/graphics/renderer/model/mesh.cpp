#include "core/stdafx.h"
#include "mesh.h"

namespace Graphics
{
    Mesh::~Mesh()
    {
        delete m_VertexBuffer;
        delete m_IndexBuffer;
    }

    void Mesh::CreateVertexBuffer(CommandBuffer* _commandBuffer, Fence* _fence, void* _data, const uint32_t _size, BufferLayout _layout)
	{
        BufferDescriptor bufferDesc;
        bufferDesc.Name         = "Generated-VertexStagingBuffer";
        bufferDesc.Size         = _size;
        bufferDesc.MemoryType   = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
        bufferDesc.Usage        = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
        bufferDesc.Data         = _data;
        bufferDesc.BufferLayout = _layout;
        
        Buffer* stagingBuffer = RenderDevice::GetInstance()->CreateBuffer(&bufferDesc);
        
        bufferDesc = {};
        bufferDesc.Name         = "Generated-VertexBuffer";
        bufferDesc.Size         = _size;
        bufferDesc.MemoryType   = ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
        bufferDesc.Usage        = BufferUsage::BUFFER_USAGE_VERTEX_BUFFER;
        bufferDesc.Data         = nullptr;
        bufferDesc.BufferLayout = _layout;
        
        m_VertexBuffer = RenderDevice::GetInstance()->CreateBuffer(&bufferDesc);

        _commandBuffer->BeginRecording();
        _commandBuffer->CopyBuffer(stagingBuffer, m_VertexBuffer, _size);
        _commandBuffer->EndRecording();

        _fence->Reset();
        RendererBackend::SubmitCommandBuffer(_commandBuffer, _fence);
        _fence->WaitForFence();

        delete stagingBuffer;
	}

    void Mesh::CreateIndexBuffer(CommandBuffer* _commandBuffer, Fence* _fence, void* _data, const uint32_t _size, BufferLayout _layout)
    {
        BufferDescriptor bufferDesc;
        bufferDesc.Name         = "Generated-IndexStagingBuffer";
        bufferDesc.Size         = _size;
        bufferDesc.MemoryType   = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
        bufferDesc.Usage        = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
        bufferDesc.Data         = _data;
        bufferDesc.BufferLayout = _layout;
     
        Buffer* stagingBuffer = RenderDevice::GetInstance()->CreateBuffer(&bufferDesc);
     
        bufferDesc = {};
        bufferDesc.Name         = "Generated-IndexBuffer";
        bufferDesc.Size         = _size;
        bufferDesc.MemoryType   = ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
        bufferDesc.Usage        = BufferUsage::BUFFER_USAGE_INDEX_BUFFER;
        bufferDesc.Data         = nullptr;
        bufferDesc.BufferLayout = _layout;
     
        m_IndexBuffer = RenderDevice::GetInstance()->CreateBuffer(&bufferDesc);

        _commandBuffer->BeginRecording();
        _commandBuffer->CopyBuffer(stagingBuffer, m_IndexBuffer, _size);
        _commandBuffer->EndRecording();

        _fence->Reset();
        RendererBackend::SubmitCommandBuffer(_commandBuffer, _fence);
        _fence->WaitForFence();

        delete stagingBuffer;
    }
}
