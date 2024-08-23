#include "include/TypeBlock.hpp"


// PUBLIC
TypeBlock::TypeBlock(uint16_t x, uint16_t y, Color color, const char* text) : x(x), y(y), color(color), text(text)
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
    DrawCircle(x + window_x, y + window_y, 12.0f, outline);
    DrawCircle(x + window_x, y + window_y, 10.0f, color);
    DrawText(text, x + window_x + 20, y + window_y - 7, 15, TEXT_COLOR);
}

void TypeBlock::Update()
{

}