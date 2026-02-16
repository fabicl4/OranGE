#include "Application.h"

#include "Log.h"

bool Application::Init() {
    // logging
    Log::Init();
    LOG_TRACE("[Application]Initializing application");
    
    

    return true;
}

bool Application::Shutdown() {
    // release renderer
    // release device
    // release window

    return false;
}

bool Application::Run() {
    if (!Init()) {
        LOG_ERROR("[Application]Could not initialize");
        return false;
    }

    // Load shaders and textures

    OnCreate();

    while (true)
    {
        // process input.
        // time calculation

        OnRender();

        OnUpdate(0);
        
    }

    OnDestroy();

    return Shutdown();
    
}