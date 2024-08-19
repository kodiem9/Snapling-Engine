#include "include/Engine.hpp"


// PUBLIC
Engine::Engine()
{
    Global::LoadTextures();

    windows.emplace_back(GetScreenWidth() - 640, 40, 600, 450);
    buttons.emplace_back(GetScreenWidth() - 72, 4, ButtonType::FULLSCREEN, 0, 2.0f);
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

    switch(Global::button_pressed)
    {
        case ButtonType::FULLSCREEN: {
            printf("test 1\n");
            Global::button_pressed = 0;
        }
        break;

        case ButtonType::SMALLER_WINDOW: {
            printf("test 2\n");
            Global::button_pressed = 0;
        }
        break;

        case ButtonType::BIGGER_WINDOW: {
            printf("test 3\n");
            Global::button_pressed = 0;
        }
        break;

        default: break;
    }
}