#pragma once
#include "Global.hpp"
#include "TypeBox.hpp"

#define TEXT_COLOR Color{ 87, 94, 117, 255 }

class PropertiesBox
{
    private:
        TypeBox *sprite_name_box;

    public:
        PropertiesBox();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};