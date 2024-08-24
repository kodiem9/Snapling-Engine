#include "include/Button.hpp"


// PUBLIC
Button::Button(uint16_t x, uint16_t y, uint8_t trigger, Type type, uint8_t frame, float scale, Global::FTexture *texture, uint8_t *checkbox, uint8_t value)
: x(x), y(y), trigger(trigger), type(type), frame(frame), scale(scale), texture(texture), checkbox(checkbox), value(value)
{
    selected = false;
    pressed = false;
    visible = true;
    toggled = false;
}

void Button::Draw()
{
    if(visible) {
        Texture();
        DrawTexturePro(texture->texture, spr.source, spr.dest, spr.origin, 0.0f, WHITE);
    }
}

void Button::Update()
{
    if(visible) {
        if(Global::MouseCollision(x, y, texture->width * scale, texture->height * scale)) {
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

        if(type == Type::CHECKBOX) {
            toggled = (*checkbox == value);
        }
    }
}


// PRIVATE
void Button::Texture()
{
    uint8_t fixed_frame;
    if(toggled) fixed_frame = 2;
    else if(selected) fixed_frame = 1;
    else fixed_frame = 0;

    spr.source = Rectangle{ (float)texture->width * frame, (float)texture->height * fixed_frame, (float)texture->width, (float)texture->height };
    spr.dest = Rectangle{ (float)x, (float)y, spr.source.width * scale, spr.source.height * scale};
}