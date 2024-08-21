#include "include/PropertiesBox.hpp"

PropertiesBox::PropertiesBox()
{
    sprite_name_box = new TypeBox(100, 20, 120, 40);
}

void PropertiesBox::Draw(uint16_t window_x, uint16_t window_y)
{
    DrawText("Sprite", 15 + window_x, 25 + window_y, 25, TEXT_COLOR);
    sprite_name_box->Draw(window_x, window_y);
}

void PropertiesBox::Update()
{

}