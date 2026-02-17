#include "Shader.h"

#include <render/Device.h>

namespace OranGE {

Handle<Shader> ShaderManager::CreateShaderFromSource(const char* vertexSrc, const char* fragmentSrc)
{
    u32 gpu_id = m_Device->CreateShader(vertexSrc, fragmentSrc); // TODO: implement shader creation from source

    LOG_TRACE("[ShaderManager::CreateShaderFromSource] Created shader with GPU ID {}", gpu_id);

    Shader shader;
    shader.id = gpu_id;

    return CreateHandle(shader); 
}

Handle<Shader> ShaderManager::CreateShaderFromFiles(const char* vertexPath, const char* fragmentPath)
{
    return ShaderHandle(); // TODO: implement shader loading from files
}

}