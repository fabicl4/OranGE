#pragma once

#include "defines.h"

#include <core/Log.h>

namespace OranGE::gfx {

// Binding target 
enum class BufferUsage : u32 {
    Vertex  = 1 << 0, // VBO    -> GL_ARRAY_BUFFER
    Index   = 1 << 1, // EBO    -> GL_ELEMENT_ARRAY_BUFFER
    Uniform = 1 << 2, // UBO
    Storage = 1 << 3, // SSBO
    CopySrc = 1 << 4,
    CopyDst = 1 << 5
};

enum class MemoryType {
    GPU,
    CPU,
    CPU_TO_GPU
};

struct Buffer
{
    u32 id; // GPU Handle

    char* debugName = nullptr;
    BufferUsage usage;
    MemoryType memType;
    size_t size;
    size_t count; // number of elements (e.g. vertices or indices)

    unsigned char* data; // pointer to CPU-side data (if applicable)
};

struct VertexArray {
    u32 id;  // OpenGL VAO ID
};

struct BufferView
{
    Buffer* buffer;
    
    size_t offset;
    size_t size;
};

};