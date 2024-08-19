#include "include/Engine.hpp"

Engine::Engine()
{
    Window window;

    // Game window
    window.width = 600;
    window.height = 450;
    window.x = GetScreenWidth() - window.width - 40;
    window.y = 40;

    windows.push_back(window);
}

Engine::~Engine()
{

}

void Engine::Draw()
{
    for(Window &window: windows) {
        window.Draw([&]() {
            
        });
    }
}

void Engine::Update()
{
    for(Window &window: windows) {
        window.Update();
    }
}