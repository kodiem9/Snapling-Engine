#pragma once
#include "Global.hpp"

#define WINDOW_OUTLINE_COLOR Color{ 195, 204, 217, 255 }

class Window
{
    public:
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        uint8_t type;
        uint8_t scale;

        bool visible;

        Window(uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0, uint8_t type = 0, uint8_t scale = 1);
        void Draw(const std::function<void()>& Render);
        void Update();
};