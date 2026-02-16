#pragma once

#include <core/defines.h>

// Platform-specific code and utilities

// Forward declarations
struct GLFWwindow;

struct WindowProps {
    std::string title;
    uint32_t width, height;
    uint32_t flags;
};

class Window {
    using WindowResizeCallback = std::function<void(int, int)>;
    using KeyPressCallback     = std::function<void(int)>;
public:
    explicit Window(const WindowProps& props);
    ~Window();

    void MakeContextCurrent();
    void SwapBuffers();

    bool ShouldClose() const;
    bool IsCreated() const { return m_Window != nullptr; }

    // Event-handling
    void SetOnResizeCallback(WindowResizeCallback callback);
    void SetOnKeyPressedCallback(KeyPressCallback callback);

    void SetVsync(bool enable);

    // getter and setters
    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    GLFWwindow* GetNativeWindow() const { return m_Window; }

private:

    // Window properties
    uint32_t m_Width, m_Height;
    uint32_t m_Flags;
    std::string m_Title;

    // GLFW Handle
    GLFWwindow* m_Window = nullptr;

    WindowResizeCallback m_OnResize;
    KeyPressCallback     m_OnKeyPressed;
};

class Platform
{
    using GLProcLoader = void* (*)(const char*);
public:

    Platform() = default;
    ~Platform();

    bool Initialize();
    bool Shutdown();

    Window* createWindow(const WindowProps& props);

    void PollEvents();

    // Platform related (Could be SDL or GLFW)
    [[nodiscard]]
    static GLProcLoader GetGLLoadingFunction();


private:
    // Holds a list of windows created by the platform
    std::vector<Window> m_Windows;
};


