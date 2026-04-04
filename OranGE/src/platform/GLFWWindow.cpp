#include <platform/Window.h>

namespace OranGE {

Window::Window(GLFWwindow* window, const WindowProps& props)
    : m_window(window),
    m_width(props.width), m_height(props.height), m_flags(props.flags), m_title(props.title)
{
    glfwSetWindowUserPointer(m_window, this);

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        self->m_width  = static_cast<uint32_t>(width);
        self->m_height = static_cast<uint32_t>(height);
        
    });
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    m_window = nullptr;
}

bool Window::ShouldClose() const
{
    return m_window && glfwWindowShouldClose(m_window);
}

void Window::Update()
{
    // Update internal state of the window
    if (!m_window)
        return;

    // if OpenGL then, 
    //glfwMakeContextCurrent(m_window);
    //glfwSwapBuffers(m_window);
}

Window* Window::Create(const WindowProps& props) {
    LOG_TRACE("[Window]Creating GLFW window: {} ({}x{})", props.title, props.width, props.height);

    GLFWwindow* window = glfwCreateWindow(
            static_cast<int>(props.width),
            static_cast<int>(props.height),
            props.title.c_str(),
            nullptr,
            nullptr
        );

    if (!window)
    {
        LOG_ERROR("[Window]Failed to create GLFW window");
        return nullptr;
    }
    
    // Property of the native window pointer is owned now by the Window
    return new Window(window, props);
}

}


