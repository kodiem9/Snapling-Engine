#include "include/Sprite.hpp"

Sprite::Sprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t id) : x(x), y(y), width(width), height(height), id(id) {}

void Sprite::Draw()
{
    DrawRectangle(x, y, width, height, (Global::selected_sprite == id) ? SPRITE_BG_COLOR_TRUE : SPRITE_BG_COLOR_FALSE);
    DrawRectangleLinesEx(Rectangle{ (float)x, (float)y, (float)width, (float)height }, 3, (Global::selected_sprite == id) ? SPRITE_OUTLINE_COLOR_TRUE : SPRITE_OUTLINE_COLOR_FALSE);
}

void Sprite::Update()
{
    if(Global::MouseCollision(x, y, width, height)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            Global::selected_sprite = id;
        }
    }
}