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

        Vector2 sprite_name_text_offset{};
        Vector2 x_pos_text_offset{};
        Vector2 y_pos_text_offset{};

        uint8_t new_id;

        static void Data(TypeBox *type_box, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TypeBox::Type);
        std::string CustomFloatToString(const float f);

    public:
        PropertiesBox();
        ~PropertiesBox();
        void Draw(uint16_t window_x, uint16_t window_y);
        void Update();
        void Reset(uint8_t mode);
};