#pragma once
#include "Global.hpp"

class PopUp
{
    public:
        Color color;

        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        bool enabled;
        bool visible;

        PopUp(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color);
        void Draw();
        void Scroll(uint16_t &modify, uint16_t value, uint16_t smoothness);
};