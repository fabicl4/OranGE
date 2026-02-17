#include "Resource.h"

#include <stb/stb_image.h>

namespace OranGE {

Handle<Texture> TextureManager::LoadTextureFromFile(const char* filePath)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

    if (!data) {
        LOG_ERROR("[TextureManager]Failed to load texture from file: {}", filePath);
        return Handle<Texture>();
    }

    Texture texture = Texture(width, height, channels, data);

    stbi_image_free(data);

    return CreateHandle(texture);
}

}
