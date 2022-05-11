#include "core/stdafx.h"

namespace Graphics
{
    struct Vert {
        float pos[2];
        float tex[2];
    };

    std::vector<Vert> vertices = {
        {{-0.5f, -0.5f }, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f }, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f }, {1.0f, 1.0f}},
        {{-0.5f,  0.5f }, {0.0f, 1.0f}}
    };

    std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

	Quad::Quad(CommandBuffer* _commandBuffer, Fence* _fence)
	{
		CreateVertexBuffer(_commandBuffer, _fence, vertices.data(), sizeof(vertices[0]) * vertices.size(), BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT },
             { "TEX",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT } }));
		CreateIndexBuffer(_commandBuffer, _fence, indices.data(), sizeof(indices[0]) * indices.size(), BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, }));

        SubMesh quad;
        quad.VertexOffset = 0;
        quad.VertexCount  = vertices.size();
        quad.IndexOffset  = 0;
        quad.IndexCount   = indices.size();

        AddSubmesh(quad);
	}
}
