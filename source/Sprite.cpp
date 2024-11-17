#include <Sprite.hpp>

Sprite::Sprite(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t id, bool upd_curr_spr) : x(x), y(y), fixed_x(0), fixed_y(0), width(width), height(height), id(id)
{
    data.x = 0.0F;
    data.y = 0.0F;
    data.size = 100;
    data.direction = 90.0F;
    data.show = true;
    data.direction_mode = 0;
    data.name = "Sprite";

    if(upd_curr_spr) {
        Global::selected_sprite = id;
    }
}

void Sprite::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }
    DrawRectangle(fixed_x, fixed_y, width, height, (Global::selected_sprite == id) ? SPRITE_BG_COLOR_TRUE : SPRITE_BG_COLOR_FALSE);
    DrawRectangleLinesEx(Rectangle{ static_cast<float>(fixed_x), static_cast<float>(fixed_y), static_cast<float>(width), static_cast<float>(height) }, 3, (Global::selected_sprite == id) ? SPRITE_OUTLINE_COLOR_TRUE : SPRITE_OUTLINE_COLOR_FALSE);
}

void Sprite::Update() const
{
    if(Global::MouseCollision(fixed_x, fixed_y, width, height)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            Global::selected_sprite = id;
        }
    }
}