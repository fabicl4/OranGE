#pragma once

#include <defines.h>

#include "Resource.h"

namespace OranGE {

enum class TextureFormat {
    RGBA8,
    BGRA8,
    RGBA16F,
    Depth24Stencil8
};

enum class TextureUsage : u32 {
    Sampled  = 1 << 0,
    Storage  = 1 << 1,
    Render   = 1 << 2,
    CopySrc  = 1 << 3,
    CopyDst  = 1 << 4
};

enum class TextureType : u32
{
    TEXTURE_1D,
    TEXTURE_2D,
    TEXTURE_3D
};

enum TextureFilterMode : u32
{
    LINEAR,
    NEAREST
};

enum TextureWrapMode : u32
{
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

enum class PixelFormat : u32
{
    None = 0,
    R8,
    RGB8,
    RGBA8,
    RGBA32F
};

struct Texture 
{
    u32 id;

    u32 width, height;
    TextureType type;

    PixelFormat format;

    TextureWrapMode wrap;
    TextureFilterMode filter;

    u32 mipmaps;
};

struct TextureParams
{
    TextureType type;
    PixelFormat format;
    TextureWrapMode wrap;
    TextureFilterMode filter;
    u32 mipmaps;
}; 

struct TextureData
{
    const void* data;
    u32 width, height, numChannels;

    TextureData(u32 width, u32 height, u32 numChannels, const void* data)
        : width(width), height(height), numChannels(numChannels), data(data) {}
};

struct TextureView
{
    Texture* texture;
    
    TextureType type;
    PixelFormat format;
    u32 width, height;
};

typedef Handle<Texture> TextureHandle;

class TextureManager : public HandleManager<Texture> 
{
public:
    TextureManager(gfx::Device* device) : m_Device(device) {}
    // Additional texture-specific management functions can be added here
    // e.g. loading textures from files, generating mipmaps, etc.

    Handle<Texture> LoadTextureFromFile(const char* filePath);

private:
    gfx::Device* m_Device; // for texture creation and resource management
};


};