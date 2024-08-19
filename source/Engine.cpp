#include "include/Engine.hpp"

Engine::Engine()
{
    windows.emplace_back(0, 0, 100, 100);
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