#include "Device.h"

#include <core/Log.h>

#include <glad/glad.h>

namespace OranGE::gfx {
Device::Device(bool enableValidation)
    : m_EnableValidation(enableValidation), m_Context(nullptr)
{
    LOG_TRACE("[Device]Created device with validation {}", enableValidation ? "enabled" : "disabled");
}


Device::~Device()
{
    // Clean up GL resources
    for (const Buffer& buffer : m_Buffers) {
        glDeleteBuffers(1, &buffer.id);
    }
    for (const Shader& shader : m_Shaders) {
        glDeleteProgram(shader.id);
    }
    for (const Texture& texture : m_Textures) {
        glDeleteTextures(1, &texture.id);
    }

    LOG_TRACE("[Device]Destroyed device and cleaned up resources");
}

void Device::enableDebugging()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            LOG_ERROR("OpenGL Debug Message (source: {}, type: {}, id: {}, severity: {}): {}", source, type, id, severity, message);
        },
        nullptr
    );
    
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
}

bool Device::Init(void* glLoadingFunc)
{
    // Initialize GL context and load function pointers using glad
    if (!gladLoadGLLoader((GLADloadproc)glLoadingFunc)) {
        LOG_ERROR("[Device]Failed to initialize OpenGL context");
        return false;
    }

    LOG_TRACE("[Device]Initialized OpenGL context successfully");

    if (m_EnableValidation) {
        enableDebugging();
    }

    return true;
}

void Device::SetViewport(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}


void Device::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear both color and depth buffers
}

void Device::BindBuffer(u32 bufferId)
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void Device::BindShader(u32 shaderId)
{
    glUseProgram(shaderId);
}

void Device::BindTexture(u32 textureId, u32 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Device::DrawIndexed(u32 baseVertex, u32 indexCount)
{
    glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, baseVertex);
}

void Device::Draw(u32 baseVertex, u32 vertexCount)
{
    glDrawArrays(GL_TRIANGLES, baseVertex, vertexCount);
}

int Device::CreateBuffer(const void* data, size_t size)
{
    u32 bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    int index = m_Buffers.size();

    Buffer buffer{};
    buffer.id = bufferId;
    m_Buffers.push_back(buffer);

    return index;
}

// utility function for checking shader compilation/linking errors.
int checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {} with info log: {}", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            LOG_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {} with info log: {}", type, infoLog);
        }
    }

    return success;
}

int Device::CreateShader(const char* vsSrc, const char* fsSrc)
{
    GLuint vsHandle, fsHandle;

    // Compile vertex shader
    // ---------------------
    vsHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsHandle, 1, &vsSrc, NULL);
    glCompileShader(vsHandle);

    if (!checkCompileErrors(vsHandle, "VERTEX"))
    {
        throw std::runtime_error("Vertex shader failed to compile");
    }

    // Compile fragment shader
    // ---------------------
    fsHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsHandle, 1, &fsSrc, NULL);
    glCompileShader(fsHandle);

    if (!checkCompileErrors(fsHandle, "FRAGMENT"))
    {
        throw std::runtime_error("Fragment shader failed to compile");
    }

    // Create Program
    // ---------------------
    GLuint program = glCreateProgram();
    glAttachShader(program, vsHandle);
    glAttachShader(program, fsHandle);
    glLinkProgram(program);

    if (!checkCompileErrors(program, "PROGRAM"))
    {
        throw std::runtime_error("Program failed to link");
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vsHandle);
    glDeleteShader(fsHandle);

    //output->...
    Shader shader{};
    shader.id = program;
    int index = m_Shaders.size();

    m_Shaders.push_back(shader);

    return index;
}

int Device::CreateTexture(const void* data, uint32_t width, uint32_t height)
{
    // TODO: Fix and expand

    if (!data) {
        LOG_ERROR("Failed to create texture: data pointer is null");
        return -1;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    Texture tex{};
    tex.id = texture;
    tex.width = width;
    tex.height = height;
    tex.wrap = TextureWrapMode::REPEAT;
    tex.filter = TextureFilterMode::LINEAR;
    tex.format = PixelFormat::RGBA8;
    tex.mipmaps = 0;

    int index = m_Textures.size();

    m_Textures.push_back(tex);

    // TODO: Check errors when creating a Texture

    return index;
}

};

