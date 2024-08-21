#pragma once
#include "Global.hpp"

#define SPRITE_BG_COLOR_FALSE          Color{ 231, 240, 252, 255 }
#define SPRITE_OUTLINE_COLOR_FALSE     Color{ 195, 204, 217, 255 }
#define SPRITE_BG_COLOR_TRUE           Color{ 255, 255, 255, 255 }
#define SPRITE_OUTLINE_COLOR_TRUE      Color{ 177, 62, 83, 255 }

class Sprite
{
    public:
        uint16_t x;
        uint16_t y;
        uint16_t fixed_x;
        uint16_t fixed_y;
        uint16_t width;
        uint16_t height;

        uint8_t id;

        Sprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t id);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};