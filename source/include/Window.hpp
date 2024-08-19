#pragma once
#include "common/PCH.hpp"

class Window
{
    private:
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

    public:
        Window(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
        void Draw(const std::function<void()>& Render);
        void Update();
};