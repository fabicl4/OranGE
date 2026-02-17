#pragma once

// file: resources/Mesh.

#include "defines.h"

#include "Resource.h"

#include <core/Log.h>

namespace OranGE {

class VertexLayout {
public:

    enum class AttributeType {
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        // etc.
    };
    
    struct Attribute {
        std::string name;
        u32 type; // e.g. GL_FLOAT, GL_UNSIGNED_INT, etc.
        u32 count; // number of components (e.g. 3 for vec3)
        bool normalized; // whether integer types should be normalized to [0,1] or [-1,1]
        u32 size; // size in bytes of the element (count * sizeof(type))
        u32 offset; // byte offset from the start of the vertex
    };

    VertexLayout(const std::vector<Attribute>& attributes)
        : m_Attributes(attributes)
    {
        // Calculate offsets and total stride
        u32 offset = 0;
        for (auto& attr : m_Attributes) {
            attr.offset = offset;
            offset += attr.size;
        }
        m_Stride = offset;
    }

    const std::vector<Attribute>& GetAttributes() const { return m_Attributes; }
    u32 GetStride() const { return m_Stride; }

private:
    std::vector<Attribute> m_Attributes;
    u32 m_Stride;

    u32 GetSizeOfType(AttributeType type) {
        switch(type) {
            case AttributeType::Float: return sizeof(float);
            case AttributeType::Float2: return sizeof(float) * 2;
            case AttributeType::Float3: return sizeof(float) * 3;
            case AttributeType::Float4: return sizeof(float) * 4;
            case AttributeType::Int: return sizeof(int);
            case AttributeType::Int2: return sizeof(int) * 2;
            case AttributeType::Int3: return sizeof(int) * 3;
            case AttributeType::Int4: return sizeof(int) * 4;
            case AttributeType::Mat3: return sizeof(float) * 3 * 3;
            case AttributeType::Mat4: return sizeof(float) * 4 * 4;
            default: 
                LOG_ERROR("Unknown attribute type!");
                return 0;
        }
    }

};

struct MeshData
{
    float* vertices;
    u32 vertex_count;
    
    VertexLayout layout;

    u32* indices = nullptr; // optional index data
    u32 index_count = 0;
    
};

struct Mesh {
    u32 vertexArray;
    u32 vertexBuffer;
    //u32 indexBuffer;

    VertexLayout layout;

    u32 vertexCount;
    //u32 indexCount;

    Mesh(u32 vertexArray, u32 vertexBuffer, u32 vertexCount, const VertexLayout& layout)
        : vertexArray(vertexArray), vertexBuffer(vertexBuffer), vertexCount(vertexCount), layout(layout) {}
};

typedef Handle<Mesh> MeshHandle;

class MeshManager : public HandleManager<Mesh> 
{
public:
    // Additional mesh-specific management functions can be added here
    // e.g. loading meshes from files, generating procedural meshes, etc.

    MeshManager(gfx::Device* device) : m_Device(device) {}

    //Handle<Mesh> LoadMeshFromFile(const char* filePath);
    Handle<Mesh> CreateMesh(const MeshData& meshData);

    void DestroyMesh(const Handle<Mesh>& handle);

private:
    gfx::Device* m_Device; // for mesh creation and resource management

};

/*
class MeshFactory
{
public:
    static MeshData CreateCube(float size = 1.0f);
    static MeshData CreateSphere(float radius = 1.0f, unsigned int segments = 16, unsigned int rings = 16);
    static MeshData CreatePlane(float width = 1.0f, float height = 1.0f);
};*/


}