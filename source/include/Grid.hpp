#pragma once
#include "Global.hpp"

class Grid
{
    private:
        bool held;
        uint16_t offset_x;
        uint16_t offset_y;

    public:
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};