#pragma once

#include "defines.h"

#include "Buffer.h"

#include "Context.h"

#include "Resource.h"

namespace OranGE::gfx {


class Device
{

public:
    Device(bool enableValidation);
    ~Device();

    bool Init(void* glLoadingFunc);

    void SetContext(Context context) { m_Context = context; }

    void SetViewport(uint32_t width, uint32_t height);
    void Clear(float r, float g, float b, float a);

    void BindBuffer(u32 bufferId);
    void BindShader(u32 shaderId);
    void BindTexture(u32 textureId, u32 slot = 0);

    void DrawIndexed(u32 baseVertex, u32 indexCount);
    void Draw(u32 baseVertex, u32 vertexCount);

    // factory method to create a GL resources
    // return the index of the created resource in the corresponding vector (e.g. m_Buffers, m_Shaders, m_Textures)
    BufferHandle CreateBuffer(const void* data, size_t size);
    BufferHandle CreateVertexBuffer(const void* data, size_t size);
    BufferHandle CreateIndexBuffer(const void* data, size_t size);
    BufferHandle CreateVertexArray();
    
    ShaderHandle CreateShader(const char* vertexSrc, const char* fragmentSrc);
    TextureHandle CreateTexture(const void* data, uint32_t width, uint32_t height);

private:
    void enableDebugging();

private:
    bool m_EnableValidation;

    glm::vec4 m_ClearColor{0.1f, 0.1f, 0.1f, 1.0f};

    Context m_Context;
};

};
