#include "application/Application.h"

#include <platform/Window.h>

namespace OranGE {

Application::Application(const ApplicationConfig& config)
    : m_Config(config)
{}

bool InitializeGLFW() {
     // Initialize window system (e.g., SDL, GLFW)
    LOG_TRACE("[Application]Initializing GLFW");

    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
    {
        // Log: Failed to initialize GLFW
        return false;
    }
    LOG_TRACE("[Platform]GLFW was initilize");

    glfwSetErrorCallback([](int error, const char* description)
    {
        LOG_ERROR("[Platform]GLFW Error {}: {}", error, description);
    });

    // disable OpenGL context creation
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    return true;
}

bool Application::Init() {
    Log::Initialize();

    if (!InitializeGLFW()) {
        return false;
    }

    // create window
    WindowProps props(m_Config.title, m_Config.width, m_Config.height);
    m_window = Window::Create(props);

    if (!m_window) {
        LOG_ERROR("Failed to create window.");
        return false;
    }

    return true;
}

bool Application::Shutdown() {
    Log::Shutdown();

    // release window
    delete m_window;

    glfwTerminate();

    return true;
}

bool Application::Run() {
    if (!Init()) {
        return false;
    }

    LOG_TRACE("Application started successfully.");

    // Load shaders and textures

    OnCreate();

    // start timer before entering the loop
    ResetTimer();

    while (!m_window->ShouldClose())
    {
        // process input

        // update clock and compute delta time since last frame
        f64 dt = CalculateDelta();

        OnRender();
        OnUpdate(dt);

        // Swapbuffers
        m_window->Update();
        // Poll events
        glfwPollEvents();
    }

    LOG_TRACE("Application is shutting down.");

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