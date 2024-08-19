#include "include/Button.hpp"


// PUBLIC
Button::Button(uint16_t x, uint16_t y, uint8_t type, uint8_t frame, float scale) : x(x), y(y), type(type), frame(frame), scale(scale) {}

void Button::Draw()
{
    Texture();
    DrawTexturePro(Global::button_texture, spr.source, spr.dest, spr.origin, 0.0f, WHITE);
}

void Button::Update()
{
    if(GetMouseX() > x && GetMouseX() < x + BUTTON_SIZE && GetMouseY() > y && GetMouseY() < y + BUTTON_SIZE) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) Global::button_pressed = type;
    }
}


// PRIVATE
void Button::Texture()
{
    spr.source = Rectangle{ (float)BUTTON_SIZE * frame, (float)BUTTON_SIZE * frame, BUTTON_SIZE, BUTTON_SIZE };
    spr.dest = Rectangle{ (float)x, (float)y, spr.source.width * scale, spr.source.height * scale};
}