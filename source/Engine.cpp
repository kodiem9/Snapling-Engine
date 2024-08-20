#include "include/Engine.hpp"


// PUBLIC
Engine::Engine()
{
    Global::LoadTextures();
    window_scale_mode = 0;
    saved_window_scale_mode = 0;

    // The windows enum is IN ORDER! So GAME_WINDOW is 0, first index in the vector is the game window, etc.
    windows.emplace_back(GetScreenWidth() - 640, 40, 60, 45, WindowType::GAME_WINDOW, 10);
    windows.emplace_back(GetScreenWidth() - 640, 500, 60, 15, WindowType::PROPERTIES_WINDOW, 10);

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
        window.Draw([&]() {});
    }

    for(Button &button: buttons) {
        button.Draw();
    }

    if(IsKeyDown(KeyboardKey::KEY_TAB)) {
        DrawFPS(10, 10);
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

    WindowAndButtonOffsets();
}


// PRIVATE
void Engine::WindowAndButtonOffsets()
{
    // All of this is just a bunch of offsets. You should probably not touch this ngl.
    switch(Global::button_pressed)
    {
        case ButtonTrigger::FULLSCREEN: FullscreenOffsets(); break;
        case ButtonTrigger::BIGGER_WINDOW: BiggerWindowOffsets(); break;
        case ButtonTrigger::SMALLER_WINDOW: SmallerWindowOffsets(); break;

        default: break;
    }
}


// OFFSETS
void Engine::FullscreenOffsets()
{
    Window &game_window = windows[WindowType::GAME_WINDOW];

    if(window_scale_mode != 2) {
        saved_window_scale_mode = window_scale_mode;
        for(Window &window: windows) {
            switch(window.type)
            {
                case WindowType::GAME_WINDOW: {
                    window.scale = 17;
                    window.y = (GetScreenHeight() - window.height * window.scale) / 2;
                    window.x = (GetScreenWidth() - window.width * window.scale) / 2;
                }
                break;

                case WindowType::PROPERTIES_WINDOW: window.visible = false; break;

                default: break;
            }
        }

        for(Button &button: buttons) {
            switch(button.trigger)
            {
                case ButtonTrigger::FULLSCREEN: {
                    button.scale = 3;
                    button.x = game_window.x + (game_window.width * game_window.scale) - BUTTON_SIZE * button.scale;
                    button.y += 6;
                }
                break;

                case ButtonTrigger::SMALLER_WINDOW: button.visible = false; break;
                case ButtonTrigger::BIGGER_WINDOW: button.visible = false; break;
            }
        }
        window_scale_mode = 2;
    }
    else {
        for(Window &window: windows) {
            switch(window.type)
            {
                case WindowType::GAME_WINDOW: {
                    if(saved_window_scale_mode == 0)
                        window.scale = 10;
                    else
                        window.scale = 5;
                    
                    window.y = 40;
                    window.x = (GetScreenWidth() - (window.width * window.scale) - 40);
                }
                break;

                case WindowType::PROPERTIES_WINDOW: window.visible = true; break;

                default: break;
            }
        }
        for(Button &button: buttons) {
            switch(button.trigger)
            {
                case ButtonTrigger::FULLSCREEN: {
                    button.scale = 2;
                    button.x = GetScreenWidth() - 72;
                    button.y -= 6;
                }
                break;

                case ButtonTrigger::SMALLER_WINDOW: button.visible = true; break;
                case ButtonTrigger::BIGGER_WINDOW: button.visible = true; break;
            }
        }
        window_scale_mode = saved_window_scale_mode;
    }
    Global::button_pressed = 0;
}

void Engine::BiggerWindowOffsets()
{
    if(window_scale_mode == 1) {
        for(Window &window: windows) {
            switch(window.type)
            {
                case WindowType::GAME_WINDOW: {
                    window.x -= window.width * window.scale;
                    window.scale = 10;
                }
                break;

                case WindowType::PROPERTIES_WINDOW: {
                    window.x -= window.width * window.scale;
                    window.y += 225; // difference between big and small game window
                    window.scale = 10;
                }
            }
        }
        window_scale_mode = 0;
    }
    Global::button_pressed = 0;
}

void Engine::SmallerWindowOffsets()
{
    if(window_scale_mode == 0) {
        for(Window &window: windows) {
            switch(window.type)
            {
                case WindowType::GAME_WINDOW: {
                    window.scale = 5;
                    window.x += window.width * window.scale;
                }
                break;

                case WindowType::PROPERTIES_WINDOW: {
                    window.scale = 5;
                    window.x += window.width * window.scale;
                    window.y -= 225; // difference between big and small game window
                }
                break;
            }
        }
        window_scale_mode = 1;
    }
    Global::button_pressed = 0;
}