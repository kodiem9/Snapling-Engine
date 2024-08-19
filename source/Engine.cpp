#include "include/Engine.hpp"


// PUBLIC
Engine::Engine()
{
    Global::LoadTextures();

    windows.emplace_back(GetScreenWidth() - 640, 40, 60, 45, WindowType::GAME_WINDOW, 10);
    window_scale_mode = 0;

    buttons.emplace_back(GetScreenWidth() - 72, 4, ButtonTrigger::FULLSCREEN, Button::Type::SINGLE_BUTTON, 0, 2.0f);
    buttons.emplace_back(GetScreenWidth() - 120, 4, ButtonTrigger::BIGGER_WINDOW, Button::Type::SINGLE_BUTTON, 1, 2.0f);
    buttons.emplace_back(GetScreenWidth() - 152, 4, ButtonTrigger::SMALLER_WINDOW, Button::Type::SINGLE_BUTTON, 2, 2.0f);
}

Engine::~Engine()
{
    Global::UnloadTextures();
}

void Engine::Draw()
{
    for(Window &window: windows) {
        window.Draw([&]() {
            DrawRectangle(window.x + (50 * window.scale) / 10, window.y + (50 * window.scale) / 10, (100 * window.scale) / 10, (100 * window.scale) / 10, RED);
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
        case ButtonTrigger::FULLSCREEN: {
            printf("test 1\n");
            Global::button_pressed = 0;
        }
        break;

        case ButtonTrigger::BIGGER_WINDOW: {
            if(window_scale_mode != 0) {
                Window &game_window = windows[WindowType::GAME_WINDOW];
                game_window.x -= game_window.width * game_window.scale;
                game_window.scale = 10;
            }
            window_scale_mode = 0;
            Global::button_pressed = 0;
        }
        break;

        case ButtonTrigger::SMALLER_WINDOW: {
            if(window_scale_mode != 1) {
                Window &game_window = windows[WindowType::GAME_WINDOW];
                game_window.scale = 5;
                game_window.x += game_window.width * game_window.scale;
            }
            window_scale_mode = 1;
            Global::button_pressed = 0;

        }
        break;

        default: break;
    }
}