#pragma once
#include "Window.hpp"
#include "Button.hpp"

enum ButtonTrigger
{
    FULLSCREEN = 1,
    BIGGER_WINDOW,
    SMALLER_WINDOW
};

enum WindowType
{
    GAME_WINDOW,
    SPRITES_WINDOW
};

class Engine
{
    public:
        Engine();
        ~Engine();
        void Draw();
        void Update();
    
    private:
        std::vector<Window> windows;
        std::vector<Button> buttons;

        uint8_t window_scale_mode;

        void WindowAndButtonOffsets();
};