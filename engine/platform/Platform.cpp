#include "Platform.h"

#include <GLFW/glfw3.h>

#include <core/Log.h>

namespace OranGE {

//-------------------------------------------------------------------------------
// WINDOW
//-------------------------------------------------------------------------------

Window::Window(const WindowProps& props)
    : m_Width(props.width), m_Height(props.height), m_Flags(props.flags), m_Title(props.title)
{
    m_Window = glfwCreateWindow(
            static_cast<int>(m_Width),
            static_cast<int>(m_Height),
            m_Title.c_str(),
            nullptr,
            nullptr
        );

    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        self->m_Width  = static_cast<uint32_t>(width);
        self->m_Height = static_cast<uint32_t>(height);

        // ---- User callback (Renderer / Application) ----
        if (self->m_OnResize)
            self->m_OnResize(self->m_Width, self->m_Height);
        
    });
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

void Window::MakeContextCurrent()
{
    glfwMakeContextCurrent(m_Window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const
{
    return m_Window && glfwWindowShouldClose(m_Window);
}


void Window::SetOnResizeCallback(WindowResizeCallback callback)
{
    m_OnResize = std::move(callback);
}

void Window::SetOnKeyPressedCallback(KeyPressCallback callback)
{
    m_OnKeyPressed = std::move(callback);
}


//-------------------------------------------------------------------------------
// PLATFORM
//-------------------------------------------------------------------------------

Platform::~Platform()
{
    LOG_TRACE("[Platform]Shutting down platform");

    // release windows
    m_Windows.clear();

    Shutdown();
}

bool Platform::Initialize()
{
    // Initialize platform-specific subsystems (e.g., SDL, GLFW)
    LOG_TRACE("[Platform]Initializing platform");

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Device Get API
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    return true;
}

bool Platform::Shutdown()
{
    // Clean up platform-specific resources
    LOG_TRACE("[Platform]Shutting down platform");

    glfwTerminate();

    return true;
}


Window* Platform::createWindow(const WindowProps& props)
{
    LOG_TRACE("[Platform]Creating window: {} ({}x{})", props.title, props.width, props.height);
    m_Windows.emplace_back(props);
    return &m_Windows.back();
}

void Platform::PollEvents()
{
    glfwPollEvents();
}

Platform::GLProcLoader Platform::GetGLLoadingFunction() {
    return (GLProcLoader)glfwGetProcAddress;
};

} // namespace OranGE