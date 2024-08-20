#pragma once
#include "Global.hpp"

class Sprite
{
    public:
        Color bg_color;
        Color outline_color;

        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        Sprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color bg_color = WHITE, Color outline_color = BLACK);
        void Draw();
        void Update();
};