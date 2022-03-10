#include "./application.h"


int main(char** argc, char** argv)
{
    Application* app = new Application();
    app->OnInitialize();
    app->Run();
    app->OnTerminate();

    delete app;
    return 0;
}