#pragma once

#include <string>

struct ApplicationConfig
{
    std::string wrkDir;

    std::string title;
    uint32_t width;
    uint32_t height;
};

class Application {
public:

    Application(const ApplicationConfig& config) 
        : m_Config(config) {}
    
    virtual ~Application() = default;

    bool Run();

protected:

    virtual bool OnCreate() {return true;};
    virtual bool OnDestroy() {return true;};
    virtual bool OnUpdate(float ts) {return true;};
    virtual bool OnRender() {return true;};
    //virtual void OnEvent() {};

private:
    // Initialize systems
    bool Init();
    bool Shutdown();

protected:


    ApplicationConfig m_Config;
};
