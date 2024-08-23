#include "include/TypeBlock.hpp"


// PUBLIC
TypeBlock::TypeBlock(uint16_t x, uint16_t y, Color color, const char* text, uint8_t id) : x(x), y(y), color(color), text(text), id(id)
{
    outline = color;
    if(outline.r >= 25) outline.r -= 25;
    else                outline.r = 0;
    if(outline.g >= 25) outline.g-= 25;
    else                outline.g = 0;
    if(outline.b >= 25) outline.b -= 25;
    else                outline.b = 0;
}

void TypeBlock::Draw(uint16_t window_x, uint16_t window_y)
{
    if(fixed_x != window_x || fixed_y != window_y) {
        fixed_x = x + window_x;
        fixed_y = y + window_y;
    }

    if(Global::selected_block_type == id) {
        DrawRectangle(fixed_x - 20, fixed_y - 20, 110, 40, LIGHTGRAY);
    }
    DrawCircle(fixed_x, fixed_y, 12.0f, outline);
    DrawCircle(fixed_x, fixed_y, 10.0f, color);
    DrawText(text, fixed_x + 20, fixed_y - 7, 15, TEXT_COLOR);
}

void TypeBlock::Update()
{
    if(Global::MouseCollision(fixed_x - 20, fixed_y - 20, 110, 40)) {
        if(IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            Global::selected_block_type = id;
        }
    }
}