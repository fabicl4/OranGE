#pragma once

#include <defines.h>

#include <platform/Platform.h>
#include <platform/Event.h>

#include "../utils/Clock.h" // time measurement helper

#include <render/Renderer.h>

#include <resources/Resource.h>

namespace OranGE {

// Forward declaration of Device class to avoid being included in main.cpp
class Device;

struct ApplicationConfig
{
    std::string wrkDir;

    std::string title;
    uint32_t width;
    uint32_t height;
};

class Application {
public:
    //Application() {};
    Application(const ApplicationConfig& config);
    
    virtual ~Application() = default;

    bool Run();

protected:

    virtual bool OnCreate() { return true; };
    virtual bool OnDestroy() { return true; };
    // ts: time step / delta time in seconds since last update
    virtual bool OnUpdate(f64 ts) { return true; };
    virtual bool OnRender() { return true; };
    void OnEvent(Event& e);

    // helpers for derived classes
    f64 GetRunTime() const { return m_Clock.GetElapsed(); }
    
private:
    Clock m_Clock;          // high resolution timer used by the main loop
    f64   m_prevFrameTime = 0.0; // last frame's elapsed time

private:
    // Initialize systems
    bool Init();
    bool Shutdown();
    
    // timing helpers (used by Run)
    void ResetTimer() { m_Clock.Start(); m_prevFrameTime = 0.0; }
    inline f64 CalculateDelta()
    {
        m_Clock.Update();
        const f64 elapsed = m_Clock.GetElapsed();
        f64 dt = elapsed - m_prevFrameTime;
        m_prevFrameTime = elapsed;
        return dt;
    }

private:
    // event handling
    bool OnWindowResize(WindowResizeEvent& e);

protected:
    ApplicationConfig m_Config;

    Platform m_Platform;    // OS surface, events and window management
    Window* m_CurrWindow = nullptr;

    Window* m_Window;       
    gfx::Renderer* m_Renderer;   // Issues rendering commands
    gfx::Device* m_Device;       // Owns GPU driver interface + capabilities
    gfx::GLContext* m_Context;   // Logical OpenGL context for state management

    // Resource managers
    //BufferManager m_BufferManager;
    ShaderManager* m_ShaderManager;
    TextureManager* m_TextureManager;
};

};
