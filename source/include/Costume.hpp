#pragma once
#include "Global.hpp"

#define COSTUME_BG_COLOR        Color{ 217, 228, 243, 255 }
#define COSTUME_OUTLINE_COLOR   Color{ 184, 193, 205, 255 }

class Costume
{
    private:
        uint16_t x;
        uint16_t y;
        uint16_t size;
        
    public:
        Costume(uint16_t x, uint16_t y, uint16_t size);
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};