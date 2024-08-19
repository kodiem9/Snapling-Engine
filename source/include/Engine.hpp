#pragma once
#include "common/PCH.hpp"
#include "Window.hpp"

class Engine
{
    private:
        std::vector<Window> windows;

    public:
        Engine();
        ~Engine();
        void Draw();
        void Update();
};