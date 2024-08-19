#pragma once
#include "Window.hpp"
#include "Button.hpp"

enum ButtonType
{
    FULLSCREEN = 1,
    BIGGER_WINDOW,
    SMALLER_WINDOW
};

class Engine
{
    private:
        std::vector<Window> windows;
        std::vector<Button> buttons;

    public:
        Engine();
        ~Engine();
        void Draw();
        void Update();
};