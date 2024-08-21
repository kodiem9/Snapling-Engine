#include "include/Sprite.hpp"

Sprite::Sprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t id) : x(x), y(y), width(width), height(height), id(id)
{
    fixed_x = 0;
    fixed_y = 0;
}

void Sprite::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }
    DrawRectangle(fixed_x, fixed_y, width, height, (Global::selected_sprite == id) ? SPRITE_BG_COLOR_TRUE : SPRITE_BG_COLOR_FALSE);
    DrawRectangleLinesEx(Rectangle{ (float)fixed_x, (float)fixed_y, (float)width, (float)height }, 3, (Global::selected_sprite == id) ? SPRITE_OUTLINE_COLOR_TRUE : SPRITE_OUTLINE_COLOR_FALSE);
}

void Sprite::Update()
{
    if(Global::MouseCollision(fixed_x, fixed_y, width, height)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            Global::selected_sprite = id;
        }
    }
}