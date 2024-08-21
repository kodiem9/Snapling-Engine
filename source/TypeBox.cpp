#include "include/TypeBox.hpp"

TypeBox::TypeBox(uint16_t x, uint16_t y, uint16_t width, uint16_t height) : x(x), y(y), width(width), height(height)
{
    selected = false;
}

void TypeBox::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }

    DrawRectangle(fixed_x, fixed_y, width, height, WHITE);
    DrawRectangleLinesEx(Rectangle{ (float)fixed_x, (float)fixed_y, (float)width, (float)height }, 2, (selected) ? TYPEBOX_OUTLINE_COLOR_TRUE : TYPEBOX_OUTLINE_COLOR_FALSE);

    DrawText(Global::entities[Global::selected_sprite].name.c_str(), x + window_x + 5, y + window_y + 10, 20, TEXT_COLOR);
}

void TypeBox::Update()
{
    if(Global::MouseCollision(fixed_x, fixed_y, width, height)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) selected = true;
    }
    else {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) selected = false;
    }
    
    if(selected) {
        key = GetCharPressed();
        if(key != 0) {
            if(MeasureText(Global::entities[Global::selected_sprite].name.c_str(), 20) + 20 < width) {
                Global::entities[Global::selected_sprite].name += key;
            }
        }

        if(IsKeyPressed(KEY_BACKSPACE)) {
            if(Global::entities[Global::selected_sprite].name.size() > 0) {
                Global::entities[Global::selected_sprite].name.pop_back();
            }
        }
    }
}