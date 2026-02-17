#pragma once

#include "defines.h"

#include "Texture.h"
#include "Shader.h"

// Forward declaration of Device class to avoid circular dependency
class Device;

namespace OranGE {

template<typename T>
class Handle 
{
public:
    Handle() : id(0), generation(0) {}
    explicit Handle(u32 id, u32 generation) : id(id), generation(generation) {}

    u32 GetId() const { return id; }
    u32 GetGeneration() const { return generation; }
    bool IsValid() const { return id != 0; }

    bool operator==(const Handle& other) const {
        return id == other.id && generation == other.generation;
    }

private:
    u32 id;
    u32 generation; // for future use in handle validation and recycling
};

// TODO: multi-threading support (e.g. thread-safe handle creation/destruction, resource loading, etc.)
// Generation overflow!
template<typename T>
class HandleManager
{
public:

    Handle<T> CreateHandle(const T& resource) {
        u32 id;

        if (!m_FreeSlots.empty()) {
            id = m_FreeSlots.back();
            m_FreeSlots.pop_back();

            m_Resource[id] = resource;
            m_Generations[id]++;

        } else {
            id = static_cast<u32>(m_Resource.size());
            m_Resource.push_back(resource);
            m_Generations.push_back(1);
        }

        return Handle<T>(id, m_Generations[id]);
    }

    void DestroyHandle(const Handle<T>& handle) {
        u32 id = handle.GetId();
        if (id < m_Resource.size()) {
            // Mark the slot as free
            m_FreeSlots.push_back(id);
            // Optionally, we could also clear the resource data here
            // m_Resource[id] = T(); // reset to default state
        }
    }

    bool IsHandleValid(const Handle<T>& handle) const {
        u32 id = handle.GetId();
        if (id >= m_Resource.size()) return false;
        const auto& slot = m_Resource[id];

        return m_Generations[id] == handle.GetGeneration() && m_Generations[id] != 0;
    }

    T& GetResource(const Handle<T>& handle) 
    {
        if (IsHandleValid(handle)) {
            u32 id = handle.GetId();
            return m_Resource[id];
        }

        throw std::out_of_range("Invalid handle ID");
    }

    const T* GetDataPtr() const {
        return m_Resource.data();
    }

private:

    std::vector<T> m_Resource;
    std::vector<int> m_Generations;
    std::vector<u32> m_FreeSlots;
};

typedef Handle<Shader> ShaderHandle;
typedef Handle<Texture> TextureHandle;
typedef Handle<Buffer> BufferHandle;

//typedef HandleManager<Buffer> BufferManager;

class TextureManager : public HandleManager<Texture> 
{
public:
    TextureManager(Device* device) : m_Device(device) {}
    // Additional texture-specific management functions can be added here
    // e.g. loading textures from files, generating mipmaps, etc.

    Handle<Texture> LoadTextureFromFile(const char* filePath);

private:
    Device* m_Device; // for texture creation and resource management
};

class ShaderManager : public HandleManager<Shader> 
{
public:
    // Additional shader-specific management functions can be added here
    // e.g. compiling shaders from source, handling shader variants, etc.

    ShaderManager(Device* device) : m_Device(device) {}

    Handle<Shader> CreateShaderFromSource(const char* vertexSrc, const char* fragmentSrc);
    Handle<Shader> CreateShaderFromFiles(const char* vertexPath, const char* fragmentPath);

private:
    Device* m_Device; // for shader compilation and resource management
};
    
}