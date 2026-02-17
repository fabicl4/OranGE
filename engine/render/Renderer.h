#pragma once

#include "defines.h"

// Types
#include "resources/Shader.h"
#include "resources/Texture.h"
#include "resources/Mesh.h"

namespace OranGE::gfx {

class Device;
class Renderer;

struct Viewport
{
    uint32_t x, y;
    uint32_t width, height;
};

class Renderer
{
    struct FrameStats {
        float frameTime;    // time taken to render the current frame in milliseconds
        int drawCalls;      // number of draw calls issued this frame
        int triangleCount;  // total number of triangles rendered this frame
    } m_Stats;

public:
    Renderer(Device* device, const Viewport& viewport);
    ~Renderer() = default;

    void BeginFrame();
    void EndFrame();

    void Submit(const Mesh& mesh, const Shader& shader);

    // event handlers
    void OnWindowResize(uint32_t width, uint32_t height);
    void OnWindowResize(int width, int height);
    void OnWindowFocus();
    void OnWindowLostFocus();
    void OnWindowMaximize();


private:
    Device* m_Device;
    Viewport m_Viewport;
};


};