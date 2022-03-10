#pragma once
#include "./graphics/renderer/model/mesh.h"

#include "./graphics/api/interface/object/sync/fence.h"
#include "./graphics/api/interface/object/command/command_buffer.h"

namespace Graphics
{
	class Quad
	{
	public:
		static Mesh* Create(CommandBuffer* _commandBuffer, Fence* _fence)
		{
			Mesh* result = new Mesh();
            return result;
        //   uint32_t bufferSizeV = sizeof(vertices[0]) * vertices.size();
        //
        //   BufferDescriptor bufferDesc;
        //   bufferDesc.Name = "VertexStagingBuffer";
        //   bufferDesc.Size = bufferSizeV;
        //   bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
        //   bufferDesc.Usage = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
        //   bufferDesc.Data = vertices.data();
        //   bufferDesc.BufferLayout = BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
        //                                                      { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });
        //
        //   Buffer* stagingBufferV = m_RenderDevice->CreateBuffer(&bufferDesc);
        //
        //   bufferDesc = {};
        //   bufferDesc.Name = "VertexBuffer";
        //   bufferDesc.Size = bufferSizeV;
        //   bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
        //   bufferDesc.Usage = BufferUsage::BUFFER_USAGE_VERTEX_BUFFER;
        //   bufferDesc.Data = nullptr;
        //   bufferDesc.BufferLayout = BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT },
        //                                            { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, });
        //
        //   m_VertexBuffer = m_RenderDevice->CreateBuffer(&bufferDesc);
        //
        //   uint32_t bufferSizeI = sizeof(indices[0]) * indices.size();
        //
        //   bufferDesc = {};
        //   bufferDesc.Name = "IndexStagingBuffer";
        //   bufferDesc.Size = bufferSizeI;
        //   bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_MEMORY;
        //   bufferDesc.Usage = BufferUsage::BUFFER_USAGE_STAGING_BUFFER;
        //   bufferDesc.Data = indices.data();
        //   bufferDesc.BufferLayout = BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, });
        //
        //   Buffer* stagingBufferI = m_RenderDevice->CreateBuffer(&bufferDesc);
        //
        //   bufferDesc = {};
        //   bufferDesc.Name = "IndexBuffer";
        //   bufferDesc.Size = bufferSizeI;
        //   bufferDesc.MemoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_MEMORY;
        //   bufferDesc.Usage = BufferUsage::BUFFER_USAGE_INDEX_BUFFER;
        //   bufferDesc.Data = nullptr;
        //   bufferDesc.BufferLayout = BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, });
        //
        //   m_IndexBuffer = m_RenderDevice->CreateBuffer(&bufferDesc);
		}
	};
}