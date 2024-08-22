#pragma once
#include "Global.hpp"
#include "TypeBox.hpp"

class PropertiesBox
{
    private:
        std::string x_pos_string;
        std::string y_pos_string;

        TypeBox *sprite_name_box;
        TypeBox *x_pos_box;
        TypeBox *y_pos_box;

        uint8_t new_id;

    public:
        PropertiesBox();
        ~PropertiesBox();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
};