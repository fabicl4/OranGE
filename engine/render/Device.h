#pragma once

// file: render/Device.h

#include "defines.h"

#include "Buffer.h"

#include "Context.h"

#include "Resource.h"

typedef OranGE::Handle<OranGE::gfx::Buffer> BufferHandle;

namespace OranGE::gfx {


class Device
{
    using GLProcLoader = void* (*)(const char*);
public:
    Device(bool enableValidation);
    ~Device();

    bool Init(GLProcLoader glLoadingFunc);

    void SetContext(Context context) { m_Context = context; }

    void SetViewport(uint32_t width, uint32_t height);
    void Clear(float r, float g, float b, float a);

    // ===== BUFFER CREATION =====
    Buffer CreateVertexBuffer(const void* data, size_t size);
    //Buffer CreateIndexBuffer(const void* data, size_t size, IndexType type);
    //void DestroyBuffer(Buffer& buffer);
    
    // ===== VERTEX ARRAY CREATION =====
    VertexArray CreateVertexArray();
    
    // Vincula un buffer a un atributo del VAO
    void SetVertexAttribute(
        VertexArray& vao,
        u32 attribIndex,
        const Buffer& buffer,
        u32 size,           // 1, 2, 3, 4
        u32 type,           // GL_FLOAT, GL_UNSIGNED_INT, etc.
        bool normalized,
        u32 stride,
        u32 offset
    );
    
    //void SetIndexBuffer(VertexArray& vao, const Buffer& buffer);

    // ===== RENDERING COMMANDS =====
    void BindBuffer(u32 bufferId);
    void UnBindBuffer(u32 target);
    void BindVertexArray(u32 vaoId);
    void BindShader(u32 shaderId);
    void BindTexture(u32 textureId, u32 slot = 0);

    void DrawIndexed(u32 baseVertex, u32 indexCount);
    void Draw(u32 baseVertex, u32 vertexCount);

    // factory method to create a GL resources
    // return the index of the created resource in the corresponding vector (e.g. m_Buffers, m_Shaders, m_Textures)
    //Mesh CreateMesh(/*MeshData*/);
    
    u32 CreateShader(const char* vertexSrc, const char* fragmentSrc);
    u32 CreateTexture(const void* data, uint32_t width, uint32_t height);

private:
    void enableDebugging();

private:
    bool m_EnableValidation;

    glm::vec4 m_ClearColor{0.1f, 0.1f, 0.1f, 1.0f};

    Context m_Context;
};

};
