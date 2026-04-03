#include "application/Application.h"

namespace OranGE {

Application::Application(const ApplicationConfig& config)
    : m_Config(config)
{}

bool Application::Init() {


    return true;
}

bool Application::Shutdown() {

    return true;
}

bool Application::Run() {
    if (!Init()) {
        return false;
    }

    // Load shaders and textures

    OnCreate();

    // start timer before entering the loop
    ResetTimer();

    while (true)
    {
        // process input

        // update clock and compute delta time since last frame
        f64 dt = CalculateDelta();

        OnRender();
        OnUpdate(dt);

        // Swapbuffers
        // Poll events
    }

    OnDestroy();

    return Shutdown();
    
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
    return true;
}

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) {
        return this->OnWindowResize(e);
    });
}

} // namespace OranGE