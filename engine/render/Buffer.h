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

struct BufferDesc {
    u64 size;
    BufferUsage usage;
    MemoryType memory;
};

struct Buffer
{
    u32 id;
    char* debugName = nullptr;
    BufferDesc desc;
    MemoryType memType;
    size_t size;
    size_t count; // number of elements (e.g. vertices or indices)

    unsigned char* data; // pointer to CPU-side data (if applicable)
};

struct BufferView
{
    Buffer* buffer;
    size_t offset;
    size_t size;
};

struct BufferElement
{
    char* debugName = nullptr;
    u32 type; // e.g. GL_FLOAT, GL_UNSIGNED_INT, etc.
    u32 count; // number of components (e.g. 3 for vec3)
    bool normalized; // whether integer types should be normalized to [0,1] or [-1,1]
    u32 size; // size in bytes of the element (count * sizeof(type))
    u32 offset; // byte offset from the start of the buffer

    BufferElement(char* name, u32 type, u32 count, bool normalized)
        : debugName(name), type(type), count(count), normalized(normalized)
    {
        // compute size based on type and count
        switch (type) {
            case 0x1406: // GL_FLOAT
                size = count * sizeof(float);
                break;
            case 0x1405: // GL_UNSIGNED_INT
                size = count * sizeof(uint32_t);
                break;
            // add more types as needed
            default:
                LOG_ERROR("Unsupported buffer element type: {}", type);
                size = 0; // unknown type
        }
    }
};

class BufferLayout
{
public:
    BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
        // compute offsets and total stride
        u32 offset = 0;
        for (auto& element : m_Elements) {
            element.offset = offset;
            offset += element.size;
        }
        m_Stride = offset;
    }

    const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    u32 GetStride() const { return m_Stride; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
    std::vector<BufferElement> m_Elements;
    u32 m_Stride = 0;
};



};