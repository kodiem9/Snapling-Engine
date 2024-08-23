#pragma once
#include "Global.hpp"

class BlockTypePanel
{
    private:
        uint16_t x;
        uint16_t y;

    public:
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};