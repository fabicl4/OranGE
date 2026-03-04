#include "Mesh.h"

#include <render/Device.h>

#include <render/Buffer.h>

namespace OranGE {

u32 AttributeType2GLType(VertexLayout::AttributeType attrType) {
    switch(attrType) {
        case VertexLayout::AttributeType::Float:
        case VertexLayout::AttributeType::Float2:
        case VertexLayout::AttributeType::Float3:
        case VertexLayout::AttributeType::Float4:
            return GL_FLOAT;
        case VertexLayout::AttributeType::Int:
        case VertexLayout::AttributeType::Int2:
        case VertexLayout::VertexLayout::AttributeType::Int3:
        case VertexLayout::AttributeType::Int4: 
            return GL_INT;
        case VertexLayout::AttributeType::Mat3: 
        case VertexLayout::AttributeType::Mat4: 
            return GL_FLOAT;
        default:
            LOG_ERROR("[Mesh]Unknown or unsupported attribute type!");
            return 0;
    }

    return 0;
}

Handle<Mesh> MeshManager::CreateMesh(const MeshData& meshData)
{
    LOG_TRACE("[MeshManager::CreateMesh] Creating mesh with {} vertices and {} indices", 
        meshData.vertex_count, meshData.index_count);

    // Create vertex buffer array and buffer
    u32 vertexArray = m_Device->CreateVertexArray().id;
    u32 vertexBuffer = m_Device->CreateVertexBuffer(
        meshData.vertices, 
        meshData.vertex_count * sizeof(float) * 3 /* assuming 3 components per vertex */
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
            AttributeType2GLType(attr.type), // type (e.g. GL_FLOAT)
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