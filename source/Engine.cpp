#include "include/Engine.hpp"

Engine::Engine()
{
    Global::LoadTextures();

    windows.emplace_back(GetScreenWidth() - 640, 40, 600, 450);
    buttons.emplace_back(GetScreenWidth() - 72, 4, 0, 0, 2.0f);
}

Engine::~Engine()
{
    Global::UnloadTextures();
}

void Engine::Draw()
{
    for(Window &window: windows) {
        window.Draw([&]() {

        });
    }

    for(Button &button: buttons) {
        button.Draw();
    }
}

void Engine::Update()
{
    for(Window &window: windows) {
        window.Update();
    }

    for(Button &button: buttons) {
        button.Update();
    }
}