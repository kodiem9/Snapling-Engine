#pragma once
#include "Global.hpp"

#define WINDOW_OUTLINE_COLOR Color{ 195, 204, 217, 255 }

class TypeBox
{
    public:
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        TypeBox(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};