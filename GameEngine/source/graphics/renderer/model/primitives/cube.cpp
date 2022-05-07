#include "core/stdafx.h"

namespace Graphics
{
    struct Vert {
        float pos[3];
        float tex[2];
    };


    std::vector<Vert> vertices = {
        // Front
        {{-0.5f, -0.5f, 0.5f }, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.5f }, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0.5f }, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, 0.5f }, {0.0f, 1.0f}},

        // Right
        {{0.5f, -0.5f,  0.5f }, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f }, {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f }, {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f }, {0.0f, 1.0f}},
        // Back
        {{ 0.5f, -0.5f, -0.5f }, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f }, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f }, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f }, {0.0f, 1.0f}},
        // Left
        {{-0.5f, -0.5f, -0.5f }, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f }, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f }, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f }, {0.0f, 1.0f}},
        // Top
        {{-0.5f, 0.5f,  0.5f }, {0.0f, 0.0f}},
        {{ 0.5f, 0.5f,  0.5f }, {1.0f, 0.0f}},
        {{ 0.5f, 0.5f, -0.5f }, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f }, {0.0f, 1.0f}},
        // Bottom
        {{-0.5f, -0.5f, -0.5f }, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f }, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f }, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f }, {0.0f, 1.0f}},
    };

    std::vector<uint16_t> indices = {
           // Front
           2, 1, 0,
           0, 3, 2,
           // Right
           6, 5, 4,
           4, 7, 6,
           // Back
           10, 9, 8,
           8, 11, 10,
           // Left
           14, 13, 12,
           12, 15, 14,
           // Top
           18, 17, 16,
           16, 19, 18,
           // Bottom
           22, 21, 20,
           20, 23, 22,
    };

    Cube::Cube(CommandBuffer* _commandBuffer, Fence* _fence)
    {
        CreateVertexBuffer(_commandBuffer, _fence, vertices.data(), sizeof(vertices[0]) * vertices.size(), BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT },
             { "TEX",  ResourceFormat::RESOURCE_FORMAT_R32G32_SFLOAT } }));
        CreateIndexBuffer(_commandBuffer, _fence, indices.data(), sizeof(indices[0]) * indices.size(), BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, }));

        SubMesh cube;
        cube.VertexOffset = 0;
        cube.VertexCount = vertices.size();
        cube.IndexOffset = 0;
        cube.IndexCount = indices.size();

        AddSubmesh(cube);
    }
}
