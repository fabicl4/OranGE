#include "Device.h"

#include <core/Log.h>

#include <glad/glad.h>

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            //case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            //case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        LOG_ERROR("OpenGL Error: {} | {} ({})", error, file, line);
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 


namespace OranGE::gfx {

Device::Device(bool enableValidation)
    : m_EnableValidation(enableValidation), m_Context({})
{
    LOG_TRACE("[Device]Created device with validation {}", enableValidation ? "enabled" : "disabled");
}

Device::~Device() {}

void Device::enableDebugging()
{
    /*
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            LOG_ERROR("OpenGL Debug Message (source: {}, type: {}, id: {}, severity: {}): {}", source, type, id, severity, message);
        },
        nullptr
    );
    
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
    */
}

bool Device::Init(GLProcLoader glLoadingFunc)
{
    // Initialize GL context and load function pointers using glad
    if (!gladLoadGLLoader((GLADloadproc)glLoadingFunc)) {
        LOG_ERROR("[Device]Failed to initialize OpenGL context");

        return false;
    }

    glCheckError();

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
    glCheckError();
}

void Device::BindShader(u32 shaderId)
{
    glUseProgram(shaderId);
    glCheckError();
}

void Device::BindTexture(u32 textureId, u32 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glCheckError();
}

void Device::UnBindBuffer(u32 target)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind any buffer from the target
    glCheckError();
}

void Device::BindVertexArray(u32 vaoId)
{
    glBindVertexArray(vaoId);
    glCheckError();
}

void Device::DrawIndexed(u32 baseVertex, u32 indexCount)
{
    glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, baseVertex);
}

void Device::Draw(u32 baseVertex, u32 vertexCount)
{
    glDrawArrays(GL_TRIANGLES, baseVertex, vertexCount);
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

u32 Device::CreateShader(const char* vsSrc, const char* fsSrc)
{
    GLuint vsHandle, fsHandle;

    // Compile vertex shader
    // ---------------------
    vsHandle = glCreateShader(GL_VERTEX_SHADER);
    glCheckError();
    glShaderSource(vsHandle, 1, &vsSrc, NULL);
    glCheckError();
    glCompileShader(vsHandle);
    glCheckError();

    if (!checkCompileErrors(vsHandle, "VERTEX"))
    {
        throw std::runtime_error("Vertex shader failed to compile");
    }

    // Compile fragment shader
    // ---------------------
    fsHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glCheckError();
    glShaderSource(fsHandle, 1, &fsSrc, NULL);
    glCheckError();
    glCompileShader(fsHandle);
    glCheckError();

    if (!checkCompileErrors(fsHandle, "FRAGMENT"))
    {
        throw std::runtime_error("Fragment shader failed to compile");
    }

    // Create Program
    // ---------------------
    GLuint program = glCreateProgram();
    glCheckError();
    glAttachShader(program, vsHandle);
    glCheckError();
    glAttachShader(program, fsHandle);
    glCheckError();
    glLinkProgram(program);
    glCheckError();

    if (!checkCompileErrors(program, "PROGRAM"))
    {
        throw std::runtime_error("Program failed to link");
    }

    LOG_TRACE("[Device::CreateShader] Created shader program with ID {}", program);

    glCheckError();

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vsHandle);
    glCheckError();
    glDeleteShader(fsHandle);
    glCheckError();

    return program;
}

u32 Device::CreateTexture(const void* data, uint32_t width, uint32_t height)
{
    // TODO: Fix and expand this method to support different texture formats, mipmaps, etc.

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    // TODO: Check errors when creating a Texture and return an invalid handle if creation failed

    return texture;
}

Buffer Device::CreateVertexBuffer(const void* data, size_t size)
{
    Buffer buffer;
    buffer.size = size;
    // usage
    buffer.count = size / sizeof(float); // assuming float data

    glGenBuffers(1, &buffer.id);
    glCheckError();
    glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
    glCheckError();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glCheckError();

    return buffer;
}

VertexArray Device::CreateVertexArray()
{
    VertexArray vao;
    glGenVertexArrays(1, &vao.id);
    glCheckError();
    return vao;
}

void Device::SetVertexAttribute(
    VertexArray& vao,
    u32 attribIndex,
    const Buffer& buffer,
    u32 size,           // 1, 2, 3, 4
    u32 type,           // GL_FLOAT, GL_UNSIGNED_INT, etc.
    bool normalized,
    u32 stride,
    u32 offset
    )
{
    glBindVertexArray(vao.id);
    glCheckError();
    glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
    glCheckError();

    glEnableVertexAttribArray(attribIndex);
    glCheckError();
    glVertexAttribPointer(
        attribIndex, 
        size, 
        type, 
        normalized ? GL_TRUE : GL_FALSE, 
        stride,
        (const void*)offset
    );
    glCheckError();

}


};

