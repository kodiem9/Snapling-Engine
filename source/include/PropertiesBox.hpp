#pragma once
#include "Global.hpp"
#include "TypeBox.hpp"

class PropertiesBox
{
    private:
        TypeBox *sprite_name_box;

    public:
        PropertiesBox();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};