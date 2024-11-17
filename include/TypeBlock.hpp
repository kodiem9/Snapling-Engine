#pragma once
#include "Global.hpp"

#define TYPE_BLOCK_SELECTED_COLOR   Color{ 233, 238, 242, 255 }
#define TRANSPARENT                 Color{ 0, 0, 0, 0 }
#define TEXT_COLOR                  Color{ 87, 94, 117, 255 }

class TypeBlock
{
    private:
        const char* text;

        Color color;
        Color outline;

        uint16_t x;
        uint16_t y;
        uint16_t fixed_x;
        uint16_t fixed_y;

        uint8_t id;

    public:
        TypeBlock(Color color, const char* text);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};