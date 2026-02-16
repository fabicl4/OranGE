#include "Application.h"

#include "Log.h"

bool Application::Init() {
    // logging
    Log::Init();
    LOG_TRACE("[Application]Initializing application");

    // initialize platform and create window
    if (!m_Platform.Initialize()) {
        LOG_ERROR("[Application]Failed to initialize platform");
        return false;
    }

    m_CurrWindow = m_Platform.createWindow({m_Config.title, m_Config.width, m_Config.height, 0});
    if (!m_CurrWindow || !m_CurrWindow->IsCreated()) {
        LOG_ERROR("[Application]Failed to create window");
        return false;
    }

    m_CurrWindow->MakeContextCurrent();

    //-------------------------------------------------------------------------
    // Set event callbacks
    m_CurrWindow->SetOnResizeCallback(
        [this](uint32_t width, uint32_t height)
        {
            LOG_TRACE("[Application]Window resized: {}x{}", width, height);
            //m_Device->SetViewport(width, height);
            //m_Renderer->OnWindowResize(width, height);
        }
    );

    return true;
}

bool Application::Shutdown() {
    Log::Shutdown();
    // platform shutdown will release windows and other resources
    m_Platform.Shutdown();

    // release renderer
    // release device
    // release window

    return true;
}

bool Application::Run() {
    if (!Init()) {
        LOG_ERROR("[Application]Could not initialize");
        return false;
    }

    // Load shaders and textures

    OnCreate();

    // start timer before entering the loop
    ResetTimer();

    while (!m_CurrWindow->ShouldClose())
    {
        // process input

        // update clock and compute delta time since last frame
        f64 dt = CalculateDelta();

        OnRender();
        OnUpdate(dt);

        m_CurrWindow->SwapBuffers();
        m_Platform.PollEvents();
    }

    OnDestroy();

    return Shutdown();
    
}