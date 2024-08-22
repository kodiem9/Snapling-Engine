#include "include/TypeBox.hpp"

TypeBox::TypeBox(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Type type) : x(x), y(y), width(width), height(height), type(type)
{
    selected = false;
    period = false;
}

void TypeBox::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }

    DrawRectangle(fixed_x, fixed_y, width, height, WHITE);
    DrawRectangleLinesEx(Rectangle{ (float)fixed_x, (float)fixed_y, (float)width, (float)height }, 2, (selected) ? TYPEBOX_OUTLINE_COLOR_TRUE : TYPEBOX_OUTLINE_COLOR_FALSE);

    DrawText(value->c_str(), x + window_x + 5, y + window_y + 8, 15, TEXT_COLOR);
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
            if(MeasureText(value->c_str(), 15) + 15 < width) {
                if(key == '.' && period) return;
                if(type == Type::FLOAT && value->size() == 1 && value->at(0) == '0' && key != '.') {
                    value->pop_back();
                }
                value->push_back(key);
            }
        }

        if(key == '.' && type == Type::FLOAT) {
            period = true;
        }

        if(IsKeyPressed(KEY_BACKSPACE)) {
            if(type == Type::FLOAT) {
                if(value->at(value->size()-1) == '.') {
                    period = false;
                }
            }
            if(value->size() > 0) {
                value->pop_back();
            }
        }

        if(type == Type::FLOAT) {
            if(value->size() == 0) {
                value->push_back('0');
            }
        }
    }
}