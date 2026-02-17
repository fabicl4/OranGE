#pragma once

#include "defines.h"

#include <core/Log.h>

namespace OranGE::gfx {

enum class BufferUsage : u32 {
    Vertex  = 1 << 0,
    Index   = 1 << 1,
    Uniform = 1 << 2,
    Storage = 1 << 3,
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
    u32 id;
    u32 target; // GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, etc.

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