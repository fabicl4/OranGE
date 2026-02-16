#include <iostream>

#include <core/Application.h>
#include <core/Log.h>

class TestApp : public Application {
public:
    TestApp(const ApplicationConfig& config) : Application(config) {};

protected:
    virtual bool OnCreate() override {
        LOG_TRACE("[TestApp::OnCreate] Hello World!");

        return true;
    };

    virtual bool OnDestroy() override{
        LOG_TRACE("[TestApp::OnDestroy] Goodbye World!");

        return true;
    };

    virtual bool OnUpdate(f64 ts) override {
        // ts is delta time since last frame in seconds
        //LOG_TRACE("[TestApp::OnUpdate] delta={} run={}", ts, GetRunTime());
        return true;
    };

    virtual bool OnRender() override {
        return true;
    };

    //virtual void OnEvent() override {};

private:
    // Resources
    //int m_Shader {-1};
    //int m_Buffer {-1};

};

int main() 
{
    ApplicationConfig config;
    config.title = std::string("Test App");
    config.width = 800;
    config.height = 600;

    TestApp* app = new TestApp(config);

    std::cout << "Create test app" << std::endl;

    app->Run();

    std::cout << "Close app";

    return 0;

}