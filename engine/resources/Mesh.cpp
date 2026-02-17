#include "Mesh.h"

#include <render/Device.h>

#include <render/Buffer.h>

namespace OranGE {

Handle<Mesh> MeshManager::CreateMesh(const MeshData& meshData)
{
    LOG_TRACE("[MeshManager::CreateMesh] Creating mesh with {} vertices and {} indices", 
        meshData.vertex_count, meshData.index_count);

    // Create vertex buffer array and buffer
    u32 vertexArray = m_Device->CreateVertexArray().id;
    u32 vertexBuffer = m_Device->CreateVertexBuffer(
        meshData.vertices, 
        meshData.vertex_count * sizeof(float)
    ).id;

    // Set up vertex attributes based on the provided layout

    const auto& attributes = meshData.layout.GetAttributes();
    for (u32 i = 0; i < attributes.size(); ++i) {
        const auto& attr = attributes[i];
        m_Device->SetVertexAttribute(
            gfx::VertexArray({vertexArray}),
            i, // attribute index
            gfx::Buffer({vertexBuffer, 0x8892/*GL_ARRAY_BUFFER*/}), // buffer
            attr.count, // size (number of components)
            attr.type, // type (e.g. GL_FLOAT)
            attr.normalized, // normalized
            meshData.layout.GetStride(), // stride
            attr.offset // offset
        );
    }

    m_Device->BindBuffer(0); // unbind the vertex buffer
    m_Device->BindVertexArray(0); // unbind the vertex array

    Mesh mesh(vertexArray, vertexBuffer, meshData.vertex_count, meshData.layout);

    return CreateHandle(mesh);
}

void MeshManager::DestroyMesh(const Handle<Mesh>& handle) {
    if (IsHandleValid(handle)) {
        // TODO: Delete the GPU resources here using m_Device
        // e.g. m_Device->DeleteBuffer(mesh.vertexBuffer);

        HandleManager<Mesh>::DestroyHandle(handle);
    }
}

};