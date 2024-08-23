#pragma once
#include "Global.hpp"

class Grid
{
    private:
        struct Dot
        {
            uint16_t x;
            uint16_t y;

            Dot(uint16_t x, uint16_t y) : x(x), y(y) {}
        };

        std::vector<Dot> dots;

        bool held;
        uint16_t offset_x;
        uint16_t offset_y;
        uint16_t move_x;
        uint16_t move_y;

    public:
        Grid();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};