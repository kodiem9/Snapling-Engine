#pragma once
#include "Window.hpp"
#include "Button.hpp"

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