#include "include/Engine.hpp"

Engine::Engine()
{
    Window window;

    // Game window
    window.width = 480;
    window.height = 360;
    window.x = GetScreenWidth() - window.width - 50;
    window.y = 50;

    windows.push_back(window);
}

Engine::~Engine()
{

}

void Engine::Draw()
{
    for(Window &window: windows) {
        window.Draw([&](){
            DrawRectangle(100, 100, 100, 100, RED);
        });
    }
}

void Engine::Update()
{
    for(Window &window: windows) {
        window.Update();
    }
}