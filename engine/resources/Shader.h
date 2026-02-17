#pragma once

#include "defines.h"

#include "Resource.h"

namespace OranGE {

struct Shader
{
    u32 id;
    u32 type; // e.g. GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.
    char* debugName = nullptr; // optional name for debugging purposes
};

typedef Handle<Shader> ShaderHandle;

class ShaderManager : public HandleManager<Shader> 
{
public:
    // Additional shader-specific management functions can be added here
    // e.g. compiling shaders from source, handling shader variants, etc.

    ShaderManager(gfx::Device* device) : m_Device(device) {}

    Handle<Shader> CreateShaderFromSource(const char* vertexSrc, const char* fragmentSrc);
    Handle<Shader> CreateShaderFromFiles(const char* vertexPath, const char* fragmentPath);

private:
    gfx::Device* m_Device; // for shader compilation and resource management
};

};