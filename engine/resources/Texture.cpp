#include "Texture.h"

#include <stb_image.h>

#include <render/Device.h>
#include <core/Log.h>

namespace OranGE {

Handle<Texture> TextureManager::LoadTextureFromFile(const char* filePath)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

    if (!data) {
        LOG_ERROR("[TextureManager]Failed to load texture from file: {}", filePath);
        return Handle<Texture>();
    }

    u32 id = m_Device->CreateTexture(data, width, height);

    Texture texture;
    texture.id = id;
    texture.width = width;
    texture.height = height;
    texture.format = (channels == 4) ? PixelFormat::RGBA8 : PixelFormat::RGB8;
    texture.type = TextureType::TEXTURE_2D;
    texture.wrap = TextureWrapMode::REPEAT;
    texture.filter = TextureFilterMode::LINEAR;
    texture.mipmaps = 1; // For simplicity, we won't generate mipmaps here

    stbi_image_free(data);

    return CreateHandle(texture);
}

};