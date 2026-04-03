#include <OranGE.h>

#include <iostream>

int main()
{

    std::cout << "Hello world!." << std::endl;


    OranGE::ApplicationConfig config;
    config.title = "OranGE Engine";
    config.width = 1280;
    config.height = 720;

    OranGE::Application app(config);
    if (!app.Run()) {
        return -1;
    }
    

    std::cout << "The application exited successfully." << std::endl;

    return 0;
}