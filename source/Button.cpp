#include "include/Button.hpp"


// PUBLIC
Button::Button(uint16_t x, uint16_t y, uint8_t trigger, Type type, uint8_t frame, float scale) : x(x), y(y), trigger(trigger), type(type), frame(frame), scale(scale)
{
    selected = false;
    pressed = false;
}

void Button::Draw()
{
    Texture();
    DrawTexturePro(Global::button_texture, spr.source, spr.dest, spr.origin, 0.0f, WHITE);
}

void Button::Update()
{
    if(GetMouseX() > x && GetMouseX() < x + BUTTON_SIZE * scale && GetMouseY() > y && GetMouseY() < y + BUTTON_SIZE * scale) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            pressed = true;
            selected = true;
        }
        if(IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
            if(pressed) {
                pressed = false;
                selected = false;
                Global::button_pressed = trigger;
            }
        }
    }
}


// PRIVATE
void Button::Texture()
{
    spr.source = Rectangle{ (float)BUTTON_SIZE * frame, (float)BUTTON_SIZE * selected, BUTTON_SIZE, BUTTON_SIZE };
    spr.dest = Rectangle{ (float)x, (float)y, spr.source.width * scale, spr.source.height * scale};
}