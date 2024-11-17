#pragma once
#include "Global.hpp"

class Entity
{
    public:
        void Draw(uint16_t window_x, u_int16_t window_y, uint8_t id);
        void Update(uint8_t id);
};