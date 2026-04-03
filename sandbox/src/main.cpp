#include <OranGE.h>

int main()
{
    OranGE::ApplicationConfig config;
    config.title = "OranGE Engine";
    config.width = 1280;
    config.height = 720;

    OranGE::Application app(config);
    if (!app.Run()) {
        return -1;
    }

    return 0;
}