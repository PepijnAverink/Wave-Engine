#include "core/stdafx.h"


namespace Graphics
{
    struct Vert {
        float pos[3];
        float color[3];
    };


    std::vector<Vert> vertices = {
        //front
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f }, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f  }, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f }, {1.0f, 1.0f, 1.0f}},
        ////back
        { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f }, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f  }, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f }, {1.0f, 1.0f, 1.0f}}
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

    Cube::Cube(CommandBuffer* _commandBuffer, Fence* _fence)
    {
        CreateVertexBuffer(_commandBuffer, _fence, vertices.data(), sizeof(vertices[0]) * vertices.size(), BufferLayout({ { "POS",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT },
             { "COLOR",  ResourceFormat::RESOURCE_FORMAT_R32G32B32_SFLOAT }, }));
        CreateIndexBuffer(_commandBuffer, _fence, indices.data(), sizeof(indices[0]) * indices.size(), BufferLayout({ { "index",  Graphics::ResourceFormat::RESOURCE_FORMAT_R16_UINT }, }));

        SubMesh cube;
        cube.VertexOffset = 0;
        cube.VertexCount = vertices.size();
        cube.IndexOffset = 0;
        cube.IndexCount = indices.size();

        m_SubMeshes.push_back(cube);
    }
}
