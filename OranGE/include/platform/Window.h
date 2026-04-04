#pragma once

#include <GLFW/glfw3.h>

#include <core/types.h>

#include <core/Log.h>

namespace OranGE {

struct WindowProps {
    std::string title;
    uint32_t width, height;
    uint32_t flags;
};

class Window
{
    using WindowResizeCallback = std::function<void(int, int)>;
public:
    explicit Window(GLFWwindow* window, 
        const WindowProps& props);
    
    ~Window();

    bool IsCreated() const { return m_window != nullptr; }
    virtual bool ShouldClose() const;

    void* getNativeHandle() const {
        return m_window;
    }

    void Update();

    u32 GetWidth() const {
        return m_width;
    }
    u32 GetHeight() const {
        return m_height;
    }
    std::string GetTitle() const {
        return m_title;
    }
    u32 GetFlags() const {
        return m_flags;
    }

    // factory method to create a GLFW window
    static Window* Create(const WindowProps& props);

private:
    // Window properties
    uint32_t m_width, m_height;
    uint32_t m_flags;
    std::string m_title;

    // GLFW Handle
    GLFWwindow* m_window = nullptr;

    bool m_VSync = false;

};

}